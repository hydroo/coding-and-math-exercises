#include "lib.hpp"

void testIsPrime();

int main() {
    testIsPrime();
    return 0;
}

void testIsPrime() {
    assert(isPrime( 1) == false);
    assert(isPrime( 2) == true );
    assert(isPrime( 3) == true );
    assert(isPrime( 4) == false);
    assert(isPrime( 5) == true );
    assert(isPrime( 6) == false);
    assert(isPrime( 7) == true );
    assert(isPrime( 8) == false);
    assert(isPrime( 9) == false);
    assert(isPrime(10) == false);
    assert(isPrime(11) == true );
    assert(isPrime(12) == false);
    assert(isPrime(13) == true );
    assert(isPrime(14) == false);
    assert(isPrime(15) == false);
    assert(isPrime(16) == false);
    assert(isPrime(17) == true );
    assert(isPrime(18) == false);
    assert(isPrime(19) == true );
    assert(isPrime(20) == false);
}
