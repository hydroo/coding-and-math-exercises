#include <cassert>
#include <cmath>

#include <QVector>

#include <QtDebug>

using s64 = int64_t;

using namespace std;

bool isPrime(s64 n) {
    if (n == 2) {
        return true;
    } else if (n % 2 == 0 || n == 1) {
        return false;
    }
    s64 sqrtn = floor(sqrt(n));
    for (s64 d = 3; d <= sqrtn; d += 2) {
        if (n % 3 == 0) {
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
