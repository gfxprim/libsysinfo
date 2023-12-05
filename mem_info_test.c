//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <unistd.h>
#include <stdio.h>

#include "mem_stat.h"

int main(void)
{
	struct mem_stat stat;

	mem_stat_load(&stat);
	mem_stat_print(&stat);

	return 0;
}
