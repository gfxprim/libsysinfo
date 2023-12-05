//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "mem_stat.h"

int mem_stat_load(struct mem_stat *stat)
{
	FILE *meminfo;
	char id[64];
	uint64_t val = 0;

	memset(stat, 0, sizeof(*stat));

	meminfo = fopen("/proc/meminfo", "r");
	if (!meminfo)
		return 1;

	while (fscanf(meminfo, "%64s %" SCNu64 " kB\n", id, &val) == 2) {
		if (id[0] == 'M' &&  id[1] == 'e' && id[2] == 'm') {
			if (id[3] == 'T' && id[4] == 'o' && id[5] == 't' &&
			    id[6] == 'a' && id[7] == 'l' && id[8] == ':')
				stat->mem_total_kb = val;
			if (id[3] == 'F' && id[4] == 'r' && id[5] == 'e' &&
			    id[6] == 'e' && id[7] == ':')
				stat->mem_free_kb = val;
		}

		if (id[0] == 'C' && id[1] == 'a' && id[2] == 'c' && id[3] == 'h' &&
		    id[4] == 'e' && id[5] == 'd' && id[6] == ':')
			stat->mem_cached_kb = val;

		if (id[0] == 'S' && id[1] == 'w' && id[2] == 'a' && id[3] == 'p') {
			if (id[4] == 'T' && id[5] == 'o' && id[6] == 't' &&
			    id[7] == 'a' && id[8] == 'l' && id[9] == ':')
				stat->swap_total_kb = val;
			if (id[4] == 'F' && id[5] == 'r' && id[6] == 'e' &&
			    id[7] == 'e' && id[8] == ':')
				stat->swap_free_kb = val;
		}
	}

	fclose(meminfo);

	return 0;
}

void mem_stat_print(struct mem_stat *stat)
{
	printf("MemTotal\t: %"PRIu64" kB\n", stat->mem_total_kb);
	printf("MemFree\t\t: %"PRIu64" kB\n", stat->mem_free_kb);
	printf("MemCached\t: %"PRIu64" kB\n", stat->mem_cached_kb);
	printf("SwapTotal\t: %"PRIu64" kB\n", stat->swap_total_kb);
	printf("SwapFree\t: %"PRIu64" kB\n", stat->swap_free_kb);
}
