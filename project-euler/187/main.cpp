#include <cassert>
#include <cmath>

#include <algorithm>

#include <QtDebug>

using s64 = int64_t;

using namespace std;

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

void test1();
void test2();
void doIt();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    test1();
    test2();
    doIt();

    return 0;
}

void test1() {
    QVector<s64> primes;
    primesToAtLeast(20, &primes);
    assert(primes.size() == 9);
    assert(primes.contains(2));
    assert(primes.contains(3));
    assert(primes.contains(5));
    assert(primes.contains(7));
    assert(primes.contains(11));
    assert(primes.contains(13));
    assert(primes.contains(17));
    assert(primes.contains(19));
    assert(primes.contains(23));
}

void test2() {
    QVector<s64> primes;
    primesToAtLeast(10000000, &primes);
}

void doIt() {

    s64 max = 100 * 1000 * 1000;

    qDebug() << "Max:" << max;

    QVector<s64> primes;
    primesToAtLeast(max, &primes);

    qDebug() << "Primes calculated:" << primes.size(); // << primes;

    s64 solution = 0;

    for (auto i = begin(primes); i != end(primes); ++i) {
        s64 n = max / *i;

        auto j = upper_bound(begin(primes), end(primes), n);
        --j;

        auto dist = distance(i,j) + 1 >= 0 ? distance(i,j) + 1 : 0;

        //qDebug() << distance(begin(primes), i) << *i << "max" << n << "lower" << *j << "distance" <<  dist;

        solution += dist;
    }

    qDebug() << solution;
}
