/*=============================================================================
#
# Author: nimisolo - nimisolo@gmail.com
#
# github : nimisolo
#
# Last modified: 2016-06-10 20:53
#
# Filename: libco.c
#
# Description: 
#
=============================================================================*/
#include "log.h"
#include "libco.h"
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <assert.h>

define LIBCO_ERR "<libco:error> "

union cc_arg {
    void *p;
    int i[2];
};

struct coroutine {
    ucontext_t uc;
    char *stack;
    unsigned int co_id;
    co_fn entry;
    co_param param;
};

static __thread struct coroutine main_thread;
static __thread struct coroutine *current;

/* 
* coroutine_get_self:
* Get current-co's struct coroutine obj.
* Must call coroutine_init in main-thread first!
*/ 
struct coroutine *coroutine_get_self()
{
    assert(current);
    
    return current;    
}

/* 
* coroutine_init:
* initilizaiton main coroutine
*/ 
int coroutine_init()
{
    if (!current)
        current = &main_thread;

    if (-1 == getcontext(&current->uc)) {
        libco_log_out(LOG_LEVEL_ERROR, "%s:%s\n",
                __func__, strerror(errno));
        return -1;
    }

    return 0;
}



int init_libco(int log_enable, int log_level)
{
    if (-1 == libco_log_start(log_enable, log_level))
        goto log_failed;

log_failed:
    printf(LIBCO_ERR"%s failed\n", __func__);
    return -1;
}

int exit_libco(int log_del)
{
    libco_log_end(log_del);
}

