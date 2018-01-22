#include <cassert>
#include <cmath>

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>

#include <gmpxx.h>

#include <QBitArray>
#include <QVector>

#include <QtDebug>

using u8  = uint8_t;
using s64 = int64_t;
using u64 = uint64_t;

using f64 = double;

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

    qDebug().noquote() << QString("%1 is deprecated. Use primesTo() instead.").arg(__func__);

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

QVector<s64> primesTo(s64 n, QBitArray* bits = nullptr) {

    QVector<s64> primes;

    QBitArray bits_;
    if (bits == nullptr) {
        bits = &bits_;
    }
    *bits = QBitArray(n, true);

    for (int i = 2; i < bits->size(); i += 1) {
        if (bits->at(i) == true) {
            primes.append(i);
            for (int j = i+i; j < bits->size(); j += i) {
                bits->setBit(j, false);
            }
        }
    }

    return primes;
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

s64 extendedGcd(s64 a, s64 b, s64 *amul, s64 *bmul) {

    s64 amul_, bmul_;
    if (amul == nullptr) {
        amul = &amul_;
    }
    if (bmul == nullptr) {
        bmul = &bmul_;
    }

    if (a > b) {
        std::swap(a, b);
        std::swap(amul, bmul);
    }

    std::function<s64(s64, s64, s64*, s64*)> recurse = [&recurse](s64 a, s64 b, s64 *amul, s64 *bmul) -> s64 {

        if (b % a == 0) {
            *bmul = 0;
            *amul = 1;
            return a;
        }

        s64 ret = recurse(b % a, a, amul, bmul);

        s64 t = *bmul;
        *bmul = *amul;
        *amul = t + *amul * -(b/a);

        return ret;
    };

    return recurse(a, b, amul, bmul);
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

template<typename T, size_t length>
QDebug operator<<(QDebug d, const std::array<T, length>& a) {
    d.nospace();
    d.noquote();

    d << '[';
    for (int i = 0; i < ((int)length) - 1; i += 1) {
        d << a[i] << ", ";
    }
    if (a.size() > 0) {
        d << a.back();
    }
    d << ']';

    return d.resetFormat();
}

template<>
QDebug operator<<(QDebug d, const std::vector<bool>& v) {
    d.nospace();
    d.noquote();

    d << '[';
    for (int i = 0; i < ((int)v.size()) - 1; i += 1) {
        d << (v[i] == true ? 1 : 0);
    }
    if (v.size() > 0) {
        d << (v.back() == true ? 1 : 0);
    }
    d << ']';

    return d.resetFormat();
}
