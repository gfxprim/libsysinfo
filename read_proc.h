//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2024 Cyril Hrubis <metan@ucw.cz>

 */

/**
 * @file read_proc.h
 * @brief Optimized /proc/$PID/{stat,status} iterator and parser.
 */
#ifndef READ_PROC_H
#define READ_PROC_H

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdint.h>

/**
 * @brief Read proc iterator state.
 */
struct read_proc {
	/** @brief A proc directory. */
	DIR *pdir;
	/** @brief A current pid. */
	pid_t pid;
};

static inline int read_proc_init(struct read_proc *p)
{
	p->pdir = opendir("/proc/");

	return p->pdir == NULL;
}

static inline int read_proc_exit(struct read_proc *p)
{
	return closedir(p->pdir);
}

/**
 * @brief Parses a proc directory name into a pid.
 *
 * @param name A proc directory name.
 * @return A pid or 0 if the name is not numeric.
 */
static inline pid_t read_proc_get_pid(const char *name)
{
	pid_t pid = 0;

	for (;;) {
		char c = *(name++);

		switch (c) {
		case '0' ... '9':
			pid = 10 * pid + c - '0';
		break;
		default:
			return 0;
		}

		if (!*name)
			return pid;
	}
}

/**
 * @brief Moves to the next process.
 *
 * Fills in the p->pid field if there is a next process.
 *
 * @param p A read proc state.
 * @return Non-zero if there is a process, 0 if there is none.
 */
static inline int read_proc_next(struct read_proc *p)
{
	struct dirent *dir;
	pid_t pid = 0;

	for (;;) {
		dir = readdir(p->pdir);
		if (!dir)
			return 0;

		pid = read_proc_get_pid(dir->d_name);
		if (pid) {
			p->pid = pid;
			return 1;
		}
	}
}

struct read_proc_buf {
	char *buf;
	size_t len;
};

static inline uint64_t read_proc_buf_get_unum(struct read_proc_buf *buf)
{
	uint64_t ret = 0;

	if (!buf->len)
		return ret;

	for (;;) {
		char c  = *(buf->buf);

		switch (c) {
		case '0' ... '9':
			ret = 10 * ret + c - '0';
		break;
		default:
			return ret;
		}

		buf->len--;
		buf->buf++;

		if (!buf->len)
			return ret;
	}
}

static inline int64_t read_proc_buf_get_snum(struct read_proc_buf *buf)
{
	int neg = 1;

	if (!buf->len)
		return 0;

	if (*(buf->buf) == '-') {
		neg = -1;
		buf->len--;
		buf->buf++;
	}

	int64_t ret = read_proc_buf_get_unum(buf);

	return neg * ret;
}

static inline char read_proc_buf_getc(struct read_proc_buf *buf)
{
	if (!buf->len)
		return 0;

	char ret = *(buf->buf);

	buf->len -= 1;
	buf->buf += 1;

	return ret;
}

static inline void read_proc_buf_get_str(struct read_proc_buf *buf,
                                         struct read_proc_buf *dst,
					 char delim)
{
	for (;;) {
		if (!buf->len)
			goto ret;

		char c = *(buf->buf);

		if (c == delim)
			goto ret;

		if (dst->len > 1) {
			*(dst->buf) = c;
			dst->buf++;
			dst->len--;
		}

		buf->len--;
		buf->buf++;
	}

ret:
	*(dst->buf) = 0;
	return;
}

static inline void read_proc_buf_eat_ws(struct read_proc_buf *buf)
{
	for (;;) {
		if (!buf->len)
			return;

		char c = *(buf->buf);

		switch (c) {
		case ' ':
		case '\t':
		break;
		default:
			return;
		}

		buf->buf++;
		buf->len--;
	}
}

static inline void read_proc_buf_next_line(struct read_proc_buf *buf)
{
	for (;;) {
		if (!buf->len)
			return;

		char c = *(buf->buf);

		buf->buf++;
		buf->len--;

		if (c == '\n')
			return;
	}
}

/** @brief Kernel limit to comm size */
#define READ_PROC_COMM_SIZE 32

/**
 * @brief A struct to read subset of /proc/$PID/stat fields into.
 */
struct read_proc_stat {
	/**
	 * @brief Task pid.
	 */
	pid_t pid;

	/**
	 * @brief Task parent pid.
	 */
	pid_t ppid;

	/**
	 * @brief Task process group.
	 */
	pid_t pgrp;

	/**
	 * @brief Real UID.
	 */
	uid_t uid;

	/**
	 * @brief Effective UID.
	 */
	uid_t euid;

	/**
	 * @brief Real GID.
	 */
	gid_t gid;

	/**
	 * @brief Effective GID.
	 */
	gid_t egid;

	/**
	 * @brief Task state.
	 *
	 * One of:
	 * R - process is running
	 * S - process is sleeping
	 * D - process sleeping uninterruptibly
	 * Z - zombie process
	 * T - process is traced
	 */
	char state;

	/**
	 * @brief User mode time counter for the process.
	 *
	 * The value is in system ticks use sysconf(_SC_CLK_TCK) to get number
	 * of ticks per second.
	 */
	uint64_t utime;

	/**
	 * @brief Kernel mode time counter for the process.
	 *
	 * The value is in system ticks use sysconf(_SC_CLK_TCK) to get number
	 * of ticks per second.
	 */
	uint64_t stime;

