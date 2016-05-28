#include "lib.hpp"

void testIsPrime();
void testPrimesToAtLeast();

int main() {
    testIsPrime();
    testPrimesToAtLeast();
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

void testPrimesToAtLeast() {
    QVector<s64> p;
    primesToAtLeast(20, &p);
    assert((p == QVector<s64>{2, 3, 5, 7, 11, 13, 17, 19, 23}));
}
