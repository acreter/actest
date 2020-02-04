#ifndef _ACTEST_H_INCLUDED
#define _ACTEST_H_INCLUDED

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* These are the function the user needs to implement
 * TestFunc: Takes pointer to data needed for testing as input.
 * 			 This isput is provided by PrepareFunc.
 * 			 Returns an error message (THIS MUST BE A STRING LITERAL),
 * 			 or 0 if the test passed.
 * PrepareFunc: Is run before the TestFunc and provides data for testing.
 * ReleaseFunc: Is run after the TestFunc and given the data pointer
 * 				provided by PrepareFunc. */
typedef char* (*TestFunc)(void*);
typedef void* (*PrepareFunc)();
typedef void  (*ReleaseFunc)(void*);

/* Run a test. If no preperation or releasing is required,
 * you can pass NULL-pointers for the respective arguments.
 * Returns the value returned by TestFunc. */
char* actest_run(PrepareFunc, ReleaseFunc, TestFunc);

/* Run multiple tests with the same PrepareFunc and ReleaseFunc.
 * This will print the results to stdout.
 * It also returns a mask for failed tests as bit field (1 = FAILED). */
unsigned short* actest_run_bulk(PrepareFunc, ReleaseFunc, unsigned int number_of_test_func, ...);

/* Stores the number of tests run */
extern unsigned int NUMBER_OF_TESTS_RUN;
#endif
