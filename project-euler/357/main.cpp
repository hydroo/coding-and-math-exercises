#include <cassert>
#include <cmath>

#include <QtDebug>
#include <QTime>

using s64 = int64_t;

s64 squareRootFloor(s64 nn) {
    return (s64) floor(sqrt(nn));
}

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

QList<s64> selectedDivisors(s64 n) {
    QList<s64> ret;

    s64 maxDiv = squareRootFloor(n);

    for (s64 i = 3; i <= maxDiv; i += 1) {
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
void testSelectedDivisors();
void testPrimeFactors();
void bug1();
void test1();
void test2();

int main() {

    testDivisors();
    testSelectedDivisors();
    testPrimeFactors();

    //bug1();

    //test1();
    test2();

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

void testSelectedDivisors() {
    assert(selectedDivisors(   1) == QList<s64>({}));
    assert(selectedDivisors(   2) == QList<s64>({}));
    assert(selectedDivisors(   3) == QList<s64>({}));
    assert(selectedDivisors(   6) == QList<s64>({}));
    assert(selectedDivisors(  13) == QList<s64>({}));
    assert(selectedDivisors(  28) == QList<s64>({4}));
    assert(selectedDivisors(  29) == QList<s64>({}));
    assert(selectedDivisors(1810) == QList<s64>({5, 10}));
    assert(selectedDivisors(1870) == QList<s64>({5, 10, 11, 17, 22, 34}));
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

void bug1() {

    s64 n = 1290;

    auto P = initPrimes();
    updatePrimes(n + 1, &P);

    auto divs = divisors(n);
    qDebug() << "divisors:" << divs;
    foreach (s64 d, divs) {
        if (isPrime(d + n / d, P)) {
            qDebug() << "  " << n << ": " << d << "+" << n << "/" << d << "=" << d + n / d << "prime";
        } else {
            qDebug() << "  " << n << ": " << d << "+" << n << "/" << d << "=" << d + n / d << "no prime";
        }
    }

    auto prims = primeFactors(n, &P);
    qDebug() << "prime factors:" << prims;
    foreach (s64 d, prims) {
        if (isPrime(d + n / d, P)) {
            qDebug() << "  " << n << ": " << d << "+" << n << "/" << d << "=" << d + n / d << "prime";
        } else {
            qDebug() << "  " << n << ": " << d << "+" << n << "/" << d << "=" << d + n / d << "no prime";
        }
    }

}

void test1() {

    s64 maxN = 10000;
    s64 sum = 3; // the property holds for 1 and 2, and we want to skip both, because of later assertions that only for n > 2

    auto P = initPrimes();

    QTime t; t.start();

    updatePrimes(maxN + 1, &P);

    qDebug() << QString("calculating primes up to %1 took %2 seconds.").arg(maxN + 1).arg(t.elapsed() / 1000.0);
    // calculating primes up to   1,000,001 took 0.318 seconds.
    // calculating primes up to  10,000,001 took 5.515 seconds.
    // calculating primes up to 100,000,001 took 120.062 seconds.

    for (int i = 2; i < P.l.size(); i += 1) {
        const s64 p = P.l[i];

        // Observation 2: n is always a prime minus one, because  n / d + d has to prime, in particular n / 1 + 1 is a prime

        s64 n = p - 1;

        if (isPrime((n >> 1 /*div 2*/) + 2, P) == false) { continue; } // every p minus 1 is even, therefore this condition has to hold for every n

        // Observation 1 (Wrong): We do not need to consider all divisors of n (yes), because:
        //
        // (yes:)
        // x = d + n / d
        // n = d_1 * d_2
        //
        // ? = d_2 + n / d_2 ??? | replace d_2 with n / d_1
        //   = d_1 + n / d_1 = x
        //
        // (no:) Because every d_1 * d_2 can be expressed as a prime or 1 times something else, >> we need only consider prime factors of n <<
        // (corrected:) you can skip every divisor where the other "half" is included. Therefore, half of all divisors can be excluded. (Primes do not work, because look at n = 1290 (bug1())
        //auto divs = primeFactors(n, &P); // note: we need not include 1, because by iterating over n that are a prime minus 1, this condition is already fulfilled
        auto divs = divisors(n);

        //assert(divs.first() == 1);
        //assert(divs.last()  == n);
        divs.removeFirst(); // we already checked for 1
        divs.removeLast();  // we already checked for 1, and don't need to check for n

        //assert(divs.first() == 2);
        //assert(divs.last()  == n / 2);
        divs.removeFirst(); // we already checked for 2
        divs.removeLast();  // we already checked for 2, and don't need to check for n

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
            //qDebug() << "n" << n << ", divisors" << divs;
        }
    }
}
// n 1318 , sum 13287  is correct
// n 9718 , sum 262615 is correct, too

// same as test1, except we use selectedDivisors and have less comments
void test2() {

    s64 maxN = 100000000;
    s64 sum = 3; // the property holds for 1 and 2, and we want to skip both, because of later assertions that only for n > 2

    auto P = initPrimes();

    QTime t; t.start();

    updatePrimes(maxN + 1, &P);

    qDebug() << QString("calculating primes up to %1 took %2 seconds.").arg(maxN + 1).arg(t.elapsed() / 1000.0);

    for (int i = 2; i < P.l.size(); i += 1) {
        const s64 p = P.l[i];
        const s64 n = p - 1;

        if (isPrime((n >> 1 /*div 2*/) + 2, P) == false) { continue; }

        auto divs = selectedDivisors(n);

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
            //qDebug() << "n" << n << ", divisors" << divs;
        }
    }

    qDebug() << "solution:" << sum;
}
