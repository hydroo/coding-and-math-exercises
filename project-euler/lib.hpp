#include <cassert>
#include <cmath>

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>

#include <gmpxx.h>

#include <QVector>

#include <QtDebug>

using u8  = uint8_t;
using s64 = int64_t;
using u64 = uint64_t;

using namespace std;

bool isPrime(s64 n) {
    if (n == 2) {
        return true;
    } else if (n % 2 == 0 || n == 1) {
        return false;
    }
    s64 sqrtn = (s64) floor(sqrt(n));
    for (s64 d = 3; d <= sqrtn; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

void primesToAtLeast(s64 n, QVector<s64> *primes) {
    *primes = {2, 3};
    auto newPrime = primes->last() + 2;
    auto newPrimeSqrt = floor(sqrt(newPrime));

    while (true) {
        bool isPrime = true;
        foreach (s64 p, *primes) {
            if (p > newPrimeSqrt) break;
            if (newPrime % p == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime == true) {
            primes->append(newPrime);
            if (newPrime < n) {
                newPrime += 2;
                newPrimeSqrt = floor(sqrt(newPrime));
                continue;
            } else {
                break;
            }
        } else {
            newPrime += 2;
            newPrimeSqrt = floor(sqrt(newPrime));
            continue;
        }
    }
}

bool isPrime(s64 n, const QVector<s64>& primes) {
    s64 sqrtn = (s64) floor(sqrt(n));
    assert(sqrtn <= primes.last());
    for (int i = 0; i < primes.size(); i += 1) {
        if (primes[i] > sqrtn) { break; }
        if (n % primes[i] == 0) { return false; }
    }
    return true;
}

QMap<s64, s64> primeFactors(s64 n, const QVector<s64>& primes) {
    assert(n <= primes.last());
    QMap<s64, s64> factors;
    for (int i = 0; i < primes.size(); i += 1) {
        if (primes[i] > n) { break; }

        s64 f = primes[i];
        if (n % f == 0) {
            factors[f] = 0;
            while (n % f == 0) {
                n /= f;
                factors[f] += 1;
            }
        }
    }
    return factors;
}

s64 gcd(s64 a, s64 b) {
    s64 t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

s64 factorial(s64 n) {
    s64 f = 1;
    for (s64 i = 1; i <= n; i += 1) {
        f = f * i;
    }
    return f;
}

QDebug operator<<(QDebug d, const mpz_class& a) {
    d.nospace();
    d.noquote();
    stringstream s;
    s << a;
    d << QString::fromStdString(s.str());
    return d.resetFormat();
}

QDebug operator<<(QDebug d, const mpf_class& f) {
    d.nospace();
    d.noquote();
    stringstream s;
    s << f;
    d << QString::fromStdString(s.str());
    return d.resetFormat();
}
