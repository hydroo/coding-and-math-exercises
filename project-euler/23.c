#include <stdio.h>
#include <math.h>

static int abundant(unsigned int i)
{
	unsigned int divisor;
	unsigned int divisorsum = 1;
	unsigned int root = (unsigned int) sqrtf((float)i);

	for (divisor = 2; divisor <= root; ++divisor) {
		if( i % divisor == 0 ) {
			divisorsum += divisor;
			if( divisor*divisor != i ) divisorsum += i / divisor;
		}
	}

	/*if (divisorsum >i) printf("%u\n",i);*/

	return divisorsum > i;
}

int main(int argc, char** argv)
{
	unsigned int i;
	unsigned int abundantnumbers[28124];

	long long unsigned int sum = 1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17+18+19+20+21+22+23;

	for (i = 0; i < 28124; ++i) abundantnumbers[i] = 0;

	for (i = 12; i < 28124; ++i) {
		if (abundant(i)) abundantnumbers[i] = 1;
	}

	
	for (i = 24; i < 28124; ++i) {
		int abundant = 0;
		unsigned int a;
		for (a=12;a<=i-12;++a) {
			if (abundantnumbers[a] && abundantnumbers[i-a]) {
				abundant = 1;
			}
		}

		if (abundant == 0) {
			sum += i;
			/*printf( "%u!\t\t%u\n",i,sum);*/
		}
	}

	printf("sum: %llu\n",sum);

	return 0;
}

