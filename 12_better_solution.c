#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(int argc, char** argv)
{
    uint64_t i = 2;
    uint64_t trianglenr = 1;

    while(1) {
        trianglenr += i;
        ++i;

        uint64_t root = (uint64_t) sqrtf( (double) trianglenr );

        /* begin with 2 because 1 and n are divisors anyways */
        int divisorc = 2;
        uint64_t divisor;
        /* count every divisor up to sqrt(trianglenr) twice */
        for (divisor = 2; divisor <= root; ++divisor) {
            if( trianglenr % divisor == 0 ) {
                divisorc += 2;
            }
        }

        /* if there is a real sqare root the middle divisor (=the sqrt) is
            double -> decrease counter by one */
        if( root * root == trianglenr ) {
            --divisorc;
        }

        printf("%llu: %d\n", (long long unsigned) trianglenr, divisorc );

        if( divisorc > 500 ) {
            break;
        }
    }

    return 0;
}
