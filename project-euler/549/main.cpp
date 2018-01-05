#include "../lib.hpp"

s64 s(const QMap<s64, s64>& factors) {

    s64 maxM = 0;

    QMapIterator<s64, s64> i(factors);
    while (i.hasNext()) {
        i.next();

        const s64 factor = i.key();
        s64 factorCount  = i.value();

        s64 m = factor;

        while (true) {
            s64 m2 = m;
            while (m2 % factor == 0) {
                m2 /= factor;
                factorCount -= 1;

                if (factorCount == 0) {
                    break;
                }
            }

            if (factorCount == 0) {
                break;
            } else {
                m += factor;
            }

        }

        maxM = std::max(m, maxM);
    }

    return maxM;
}

s64 s(s64 n, const QVector<s64>& primes) {
    return s(primeFactors(n, primes));
}

s64 S(s64 n, const QVector<s64>& primes) {

    s64 sum = 0;
    for (s64 i = 2; i <= n; i += 1) {
        sum += s(i, primes);
    }
    //qDebug() << QString("S(%1) = %2").arg(n, 4).arg(sum, 4);
    return sum;
}

void test_s();
void test_S();
void test1();

int main(int argc, char **args) {
    (void) argc; (void) args;

    test_s();
    test_S();
    test1();

    return 0;
}

void test_s() {
    QVector<s64> primes;
    primesToAtLeast(25, &primes);

    assert(s(10, primes) ==  5);
    assert(s(25, primes) == 10);

}

void test_S() {
    QVector<s64> primes;
    primesToAtLeast(100, &primes);

    assert(S(100, primes) == 2012); // wrong
}

void test1() {
    //s64 n = 100; 793183093
    s64 n = 100 * 1000 * 1000;

    QVector<s64> primes;
    primesToAtLeast(n, &primes);

    std::function<s64(s64, int, QMap<s64, s64>*)> recurse = [primes, n, &recurse](s64 i, int primeIndex, QMap<s64, s64>* factors) -> s64 {

        s64 p = primes[primeIndex];
        i *= p;

        s64 ret = 0;

        if (factors->contains(p)) { (*factors)[p] += 1; }
        else                      { (*factors)[p]  = 1; }

        const s64 s_ = s(*factors);
        ret += s_;

        //qDebug() << QString("4 s(%1) = %2").arg(i, 4).arg(s_, 4);

        for(int j = primeIndex; j < primes.size(); j += 1) {
            if (i*primes[j] > n) { break; }
            ret += recurse(i, j, factors);
        }

        if ((*factors)[p] == 1) {
            factors->remove(p);
        } else {
            (*factors)[p] -= 1;
        }

        return ret;
    };

    QMap<s64, s64> factors;
    s64 sum = 0;
    for(int j = 0; j < primes.size(); j += 1) {
        if (primes[j] > n) { break; }

        sum += recurse(1, j, &factors);
    }

    qDebug() << QString("2 S(%1) = %2").arg(n, 4).arg(sum, 4);
}
