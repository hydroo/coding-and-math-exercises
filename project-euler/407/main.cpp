#include "../lib.hpp"

using namespace std;

void test1();
void test2();

int main(int argc, char **args) {
    (void) argc; (void) args;

    //test1();
    test2();

    return 0;
}

s64 M(s64 n) {
    for (s64 a = n - 1; a > 0; a -= 1) {
        //cerr << a << ":" << a*a % n << ", ";
        if (a*a % n == a) {
            //cerr << endl;
            return a;
        }
    }

    return 0;  // happens only for n == 1
}

void test1() {

    const s64 max = 100;
    const int printWidth = (int) ceil(log10(max + 1));

    s64 sum = 0;

    for (s64 n = 1; n <= max; n += 1) {

        const s64 a  = M(n);

        sum += a;

        qDebug() << QString("M(%1) = %2, sum %4").arg(n, printWidth, 10).arg(a, printWidth).arg(sum, 2*printWidth);
    }

    qDebug() << "Sum" << sum;

}

void test2() {

    const s64 max = 10 * 1000 * 1000;
    const int printWidth = (int) ceil(log10(max + 1));

    QVector<s64> primes = primesTo(max);

    // builds all numbers from 2 to max
    std::function<s64(s64, int, QMap<s64, s64>*)> recurse = [primes, printWidth, &recurse](s64 i, int primeIndex, QMap<s64, s64>* factors) -> s64 {

        const s64 p = primes[primeIndex];
        i *= p;

        s64 sum = 0;

        if (factors->contains(p)) { (*factors)[p] += 1; }
        else                      { (*factors)[p]  = 1; }

        QVector<s64> pks;
        QMapIterator<s64, s64> j(*factors);
        while (j.hasNext()) {
            j.next();

            pks << std::pow(j.key(), j.value());
        }

        // forms d1 * d2 = i, with gcd(d1, d2) = 1 and finds the largest m such that m*m == m mod i
        std::function<s64(const QVector<s64>&)> recurse2 = [&recurse2, i](const QVector<s64>& f) {

            if (f.size() == 2) {

                s64 a = f[0];
                s64 b = f[1];
                s64 amul;
                if (a > b) { std::swap(a, b); }
                extendedGcd(a, b, &amul, nullptr);

                s64 m1 = a*amul;
                s64 m2 = i - m1 + 1;

                if (m1 < 0) { m1 += i; }
                if (m2 < 0) { m2 += i; }

                if (m1 < m2) { std::swap(m1, m2); }

                if      (m1*m1 % i == m1) { return m1; }
                else if (m2*m2 % i == m2) { return m2; }
                else                      { return (s64) 0;  }

            } else {

                s64 m = 0;

                for (int j = 0; j < f.size(); j += 1) {
                    for (int k = j + 1; k < f.size(); k += 1) {

                        QVector<s64> newF = f;
                        newF[k] = newF[k]*newF[j];
                        newF.remove(j);

                        m = std::max(m, recurse2(newF));
                    }
                }

                return m;
            }
        };

        s64 m2;
        if (pks.size() == 1) {
            m2 = 1;
        } else {
            m2 = recurse2(pks);
        }

        sum += m2;

        // const s64 m1 = M(i);

        //qDebug().noquote() << QString("M(%1) = %2 %3 %4     Factors of %1:").arg(i, printWidth, 10, QChar('0')).arg(m1, printWidth).arg(m2, printWidth).arg(m1 == m2 ? "   " : "!!!") << *factors;

        //assert(m1 == m2);

        for(int j = primeIndex; j < primes.size(); j += 1) {
            if (i*primes[j] > max) { break; }
            sum += recurse(i, j, factors);
        }

        if ((*factors)[p] == 1) {
            factors->remove(p);
        } else {
            (*factors)[p] -= 1;
        }

        return sum;
    };

    QMap<s64, s64> factors;
    s64 sum = 0; // for M(1) = 0
    for(int j = 0; j < primes.size(); j += 1) {
        if (primes[j] > max) { break; }

        sum += recurse(1, j, &factors);
    }

    // // QVector<QPair<s64, s64>> pq{{2, 3}, {2, 5}, {2, 7}, {2, 11}, {2, 13}, {3, 5}, {3, 7}, {3, 11}, {3, 13}, {5, 7}, {5, 11}, {5, 13}, {7, 11}, {7, 13}};
    // // QVector<QPair<s64, s64>> pq{{2, 9}, {2, 25}, {2, 49}, {2, 121},  {3, 25}, {3, 49}, {3, 121}, {5, 49}, {5, 121}, {7, 121}};
    // // QVector<QPair<s64, s64>> pq{{4, 9}, {4, 25}, {4, 49}, {4, 121},  {9, 25}, {9, 49}, {9, 121}, {25, 49}, {25, 121}, {49, 121}};
    // QVector<QPair<s64, s64>> pq{{5, 6}, {6, 7}, {6, 11}, {5, 14},  {7, 22}, {7, 15}, {11, 21}, {7, 55}};
    // foreach (auto a, pq) {
    //     s64 p = a.first;
    //     s64 q = a.second;
    //     s64 pmul;

    //     extendedGcd(p, q, &pmul, nullptr);
    //     if (pmul < 0) { pmul += q; }
    //     qDebug().noquote() << QString("p %1, %2, p^-1 = %3 mod q, M(%4) = %5       %6   %7").arg(p, 3).arg(q, 3).arg(pmul, 3).arg(p*q, 3).arg(M(p*q), 3).arg(p*pmul, 3).arg(p*q - (p*pmul-1), 3);
    // }

    qDebug().noquote() << QString("Sum %1").arg(sum);
}

