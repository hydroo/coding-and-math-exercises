#include "../lib.hpp"

using namespace std;

void test1();
void testEratostenes();

int main(int argc, char **args) {
    (void) argc; (void) args;

    test1();
    //testEratostenes();

    return 0;
}

void test1() {
    // const s64 max = 100;
    const s64 max = 100 * 1000 * 1000;
    const int printWidth = (int) ceil(log10(max));

    QBitArray primeBits;
    QVector<s64> primes = primesTo(max, &primeBits);
    const int primesCount = primes.size();

    s64 sum = 0;

    for (int i = 0; i < primesCount; i += 1) {
        const s64 p = primes[i];

        s64 d = 1;
        for (s64 dTmp = 1; dTmp*dTmp <= p+1; dTmp += 1) {
            if ((p+1) % (dTmp*dTmp) == 0) {
                d = dTmp;
            }
        }

        const s64 qd = (p+1) / d;
        const s64 rd = qd    / d;

        s64 nLe = (s64) ceil(d*sqrt((double) (max+1) / (double) (p+1)));

        for (s64 n = d+1; n < nLe; n += 1) {

            const s64 q = qd * n     - 1;
            const s64 r = rd * n * n - 1;

            if (primeBits.at(q) == true && primeBits.at(r) == true) {
                sum += p + q + r;
                qDebug() << QString("(%1, %2, %3), sum %4").arg(p, printWidth).arg(q, printWidth).arg(r, printWidth).arg(sum, printWidth*2);
            }

        }

    }

    qDebug() << "Sum" << sum;
}

void testEratostenes() {

    const s64 max = 100 * 1000 * 1000;

    QVector<s64> primes = primesTo(max);

    QBitArray bits;
    QVector<s64> primes2 = primesTo(max, &bits);

    (void) primes;
    (void) primes2;
    (void) bits;

    //qDebug() << primes2;
    //qDebug() << bits;

    //qDebug() << primes;
}
