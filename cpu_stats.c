//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2007-2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

#include "cpu_stats.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define STATS "/proc/stat"

static void load_proc(struct cpu_stat *data, unsigned int cnt)
{
	FILE *f;

	f = fopen(STATS, "r");

	if (!f)
		return;

	unsigned int i;

	for (i = 0; i < cnt; i++) {
		unsigned long long user, nice, syst, idle, iowt, irq, sirq, sum;
		int ret;

		ret = fscanf(f, "%*s%llu%llu%llu%llu%llu%llu%llu%*u%*u%*u\n",
		             &user, &nice, &syst, &idle, &iowt, &irq, &sirq);

		if (ret <= 0)
			return;

		sum = user + nice + syst + idle + iowt + irq + sirq;

		data[i].user_diff = user - data[i].user;
		data[i].nice_diff = nice - data[i].nice;
		data[i].syst_diff = syst - data[i].syst;
		data[i].idle_diff = idle - data[i].idle;
		data[i].iowt_diff = iowt - data[i].iowt;
		data[i].irq_diff  = irq  - data[i].irq;
		data[i].sirq_diff = sirq - data[i].sirq;
		data[i].sum_diff  = sum  - data[i].sum;

		data[i].user = user;
		data[i].nice = nice;
		data[i].syst = syst;
		data[i].idle = idle;
		data[i].iowt = iowt;
		data[i].irq  = irq;
		data[i].sirq = sirq;
		data[i].sum  = sum;
	}

	fclose(f);
}

static void open_cpu_temp(struct cpu_temp *temp,
                          const char *sys_dir, const char *sys_dir_id,
                          const char **drivers,
			  int (*open_temp)(const char *subdir_name))
{
	DIR *d;
	struct dirent *ent;

	d = opendir(sys_dir);

	if (!d)
		return;

	while ((ent = readdir(d))) {
		char path[2048];
		char name[256];
		ssize_t size;
		int fd;

		snprintf(path, sizeof(path), sys_dir_id, ent->d_name);

		fd = open(path, O_RDONLY);
		if (fd < 0)
			continue;

		size = read(fd, name, sizeof(name));
		close(fd);

		if (size <= 1)
			continue;

		name[size-1] = 0;

		const char **id;
		int match = 0;

		for (id = drivers; *id; id++) {
			if (!strcmp(name, *id)) {
				match = 1;
				break;
			}
		}

		if (!match)
			continue;

		fd = open_temp(ent->d_name);

		if (fd >= 0) {
			temp->driver = *id;

			temp->fd = fd;
			temp->temp = 0;

			closedir(d);

			return;
		}
	}

	closedir(d);

	temp->fd = -1;
	temp->temp = INT_MIN;
	temp->driver = NULL;
}

static int open_hwmon_temp(const char *subdir_name)
{
	char path[2048];
	int i, fd;

	for (i = 0; i < 10; i++) {
		snprintf(path, sizeof(path),
		         "/sys/class/hwmon/%s/temp%i_input",
			 subdir_name, i);

		fd = open(path, O_RDONLY);

		if (fd > 0)
			return fd;
	}

	return -1;
}

static void open_hwmon(struct cpu_temp *temp)
{
	static const char *hwmon_cpu_drivers[] = {
		/* AMD */
		"k10temp",
		"k8temp",
		/* Intel */
		"coretemp",
		/* Embedded boards */
		"cpu_thermal",
		NULL
	};

	open_cpu_temp(temp, "/sys/class/hwmon", "/sys/class/hwmon/%s/name",
	              hwmon_cpu_drivers, open_hwmon_temp);
}

static int open_acpi_temp(const char *subdir_name)
{
	char path[2048];

	snprintf(path, sizeof(path),
	         "/sys/class/thermal/%s/temp",
		 subdir_name);

	return open(path, O_RDONLY);
}

static void open_acpi_thermal(struct cpu_temp *temp)
{
	static const char *acpi_cpu_types[] = {
		"x86_pkg_temp",
		NULL
	};

	open_cpu_temp(temp, "/sys/class/thermal", "/sys/class/thermal/%s/type",
	              acpi_cpu_types, open_acpi_temp);
}

static void close_hwmon(struct cpu_temp *temp)
{
	if (temp->fd >= 0)
		close(temp->fd);
}

static void read_hwmon(struct cpu_temp *temp)
{
	char buf[32];
	ssize_t ret;

	ret = pread(temp->fd, buf, sizeof(buf)-1, 0);

	if (ret <= 0)
		return;

	buf[ret] = 0;

	temp->temp = atoi(buf);
}

void cpu_stats_update(struct cpu_stats *self)
{
	load_proc(self->stats, self->nr_cpu + 1);

	if (self->temp.fd >= 0)
		read_hwmon(&self->temp);
}

void cpu_stats_destroy(struct cpu_stats *self)
{
	close_hwmon(&self->temp);

	free(self);
}

static unsigned int count_cpus(void)
{
	FILE *f;

	f = fopen(STATS, "r");

	if (!f)
		return 0;

	int flag = 1;
	unsigned int cnt = 0;

	for (;;) {
		switch (fgetc(f)) {
		case EOF:
			fclose(f);
			return cnt;
		case 'c':
			if (flag) {
				if (fgetc(f) == 'p' && fgetc(f) == 'u')
					cnt++;
				flag = 0;
			}
		break;
		case '\n':
			flag = 1;
		break;
		default:
			flag = 0;
		}
	}

	fclose(f);
	return cnt;
}

struct cpu_stats *cpu_stats_create(void)
{
	struct cpu_stats *stats;
	unsigned int cpus = count_cpus();

	stats = malloc(sizeof(struct cpu_stats) +
		       cpus * sizeof(struct cpu_stat));

	if (!stats)
		return NULL;

	stats->nr_cpu = cpus - 1;

	load_proc(stats->stats, cpus);

	open_hwmon(&stats->temp);

	if (stats->temp.fd < 0)
		open_acpi_thermal(&stats->temp);

	read_hwmon(&stats->temp);

	return stats;
}
