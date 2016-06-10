/*=============================================================================
#
# Author: nimisolo - nimisolo@gmail.com
#
# github : nimisolo
#
# Last modified:	2016-06-08 20:53
#
# Filename:		log.c
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
#include <time.h>

#define LOG_ERR "<libco:log:error> "

static int log_level = 1;
static int log_fd = -1;
static char *log = "libco.log";
static char logbuf[4096];
static int log_flags = O_WRONLY | O_APPEND | O_CREAT;
static mode_t log_mode = S_IRUSR | S_IWUSR; 

static char *log_color[] = {
    "\x1b[31m", // COLOR_RED
    "\x1b[33m", // COLOR_YELLOW
    "\x1b[34m"  // COLOR_BLUE
};

/* 
* libco_log_out:
* Upon log system has ready, we should use log_out to log/disaply msg.
*/ 
int libco_log_out(int level, const char *format, ...)
{
    int len;
    ssize_t ret;
    va_list args;
    time_t tm;

    time(&tm);
    strcpy(logbuf, asctime(gmtime(&tm)));

    len = strlen(logbuf);
    logbuf[len-1] = '|';
    logbuf[len++] = ' ';

    va_start(args, format);
    len += vsprintf(logbuf+len, format, args);
    va_end(args);

    logbuf[len++] = '\n';
    logbuf[len] = '\0';

    if (level <= log_level)
        printf("%s%s", log_color[level], logbuf);

    
    /* 
    * user disable log OR log init failed 
    */ 
    if (-1 == log_fd)
        return 0;

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
int libco_log_start(int enable, int level)
{
    if (enable <= 0) {
        log_level = 2;
        return 0;
    }

    log_fd = open(log, log_flags, log_mode);
    if (-1 == log_fd) {
        printf(LOG_ERR"%s: %s\n", __func__, strerror(errno));
        return -1; 
    }

    if (0 <= level && level <= 2)
        log_level = level;
   
    return 0;
}


/* 
* libco_log_end:
* Disable libco's log system. 
* This will delete log file if @del is positive. 
*/ 
void libco_log_end(int del)
{
    if (-1 == close(log_fd))   
        printf(LOG_ERR"%s: %s\n", __func__, strerror(errno));
    
    if (del > 0)
        remove(log);    
}

