#include "../lib.hpp"

s64 hammingNumberCount(s64 max, s64 type) {
    QVector<s64> primes;
    primesToAtLeast(type, &primes);

    //qDebug() << primes;

    // wow, that api is shit
    primes.erase(
        remove_if(begin(primes), end(primes), [type](s64 i) { return i > type; }),
        end(primes)
    );

    //qDebug() << primes;

    s64 count = 0;
    s64 printSomething = 1000*1000;

    for (s64 i = 1; i <= max; i += 1) {
        s64 j = i;
        foreach (auto p, primes) {
            while (j % p == 0) {
                j /= p;
            }
        }

        if (j == 1) {

            if (i > printSomething) {
                qDebug() << i;
                printSomething += 1000 *1000;
            }

            count += 1;
        }
    }

    return count;
}

void test1();

int main() {

    test1();

    return 0;
}

void test1() {
    //qDebug() << "15"   << hammingNumberCount(15, 5);
    //qDebug() << "10^3" << hammingNumberCount(1000, 5);
    //qDebug() << "10^4" << hammingNumberCount(10*1000, 5);
    //qDebug() << "10^5" << hammingNumberCount(100*1000, 5);
    //qDebug() << "10^6" << hammingNumberCount(1000*1000, 5);
    //qDebug() << "10^7" << hammingNumberCount(10*1000*1000, 5);
    //qDebug() << "10^8" << hammingNumberCount(100*1000*1000, 5);
    qDebug() << "10^9" << hammingNumberCount(1000*1000*1000, 100);
}
