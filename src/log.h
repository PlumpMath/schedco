/*=============================================================================
#
# Author: nimisolo - nimisolo@gmail.com
#
# github : nimisolo
#
# Last modified: 2016-06-10 19:35
#
# Filename: log.h
#
# Description: 
#
=============================================================================*/
#ifndef __LIBCO_LOG_H
#define __LIBCO_LOG_H

#include <stdio.h>

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN  1
#define LOG_LEVEL_DEBUG 2

#define LOG_DISABLE 0
#define LOG_ENABLE 1

#define LOG_FILE_DEL 1
#define LOG_FILE_PERSIST 0

extern int libco_log_out(int level, const char *format, ...);
extern int libco_log_start(int enable, int level);
extern void libco_log_end(int del);

#endif

