/* This code provides an example for using the actest lib.
 * You can build it with 'make example'. */
#include "src/actest.h"
#include <stdlib.h>
#include <stdio.h>
/* These are the functions we want to test. */
int
add(int x, int y) {
	return x + y;
}

int
sub(int x, int y) {
	return x - y;
}

/* This function is intended to be flawed.
 * The tests will uncover that. */
int
mul(int x, int y) {
	int result = 0;
	for(int i = 0; i < y; ++i) {
		result += x;
	}
	
	return result;
}

/* These are the test functions,
 * note that all of them have the same prototype. */
char* test_add(void* data) {
	/* All of our test functions require data,
	 * so we need to check that the given pointer
	 * is not a NULL-pointer. */
	if (data) {
		/* This is where the actual testing happens.
		 * Note that the returned message should contain
		 * a note on what test failed (in this case add). */
		int* integer_data = data;
		if (integer_data[0] + integer_data[1] != add(integer_data[0], integer_data[1])) return "TEST ADD 1";
		if (integer_data[2] + integer_data[3] != add(integer_data[2], integer_data[3])) return "TEST ADD 2";
		if (integer_data[4] + integer_data[5] != add(integer_data[4], integer_data[5])) return "TEST ADD 3";
	} else {
		return "NO DATA PROVIDED";
	}	
	return 0;
}

char* test_mul(void* data) {
	if (data) {
		int* integer_data = data;
		if (integer_data[0] * integer_data[1] != mul(integer_data[0], integer_data[1])) return "TEST MUL 1";
		if (integer_data[2] * integer_data[3] != mul(integer_data[2], integer_data[3])) return "TEST MUL 2";
		if (integer_data[4] * integer_data[5] != mul(integer_data[4], integer_data[5])) return "TEST MUL 3";
	} else {
		return "NO DATA PROVIDED";
	}
	return 0;
}

char* test_sub(void* data) {
	if (data) {
		int* integer_data = data;
		if (integer_data[0] - integer_data[1] != sub(integer_data[0], integer_data[1])) return "TEST SUB 1";
		if (integer_data[2] - integer_data[3] != sub(integer_data[2], integer_data[3])) return "TEST SUB 2";
		if (integer_data[4] - integer_data[5] != sub(integer_data[4], integer_data[5])) return "TEST SUB 3";
	} else {
		return "NO DATA PROVIDED";
	}
	return 0;
}

/* We want to test 3 base cases for all functions.
 * 1. Both input integers are positive.
 * 2. One of the input integers is 0.
 * 3. Both input integers are negative.
 * This is of course not exhaustive. */
void* prepare() {
	int* data = malloc(6 * sizeof (int));

	/* Case 1 */
	data[0] = 4;
	data[1] = 5;

	/* Case 2 */
	data[2] = 4;
	data[3] = 0;

	/* Case 3 */
	data[4] = -5;
	data[5] = -10;

	return (void*) data;
}

void release(void* data) {
	free(data);
	return;
}

int main() {
	/* This array can tell us which tests failed.
	 * You will not need it most of the time.
	 * It needs to be freed however. */
	unsigned short* test_results_failed_array;
	/* Run the tests all at once */
	test_results_failed_array = actest_run_bulk(prepare, release, 3, test_add, test_sub, test_mul);
	free(test_results_failed_array);
	return 0;
}
