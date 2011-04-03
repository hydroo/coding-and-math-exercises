#include <stdio.h>
#include <stdint.h>

int main(int arc, char** argv) {

	uint64_t i = 2;
	uint64_t numprime = 0;
	uint64_t prime = 0;

	while (numprime < 10001) {

		int isprime = 1;
		uint64_t a;
		for (a = 2; a < i; ++a) {
			if ( i % a == 0 ) {
				isprime = 0;
				break;
			}
		}

		if (isprime == 1) {
			++numprime;
			prime = i;

			printf( "%llu\n", (long long unsigned) prime);
		}

		++i;
	}

	printf("%llu\n", (long long unsigned) prime);

	return 0;
}
