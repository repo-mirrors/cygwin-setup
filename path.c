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
 * Written by Ron Parker <parkerrd@hotmail.com>
 *
 */

#include <windows.h>
#include <wininet.h>
#include <assert.h>
#include <ctype.h>
#include <direct.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <shellapi.h>
#include <shlguid.h>
#include <shlobj.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "setup.h"
#include "strarry.h"
#include "zlib/zlib.h"

static FILE *cygin = NULL, *cygout = NULL;
static HANDLE hcygpath = NULL;

void
exit_cygpath (void)
{
  if (cygin)
    fclose (cygin);
  if (cygout)
    fclose (cygout);
  if (hcygpath)
    {
      Sleep (0);
      if (WaitForSingleObject (hcygpath, 5000) != WAIT_OBJECT_0)
	{
	  TerminateProcess (hcygpath, 0);
	  WaitForSingleObject (hcygpath, 5000);
	}
      CloseHandle (hcygpath);
    }
}

static int
cygpath_pipe (void)
{
  int hpipein[2] = {-1, -1};
  int hpipeout[2] = {-1, -1};
  char buffer[256];
  
  HANDLE hin, hout;
  if (_pipe (hpipein, 256, O_TEXT) == -1)
    return 0;
  if (_pipe (hpipeout, 256, O_TEXT) == -1)
    return 0;

  hin = (HANDLE) _get_osfhandle (hpipein[1]);
  hout = (HANDLE) _get_osfhandle (hpipeout[0]);
  sprintf (buffer, "cygpath -a -o -f - -c %lx", (unsigned long) _get_osfhandle (hpipeout[1]));
  hcygpath = (HANDLE) xcreate_process (0, hout, hin, hin, buffer);
  if (!hcygpath)
    return 0;
  _close (hpipein[1]);
  _close (hpipeout[0]);
  cygin = fdopen (hpipein[0], "rt");
  cygout = fdopen (hpipeout[1], "wt");
  setbuf (cygout, NULL);
  return 1;
}

char *
pathcvt (char target, const char *path)
{
  char buffer[1024];
  char *retval;

  if (!cygin && !cygpath_pipe ())
    return NULL;	/* FIXME - error */

  fprintf (cygout, "-%c %s\n", target, path);
  retval = fgets (buffer, sizeof (buffer), cygin);
  if (retval)
    {
      char *p = strchr (buffer, '\n');
      if (p != NULL)
	*p = '\0';
      retval = xstrdup (buffer);
    }

  /* If there is an error try using the original style path anyway. */
  return retval ? retval : xstrdup (path);
}

char *
dtoupath (const char *path)
{
  char *retval = pathcvt ('u', path);
  size_t len = strlen (retval);
  if (len > 2 && retval[len - 1] == '/')	/* Trim the trailing slash
						   off of a nonroot path. */
    retval[len - 1] = '\0';

  return retval;
}

char *
utodpath (const char *path)
{
  char *retval = pathcvt ('w', path);
  size_t len = strlen (retval);
  if (len > 3 && retval[len - 1] == '\\')	/* Trim the trailing slash
						   off of a nonroot path. */
    retval[len - 1] = '\0';

  return retval;
}

char *
pathcat (const char *arg1, const char *arg2)
{
  char path[_MAX_PATH];
  size_t len;
  char *s, *d;

  strcpy (path, arg1);
  strcat (path, "\\");
  strcat (path, arg2);

  for (s=path; *s; s++)
    if (*s == '/')
      *s = '\\';
  for (s=d=path; *s; s++)
    {
      *d++ = *s;
      if (*s == '\\')
	while (s[1] == '\\')
	  s++;
    }
  *d = 0;

  return xstrdup (path);
}
