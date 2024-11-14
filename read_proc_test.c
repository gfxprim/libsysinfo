//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2024 Cyril Hrubis <metan@ucw.cz>

 */

#include <stdio.h>

#include "read_proc.h"

int main(void)
{
	struct read_proc p;
	struct read_proc_stat stat;

	if (read_proc_init(&p)) {
		perror("read_proc_init() failed");
		return 1;
	}

	while (read_proc_next(&p)) {
		if (read_proc_stat(&p, &stat)) {
			printf("Failed to parse %i\n", p.pid);
			continue;
		}

		printf("%8i %c [ %-31s ] UID: %6i EUID: %6i GID: %6i EGID: %6i RSS: %10u\n",
		       stat.pid, stat.state, stat.comm,
		       stat.uid, stat.euid, stat.gid, stat.egid,
		       stat.rss);
	}

	read_proc_exit(&p);

	return 0;
}
