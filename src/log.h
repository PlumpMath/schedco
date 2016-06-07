#ifndef __LIBCO_LOG_H
#define __LIBCO_LOG_H

#include <stdio.h>

#define LIBCO_ERROR 0
#define LIBCO_WARN  1
#define LIBCO_DEBUG 2

extern int libco_log_out(int level, const char *format, ...);
extern int libco_log_start(int level);
extern void libco_log_end();

#endif

