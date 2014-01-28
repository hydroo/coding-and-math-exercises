#include <stdio.h>
#include <stdint.h>

int main(int arc, char** argv) {

	uint64_t i = 2;
	uint64_t prime = 0;
	uint64_t sumofprimes = 0;

	while (i < 1000000) {

		int isprime = 1;
		uint64_t a;
		for (a = 2; a < i; ++a) {
			if ( i % a == 0 ) {
				isprime = 0;
				break;
			}
		}

		if (isprime == 1) {
			sumofprimes += i;

			printf( "%llu\n", (long long unsigned) i );
		}

		++i;
	}

	printf("sum %llu\n", (long long unsigned) sumofprimes);

	return 0;
}
