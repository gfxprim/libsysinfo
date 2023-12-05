//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <unistd.h>
#include <stdio.h>

#include "cpu_arch.h"
#include "cpu_stats.h"

static void print_cpu_arch(void)
{
	struct cpu_arch arch;

	cpu_arch_get(&arch);
	cpu_arch_print(&arch);
	printf("\n");
}

static void show_temp_load(void)
{
	struct cpu_stats *stats = cpu_stats_create();

	printf("CPU temp driver : %s\n\n", stats->temp.driver);

	cpu_stats_update(stats);

	usleep(300000);

	do {
		cpu_stats_update(stats);

		printf("\rCPU Load : %3i%%", (int)cpu_stats_load_perc(stats, 0));

		if (cpu_stats_temp_supported(stats))
			printf(" | CPU Temp : %3iC", (int)cpu_stats_temp(stats));

		fflush(stdout);
		usleep(300000);
	} while (1);
}

int main(void)
{
	print_cpu_arch();
	show_temp_load();

	return 0;
}
