//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2024 Cyril Hrubis <metan@ucw.cz>

 */

#include <unistd.h>
#include <stdio.h>

#include "guid_map_cache.h"

static void print_uid(uint32_t uid)
{
	printf("%6i - '%s'\n", uid, uid_map_get(uid));
}

static void print_gid(uint32_t gid)
{
	printf("%6i - '%s'\n", gid, gid_map_get(gid));
}

int main(void)
{
	uint32_t i;

	printf("UIDs\n----\n");

	for (i = 0; i < 20; i++)
		print_uid(i);

	for (i = 1000; i < 1010; i++)
		print_uid(i);

	print_uid(1000);

	uid_map_drop_cache();
	uid_map_drop_cache();

	print_uid(1000);

	printf("\nGIDs\n----\n");

	for (i = 0; i < 30; i++)
		print_gid(i);

	gid_map_drop_cache();
	gid_map_drop_cache();

	return 0;
}
