/*
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include "sys9.h"

typedef unsigned long long uvlong;
typedef long long vlong;
typedef unsigned char uchar;
typedef	unsigned long long uint64_t;
typedef	long long	int64_t;

static uint64_t order = 0x0001020304050607ULL;

static void
be2vlong(int64_t *to, char *f)
{
	char *t, *o;
	int i;

	t = (char*)to;
	o = (char*)&order;
	for(i = 0; i < 8; i++)
		t[o[i]] = f[i];
}

int
gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	char b[8];
	int64_t t;
	int opened;
	static int fd = -1;

	opened = 0;
	for(;;) {
		if(fd < 0)
			if(opened++ ||
			    (fd = open("/dev/bintime", OREAD|OCEXEC)) < 0)
				return 0;
		if(pread(fd, b, sizeof b, 0) == sizeof b)
			break;		/* leave fd open for future use */
		/* short read, perhaps try again */
		close(fd);
		fd = -1;
	}
	be2vlong(&t, b);

	tp->tv_sec = t/1000000000;
	tp->tv_usec = (t/1000)%1000000;

	if(tzp) {
		tzp->tz_minuteswest = 4*60;	/* BUG */
		tzp->tz_dsttime = 1;
	}

	return 0;
}
