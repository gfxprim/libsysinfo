//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2007-2023 Cyril Hrubis <metan@ucw.cz>

 */

#ifndef CPU_STATS_H
#define CPU_STATS_H

struct cpu_arch;

struct cpu_stat {
	unsigned long long user;
	unsigned long long user_diff;

	unsigned long long nice;
	unsigned long long nice_diff;

	unsigned long long syst;
	unsigned long long syst_diff;

	unsigned long long idle;
	unsigned long long idle_diff;

	unsigned long long iowt;
	unsigned long long iowt_diff;

	unsigned long long irq;
	unsigned long long irq_diff;

	unsigned long long sirq;
	unsigned long long sirq_diff;

	unsigned long long sum;
	unsigned long long sum_diff;
};

struct cpu_temp {
	/* Temperature in Celsius * 1000 or INT_MIN if not available */
	int temp;
	/* Driver name */
	const char *driver;
	/* Do not touch */
	int fd;
};

/**
 * The stats array is nr_cpus + 1 long and the stats[0] is the overall value.
 */
struct cpu_stats {
	/* Number of CPUs */
	unsigned int nr_cpu;
	/* CPU temperature */
	struct cpu_temp temp;
	/* Per core CPU load statistics */
	struct cpu_stat stats[];
};

static inline int cpu_stats_temp_supported(struct cpu_stats *self)
{
	return self->temp.fd >= 0;
}

static inline float cpu_stats_temp(struct cpu_stats *self)
{
	return 0.001 * self->temp.temp;
}

static inline float cpu_stats_load_perc(struct cpu_stats *self, unsigned int cpu)
{
	return 100.00 * (self->stats[cpu].sum_diff - self->stats[cpu].idle_diff) / self->stats[cpu].sum_diff;
}

struct cpu_stats *cpu_stats_create(struct cpu_arch *arch);

void cpu_stats_update(struct cpu_stats *self);

void cpu_stats_destroy(struct cpu_stats *self);

#endif /* CPU_STATS_H */