	/**
	 * @brief Process schedulling priority.
	 */
	int nice;

	/**
	 * @brief Process start time.
	 *
	 * The value is in system ticks since the machine boot use
	 * sysconf(_SC_CLK_TCK) to get number of ticks per second.
	 */
	uint64_t start_time;

	/**
	 * @brief Program memory resident set in pages.
	 */
	uint32_t rss;

	/**
	 * @brief The command name.
	 *
	 * The string from /proc/$pid/comm
	 */
	char comm[READ_PROC_COMM_SIZE];
};

/**
 * @brief Parses subset of /proc/$PID/stat and /proc/$PID/status fields.
 *
 * @param p A read proc state.
 * @param stat A struct to store the parsed stat data into.
 *
 * There is a race window between listing the /proc/ directory content and
 * reading the stat file. This function may return non-zero if the process did
 * exit() and was waited for between the readdir() and open() of /proc/$PID/foo
 * files. The user of this function should skip to the next pid with
 * read_proc_next() if this functions returns non-zero.
 *
 * @return Zero on success, non-zero otherwise.
 */
static inline int read_proc_stat(struct read_proc *p, struct read_proc_stat *stat)
{
	char str[2048];
	struct read_proc_buf buf, comm;
	int fd;
	unsigned int i;

	snprintf(str, sizeof(str), "/proc/%i/stat", p->pid);
	fd = open(str, O_RDONLY);
	if (!fd)
		return 1;

	buf.len = read(fd, str, sizeof(str));
	buf.buf = str;

	/* PID */
	stat->pid = read_proc_buf_get_snum(&buf);

	/* Remove ' (' */
	read_proc_buf_getc(&buf);
	read_proc_buf_getc(&buf);

	/* Read comm */
	comm.buf = stat->comm;
	comm.len = sizeof(stat->comm);
	read_proc_buf_get_str(&buf, &comm, ')');

	/* Remove ') ' */
	read_proc_buf_getc(&buf);
	read_proc_buf_getc(&buf);

	/* Read state and remove ' ' */
	stat->state = read_proc_buf_getc(&buf);
	read_proc_buf_getc(&buf);

	/* Read parent PID and remove ' ' */
	stat->ppid = read_proc_buf_get_snum(&buf);
	read_proc_buf_getc(&buf);

	/* Read process group and remove ' ' */
	stat->pgrp = read_proc_buf_get_snum(&buf);
	read_proc_buf_getc(&buf);

	/* Ignore 8 numeric fields */
	for (i = 0; i < 8; i++) {
		read_proc_buf_get_snum(&buf);
		read_proc_buf_getc(&buf);
	}

	/* Read User and System time */
	stat->utime = read_proc_buf_get_unum(&buf);
	read_proc_buf_getc(&buf);
	stat->stime = read_proc_buf_get_unum(&buf);
	read_proc_buf_getc(&buf);

	/* Ignore cstime, cutime and realtime prio */
	for (i = 0; i < 3; i++) {
		read_proc_buf_get_snum(&buf);
		read_proc_buf_getc(&buf);
	}

	/* Read nice value. */
	stat->nice = read_proc_buf_get_snum(&buf);
	read_proc_buf_getc(&buf);

	/* Ignore num threads and itrealvalue */
	for (i = 0; i < 2; i++) {
		read_proc_buf_get_snum(&buf);
		read_proc_buf_getc(&buf);
	}

	/* Read process start time. */
	stat->start_time = read_proc_buf_get_unum(&buf);
	read_proc_buf_getc(&buf);

	/* Ignore vmsize. */
	read_proc_buf_get_unum(&buf);
	read_proc_buf_getc(&buf);

	/* Read program resident set. */
	stat->rss = read_proc_buf_get_unum(&buf);
	read_proc_buf_getc(&buf);

	close(fd);

	snprintf(str, sizeof(str), "/proc/%i/status", p->pid);
	fd = open(str, O_RDONLY);
	if (!fd)
		return 1;

	buf.len = read(fd, str, sizeof(str));
	buf.buf = str;

	while (buf.len) {
		char id_str[32];
		struct read_proc_buf id = {
			.buf = id_str,
			.len = sizeof(id_str)\
		};

		read_proc_buf_get_str(&buf, &id, ':');

		if (id_str[0] == 'U' && id_str[1] == 'i' &&
		    id_str[2] == 'd' && id_str[3] == 0) {
			/* Get rid of ':' */
			read_proc_buf_getc(&buf);
			read_proc_buf_eat_ws(&buf);
			stat->uid = read_proc_buf_get_unum(&buf);
			read_proc_buf_eat_ws(&buf);
			stat->euid = read_proc_buf_get_unum(&buf);
		}

		if (id_str[0] == 'G' && id_str[1] == 'i' &&
		    id_str[2] == 'd' && id_str[3] == 0) {
			/* Get rid of ':' */
			read_proc_buf_getc(&buf);
			read_proc_buf_eat_ws(&buf);
			stat->gid = read_proc_buf_get_unum(&buf);
			read_proc_buf_eat_ws(&buf);
			stat->egid = read_proc_buf_get_unum(&buf);
		}

		read_proc_buf_next_line(&buf);
	}

	close(fd);

	return 0;
}

#endif /* READ_PROC_H */
