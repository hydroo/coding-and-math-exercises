#include <cassert>
#include <cmath>

#include <QtDebug>
#include <QTime>

using s64 = int64_t;

s64 squareRootCeil(s64 nn) {
    return (s64) ceil(sqrt(nn));
}

struct Primes {
    s64 max;
    QSet<s64> s; // quick lookup
    QList<s64> l; // sorted
};

Primes initPrimes() {
    return Primes{1, QSet<s64>{}, QList<s64>{}};
}

void updatePrimes(s64 n, Primes *primes) {
    if (n <= primes->max) { return; }

    for (s64 i = primes->max + 1; i <= n; i += 1) {
        bool iIsPrime = true;
        s64 maxDiv = squareRootCeil(i);
        for (int j = 0; j < primes->l.size() && primes->l[j] <= maxDiv; j += 1) {
            if (i % primes->l[j] == 0) {
                iIsPrime = false;
                break;
            }
        }
        if (iIsPrime == true) {
            primes->s << i;
            primes->l << i;
        }
    }

    primes->max = n;
}

bool isPrime(s64 n, const Primes& primes) {
    assert(n <= primes.max);
    return primes.s.contains(n);
}

QList<s64> divisors(s64 n) {
    QList<s64> ret;
    for (s64 i = 1; i <= n; i += 1) {
        if (n % i == 0) {
            ret << i;
        }
    }
    return ret;
}

QList<s64> primeFactors(s64 n, Primes* P) {
    QList<s64> ret;

    //updatePrimes(n, P); // we do that manually somewhere else

    int i = 0;
    while (i < P->l.size() && P->l[i] <= n) {
        auto p = P->l[i];
        if (n % p == 0) {
            ret << p;
            while (n % p == 0) {
                n /= p;
            }
        }
        i += 1;
    }

    if (n > 1) {
        ret << n;
    }

    return ret;
}

void testDivisors();
void testPrimeFactors();
void test1();

int main() {

    testDivisors();
    testPrimeFactors();

    test1();

    return 0;
}

void testDivisors() {
    assert(divisors( 1) == QList<s64>({1}));
    assert(divisors( 2) == QList<s64>({1, 2}));
    assert(divisors( 3) == QList<s64>({1, 3}));
    assert(divisors( 6) == QList<s64>({1, 2, 3, 6}));
    assert(divisors(13) == QList<s64>({1, 13}));
    assert(divisors(28) == QList<s64>({1, 2, 4, 7, 14, 28}));
    assert(divisors(29) == QList<s64>({1, 29}));
}

void testPrimeFactors() {
    auto P = initPrimes();
    updatePrimes(30, &P);
    assert(primeFactors( 1, &P) == QList<s64>({}));
    assert(primeFactors( 2, &P) == QList<s64>({2}));
    assert(primeFactors( 3, &P) == QList<s64>({3}));
    assert(primeFactors( 6, &P) == QList<s64>({2, 3}));
    assert(primeFactors(13, &P) == QList<s64>({13}));
    assert(primeFactors(28, &P) == QList<s64>({2, 7}));
    assert(primeFactors(29, &P) == QList<s64>({29}));
    assert(primeFactors(30, &P) == QList<s64>({2, 3, 5}));
}

void test1() {

    s64 maxN = 1000;
    s64 sum = 0;

    auto P = initPrimes();

    QTime t; t.start();

    updatePrimes(maxN + 1, &P);

    qDebug() << QString("calculating primes up to %1 took %2 seconds.").arg(maxN + 1).arg(t.elapsed() / 1000.0);
    // calculating primes up to  1,000,001 took 0.318 seconds.
    // calculating primes up to 10,000,001 took 5.515 seconds.

    foreach (s64 p, P.l) {

        // Observation 2: n is always a prime minus one, because  n / d + d has to prime, in particular n / 1 + 1 is a prime

        s64 n = p - 1;


        // Observation 1: We do not need to consider all divisors of n, because:
        //
        // x = d + n / d
        // n = d_1 * d_2
        //
        // ? = d_2 + n / d_2 ??? | replace d_2 with n / d_1
        //   = d_1 + n / d_1 = x
        //
        // Because every d_1 * d_2 can be expressed as a prime or 1 times something else, >> we need only consider prime factors of n <<

        auto divs = primeFactors(n, &P); // note: we need not include 1, because by iterating over n that are a prime minus 1, this condition is already fulfilled
        //auto divs = divisors(n);

        bool allPrime = true;
        foreach (s64 d, divs) {
            if (isPrime(d + n / d, P) == false) {
                allPrime = false;
                break;
            } else {
                //qDebug() << "  " << n << ": " << d << "+" << n << "/" << d << "=" << d + n / d;
            }
        }

        if (allPrime) {
            sum += n;
            qDebug() << "n" << n << ", sum" << sum;
        }
    }
}
