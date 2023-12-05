//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2007-2023 Cyril Hrubis <metan@ucw.cz>

 */

#ifndef CPUINFO_PARSER_H
#define CPUINFO_PARSER_H

enum cpuinfo_type {
	CPUINFO_UINT,
	CPUINFO_UINT_MAX,
	CPUINFO_STR,
};

struct cpuinfo_entry {
	const char *name;
	enum cpuinfo_type type;
	int found;
	union {
		unsigned int uint;
		char *str;
	} val;
};

/**
 * @brief Parses /proc/cpuinfo and stores requested entries.
 *
 * The entries array has to be sorted by name.
 *
 * @entries An array of struct cpuinfo_entry
 * @entries_cnt An entries array lenght
 */
void cpuinfo_parse(struct cpuinfo_entry *entries, size_t entries_cnt);

/**
 * @brief Frees all strings allocated by cpuinfo parser.
 *
 * @entries An array of struct cpuinfo_entry
 * @entries_cnt An entries array lenght
 */
void cpuinfo_free(struct cpuinfo_entry *entries, size_t entries_cnt);

/**
 * @brief Prints parsed entries.
 *
 * Prints all entries that have the found flag set.
 *
 * @entries An array of struct cpuinfo_entry
 * @entries_cnt An entries array lenght
 */
void cpuinfo_print(struct cpuinfo_entry *entries, size_t entries_cnt);

#endif /* CPUINFO_PARSER_H */
