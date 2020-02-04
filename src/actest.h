#ifndef _ACTEST_H_INCLUDED
#define _ACTEST_H_INCLUDED

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* (*TestFunc)(void*);
typedef void* (*PrepareFunc)();
typedef void  (*ReleaseFunc)(void*);

char* actest_run(PrepareFunc, ReleaseFunc, TestFunc);
unsigned short* actest_run_bulk(PrepareFunc, ReleaseFunc, unsigned int number_of_test_func, ...);

extern unsigned int NUMBER_OF_TESTS_RUN;
#endif
