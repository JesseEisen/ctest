#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;

#define true  1
#define false 0

void
intequal
(
    int expect,
    int actual,
    int lineno,
    const char *fcname,
    const char *fname
);

void
intnequal
(
    int expect,
    int actual,
    int lineno,
    const char *fcname,
    const char *fname
);

void
strequal
(
    int expect,
    int actual,
    int lineno,
    const char *fcname,
    const char *fname
);

void
strnequal
(
    int expect,
    int actual,
    int lineno,
    const char *fcname,
    const char *fname
);
#endif /*  __UTIL_H__ */
