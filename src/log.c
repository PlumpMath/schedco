/*=============================================================================
#
# Author: nimisolo - nimisolo@gmail.com
#
# github : nimisolo
#
# Last modified: 2016-06-07 20:20
#
# Filename: log.c
#
# Description: 
#
=============================================================================*/
#include "log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define LOG_ERR "<libco:log:error> "

int log_level = 1;

static int log_fd = -1;
static char *log = "libco.log";
static char logbuf[4096];

int log_flags = O_WRONLY | O_APPEND | O_CREAT;
mode_t log_mode = S_IRUSR | S_IWUSR; 


/* 
* libco_log_out:
* Upon log system has ready, we should use log_out to log/disaply msg.
*/ 
int libco_log_out(int level, const char *format, ...)
{
    int len;
    ssize_t ret;
    va_list args;

    va_start(args, format);
    len = vsprintf(logbuf, format, args);
    va_end(args);

    logbuf[len++] = '\n';
    logbuf[len] = '\0';

    if (level <= log_level)
        printf(logbuf);

    
    /* 
    * no need to check log_fd, because we must use libco_log_start first! 
    */ 
    ret = write(log_fd, logbuf, len+1);
    if (-1 == ret) {
        printf(LOG_ERR"%s: %s\n", __func__, strerror(errno));
        return -1;
    }
    
    return 0;
}

/* 
* libco_log_start:
* Initializaiton libco's log system. Return -1 if something error, otherwise
* return 0.
* @level is the maximal level would display on console, default is 1.
*/ 
int libco_log_start(int level)
{
    log_fd = open(log, log_flags, log_mode);
    if (-1 == log_fd) {
        printf(LOG_ERR"%s: %s\n", __func__, strerror(errno));
        return -1; 
    }

    if (0 <= level && level <= 2)
        log_level = level;
   
    return 0;
}

void libco_log_end()
{
    if (-1 == close(log_fd))   
        printf(LOG_ERR"%s: %s\n", __func__, strerror(errno));
}
