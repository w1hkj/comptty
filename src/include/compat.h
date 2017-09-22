// ----------------------------------------------------------------------------
// Copyright (C) 2014
//              David Freese, W1HKJ
//
// This file is part of flmsg
//
// flrig is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// flrig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#ifndef COMPAT_H
#define COMPAT_H

/* adapted from compat.h in git-1.6.1.2 */

#if !defined(__APPLE__) && !defined(__FreeBSD__)  && !defined(__USLC__) && !defined(_M_UNIX)
#  define _XOPEN_SOURCE 600 /* glibc2 and AIX 5.3L need 500, OpenBSD needs 600 for S_ISLNK() */
#  define _XOPEN_SOURCE_EXTENDED 1 /* AIX 5.3L needs this */
#endif
#define _ALL_SOURCE 1
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1

#include <config.h>

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <assert.h>

#include "compat-mingw.h"

#ifdef __WIN32__
#  define dirent fl_dirent_no_thanks
#  else
#  include <dirent.h>
#  include <sys/utsname.h>
#  include <sys/ipc.h>
#  include <sys/msg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if SNPRINTF_RETURNS_BOGUS
#define snprintf git_snprintf
extern int git_snprintf(char *str, size_t maxsize,
			const char *format, ...);
#define vsnprintf git_vsnprintf
extern int git_vsnprintf(char *str, size_t maxsize,
			 const char *format, va_list ap);
#endif

#ifdef __cplusplus
}
#endif

#endif // MINGW32_H
