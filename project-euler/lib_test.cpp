#include "lib.hpp"

void testIsPrime();
void testPrimesToAtLeast();
void testPrimesTo();
void testGcd();
void testFactorial();

int main() {
    testIsPrime();
    testPrimesToAtLeast();
    testPrimesTo();
    testGcd();
    testFactorial();
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

void testPrimesTo() {
    QVector<s64> p = primesTo(20);
    assert((p == QVector<s64>{2, 3, 5, 7, 11, 13, 17, 19}));
}

void testGcd() {
    assert(gcd(  2,   2) ==   2);
    assert(gcd( 10,  10) ==  10);
    assert(gcd(121, 121) == 121);
    assert(gcd(100,   5) ==   5);
    assert(gcd(  5, 100) ==   5);
    assert(gcd(  3,   7) ==   1);
    assert(gcd(113, 107) ==   1);
    assert(gcd( 30,   6) ==   6);
}

void testFactorial() {
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(2) == 2);
    assert(factorial(3) == 6);
    assert(factorial(4) == 24);
    assert(factorial(5) == 120);
    assert(factorial(6) == 720);
}

