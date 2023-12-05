//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#ifndef MEM_STAT_H
#define MEM_STAT_H

#include <stdint.h>

struct mem_stat {
	uint64_t mem_total_kb;
	uint64_t mem_free_kb;
	uint64_t mem_cached_kb;

	uint64_t swap_total_kb;
	uint64_t swap_free_kb;
};

/**
 * @brief Parses current memory statistics.
 *
 * Fills in the stat structure with a current memory statistics. Values that
 * are not found are set to 0.
 *
 * @return Returns 0 on success, non-zero on a failure,
 *         (/proc/meminfo can't be read).
 */
int mem_stat_load(struct mem_stat *stat);

/**
 * @brief Pretty print memory statistics.
 */
void mem_stat_print(struct mem_stat *stat);

#endif /* MEM_STAT_H */
