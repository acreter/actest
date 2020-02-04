#include "actest.h"

unsigned int NUMBER_OF_TESTS_RUN = 0;

char*
actest_run(PrepareFunc prepare_func, ReleaseFunc release_func, TestFunc test_func) {
	void* input_for_test = 0;
	if (prepare_func) input_for_test = prepare_func();

	char* test_result;
	test_result = test_func(input_for_test);
	++NUMBER_OF_TESTS_RUN;

	if (release_func) release_func(input_for_test);

	return test_result;
}

unsigned short*
actest_run_bulk(PrepareFunc prepare_func, ReleaseFunc release_func, unsigned int number_of_test_func, ...) {
	va_list test_functions;
	va_start (test_functions, number_of_test_func);

	char* test_result;
	unsigned short* test_results_bit_array = malloc(number_of_test_func * sizeof (unsigned short));
	for (unsigned int i = 0; i < number_of_test_func; ++i) {
		test_result = actest_run(prepare_func, release_func, va_arg (test_functions, TestFunc));
		printf("| %s | %s\n", test_result ? "FAILED" : "PASSED", test_result);
		test_results_bit_array[i] = test_result ? 1 : 0;
	}

	va_end (test_functions);

	return test_results_bit_array;
}
