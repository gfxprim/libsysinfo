//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2007-2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "cpuinfo_parser.h"

static int parse_string(FILE *f, char *name, size_t namelen, char terminator)
{
	size_t pos = 0;
	int c;

	for (;;) {
		c = fgetc(f);

		if (!isspace(c) || c == terminator)
			break;

		if (c == EOF)
			return 1;
	}

	for (;;) {
		if (pos < namelen-1)
			name[pos++] = c;

		c = fgetc(f);

		if (c == terminator)
			break;

		if (c == EOF)
			return 1;
	}

	name[pos] = 0;

	if (!pos)
		return 0;

	pos--;

	while (pos > 0 && isspace(name[pos]))
		name[pos--] = 0;

	return 0;
}

static struct cpuinfo_entry *entry_by_name(struct cpuinfo_entry *entries,
                                           size_t entries_cnt, const char *name)
{
	size_t mid = -1;
	size_t l = 0;
	size_t r = entries_cnt-1;

	while (r - l > 1) {
		mid = (l+r)/2;

		int ret = strcmp(entries[mid].name, name);
		if (!ret)
			return entries + mid;

                if (ret < 0)
                        l = mid;
                else
                        r = mid;
        }

	if (r != mid && !strcmp(entries[r].name, name))
		return entries + r;

	if (l != mid && !strcmp(entries[l].name, name))
		return entries + l;

	return NULL;
}

static void parse_entry(struct cpuinfo_entry *entry, const char *val)
{
	unsigned int ival;
	long tmp;

	if (!entry)
		return;

	if (entry->found && entry->type != CPUINFO_UINT_MAX)
		return;

	switch (entry->type) {
	case CPUINFO_STR:
		entry->val.str = strdup(val);
	break;
	case CPUINFO_UINT:
		tmp = strtol(val, NULL, 0);

		if (tmp < 0)
			return;

		if (sizeof(long) != sizeof(unsigned int) &&
		    tmp > (long)UINT_MAX)
			return;

		entry->val.uint = tmp;
	break;
	case CPUINFO_UINT_MAX:
		ival = atoi(val);
		if (entry->val.uint < ival)
			entry->val.uint = ival;
	break;
	}

	entry->found = 1;
}

void cpuinfo_parse(struct cpuinfo_entry *entries, size_t entries_cnt)
{
	FILE *cpuinfo;
	struct cpuinfo_entry *entry;
	size_t i;
	char name[64];
	char val[128];

	for (i = 0; i < entries_cnt; i++) {
		entries[i].found = 0;
		entries[i].val.str = NULL;
	}

	cpuinfo = fopen("/proc/cpuinfo", "r");
	if (!cpuinfo)
		return;

	for (;;) {
		if (parse_string(cpuinfo, name, sizeof(name), ':')) {
			fclose(cpuinfo);
			return;
		}

		//printf("NAME: '%s'\n", name);

		entry = entry_by_name(entries, entries_cnt, name);

		if (parse_string(cpuinfo, val, sizeof(val), '\n')) {
			fclose(cpuinfo);
			return;
		}

		//printf("VAL: %s\n", val);

		parse_entry(entry, val);
	}
}

void cpuinfo_free(struct cpuinfo_entry *entries, size_t entries_cnt)
{
	size_t i;

	for (i = 0; i < entries_cnt; i++) {
		if (entries[i].type == CPUINFO_STR)
			free(entries[i].val.str);
	}
}

void cpuinfo_print(struct cpuinfo_entry *entries, size_t entries_cnt)
{
	size_t i;

	for (i = 0; i < entries_cnt; i++) {
		if (!entries[i].found)
			continue;

		switch (entries[i].type) {
		case CPUINFO_STR:
			printf("%s\t\t: %s\n", entries[i].name, entries[i].val.str);
		break;
		case CPUINFO_UINT:
		case CPUINFO_UINT_MAX:
			printf("%s\t\t: %u\n", entries[i].name, entries[i].val.uint);
		break;
		}
	}
}
