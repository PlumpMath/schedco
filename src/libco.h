/*=============================================================================
#
# Author: nimisolo - nimisolo@gmail.com
#
# github : nimisolo
#
# Last modified: 2016-06-10 20:53
#
# Filename: libco.h
#
# Description: 
#
=============================================================================*/
#ifndef __LIBCO_H
#define __LIBCO_H

#include <stdio.h>
#define _XOPEN_SOURCE
#include <ucontext.h>

typedef void (*co_fn)(void *param);
typedef void* co_param;

#endif

