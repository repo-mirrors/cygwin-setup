/*
 * Copyright (c) 2000, Red Hat, Inc.
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     A copy of the GNU General Public License can be found at
 *     http://www.gnu.org/
 *
 * Written by DJ Delorie <dj@redhat.com>
 *
 */

/* This is for "printf"-like logging.  Messages are stored in memory
   until they're written out.  "babble" means the message is just idle
   babbling; it can be ignored for shorter logs. */

#include "String++.h"

enum log_level {
  LOG_PLAIN = 2,
  LOG_BABBLE = 1,
  LOG_TIMESTAMP	= 2
};

void log (enum log_level level, const char *fmt, ...)
  __attribute__ ((format (printf, 2, 3)));
void log (enum log_level level, String const &);

/* Here, "babble" means to write out the babble also.  If "append" is
   nonzero, the log is appended to any existing file. */

void log_save (int writebabble, String const &filename, int append);

/* This is the only legal way to exit.  It writes out all the logs and things */

void exit_setup (int exit_code) __attribute__ ((noreturn));
