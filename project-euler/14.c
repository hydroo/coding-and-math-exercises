#include <stdio.h>

int main(int argc, char** argv) {

	unsigned int i;
	unsigned int ii;
	unsigned int cnt;

	unsigned int maxi = 0;
	unsigned int maxcnt = 0;

	for( i = 1000000; i > 1; --i ) {

		ii = i;
		cnt = 1;

		while( ii != 1 ) {
			

			if( ii % 2 == 0 ) {
				ii /= 2;
			} else {
				ii = 3 * ii +1;
			}
			++cnt;
		}

		if( maxcnt < cnt ) {
			maxi = i;
			maxcnt = cnt;
		}

	}

	printf("%u  %u\n", maxi, maxcnt );

	return 0;
}

