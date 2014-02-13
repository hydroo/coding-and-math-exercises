#include <cassert>
#include <cmath>
#include <cstdlib>

#include <QList>
#include <QSet>
#include <QtDebug>
#include <QtGlobal>
#include <QVector>

/* *** helpers ***************************************************************/
struct Primes {
    qint64 max;
    QSet<qint64> s; // quick lookup
    QList<qint64> l; // sorted
};

static Primes* newPrimes() {
    Primes *ret = new Primes;
    ret->max = 2;
    return ret;
}

static void deletePrimes(Primes *primes) {
    delete primes;
}

static void updatePrimes(qint64 n, Primes *primes) {
    if (n < primes->max) return;

    for (qint64 i = primes->max; i <= n; i += 1) {
        bool p = true;
        for (int j = 0; j < primes->l.size(); j += 1) {
            if (i % primes->l[j] == 0) {
                p = false;
                break;
            }
        }
        if (p == true) {
            primes->s.insert(i);
            primes->l.append(i);
        }
    }

    primes->max = n;
}

static bool isPrime(qint64 n, const Primes& primes) {
    Q_ASSERT(n <= primes.max);
    return primes.s.contains(n);
}

/* *** ring ******************************************************************/
static int ring(qint64 n) {
    Q_ASSERT(n > 1);
    qint64 x = (n-2) / 6; // partition things into buckets of 6, ignoring n < 2
    return -0.5 + sqrt(0.25 + 2*x) + 1; // solution to the equation n = (1+x)*(x/2)
}

// starts with 0, not with 2
static qint64 ringOffset(int r) {
    Q_ASSERT(r > 0);
    return 6*((1+(r-1))*((r-1)/2.0));
}

static qint64 positionInRing(qint64 n) {
    Q_ASSERT(n > 1);
    return n - ringOffset(ring(n)) - 2;
}

static qint64 modInRing(qint64 n, int r) {
    return (((n - ringOffset(r) - 2) + 6*r) % (6*r)) + ringOffset(r) + 2;
}

static QSet<qint64> neighbors(qint64 n) {
    Q_ASSERT(n > 7);

    QSet<qint64> b;

    int r  = ring(n);
    qint64 p  = positionInRing(n);

    int corner = p / r; // 0 = top, counterclockwise
    qint64 offsetFromCorner = p % r; //counterclockwise

    qint64 o = ringOffset(r+1) + 2 + corner*(r+1) + offsetFromCorner; // outer neighbor
    qint64 i = ringOffset(r-1) + 2 + corner*(r-1) + offsetFromCorner; // inner neighbor

    if (p == 0) { // top corner
        b.insert(          o          );
        b.insert(          o + 1      );
        b.insert(modInRing(o - 1, r+1));
        b.insert(modInRing(n - 1, r  ));
        b.insert(          i          );
        //b.insert(n + 1); // diff = 1 -> not prime
    } else if (p == r*6 - 1) { // right to the top corner
        b.insert(          o          );
        b.insert(          o + 1      );
        b.insert(          i - 1      );
        b.insert(modInRing(n + 1, r  ));
        b.insert(modInRing(i    , r-1));
        //b.insert(n - 1); // diff = 1 -> not prime
    }

    return b;
}

static bool hasThreePrimeDifferences(qint64 n, Primes *primes) {
    Q_ASSERT(n > 7);

    qint64 maxDiff = (ring(n))*6 + (ring(n)+1)*6 - 1; // exact

    updatePrimes(maxDiff, primes);

    const QSet<qint64> b = neighbors(n);
    int primeCount = 0;
    foreach(qint64 i, b) {
        qint64 diff = llabs(i - n);
        Q_ASSERT(diff <= maxDiff);
        primeCount += isPrime(diff, *primes) == true ? 1 : 0;
    }
    return primeCount == 3;
}

/* *** tests *****************************************************************/
static void test1() {
    assert(ring(2)  == 1);
    assert(ring(7)  == 1);
    assert(ring(8)  == 2);
    assert(ring(19) == 2);
    assert(ring(20) == 3);
    assert(ring(37) == 3);
    assert(ring(38) == 4);

    assert(positionInRing(2)  == 0 );
    assert(positionInRing(3)  == 1 );
    assert(positionInRing(4)  == 2 );
    assert(positionInRing(5)  == 3 );
    assert(positionInRing(6)  == 4 );
    assert(positionInRing(7)  == 5 );
    assert(positionInRing(8)  == 0 );
    assert(positionInRing(9)  == 1 );
    assert(positionInRing(12) == 4 );
    assert(positionInRing(13) == 5 );
    assert(positionInRing(19) == 11);
    assert(positionInRing(20) == 0 );
    assert(positionInRing(27) == 7 );
    assert(positionInRing(32) == 12);
    assert(positionInRing(37) == 17);
    assert(positionInRing(38) == 0 );

    assert(neighbors(8 ) == QSet<qint64>::fromList(QList<qint64>::fromVector(QVector<qint64>::fromStdVector({20, 21,  2, 19, 37}))));
    assert(neighbors(20) == QSet<qint64>::fromList(QList<qint64>::fromVector(QVector<qint64>::fromStdVector({38, 39,  8, 37, 61}))));
    assert(neighbors(37) == QSet<qint64>::fromList(QList<qint64>::fromVector(QVector<qint64>::fromStdVector({61, 20,  8, 19, 60}))));

    Primes *primes = newPrimes();

    assert(hasThreePrimeDifferences(8  , primes) == true);
    assert(hasThreePrimeDifferences(271, primes) == true);

    int count = 2;
    for (int n = 8; n < 300; n += 1) {
        if (hasThreePrimeDifferences(n, primes)) {
            count += 1;
            if (count == 10) {
                assert(n == 271);
                break;
            }
        }
    }
    assert(count == 10);

    deletePrimes(primes);
}

/* *** main ******************************************************************/
int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    test1();

    Primes *primes = newPrimes();

    int    count = 2;
    qint64 top   = 8;
    qint64 right = 19;
    int    r     = 2;
    for (; top < 20000000000LL;) {
        if (hasThreePrimeDifferences(top, primes)) {
            count += 1;
            qDebug() << count << top;
        }
        if (hasThreePrimeDifferences(right, primes)) {
            count += 1;
            qDebug() << count << right;
        }

        top   += 6*r;
        right += 6*(r+1);
        r     += 1;
    }

    deletePrimes(primes);

    return 0;
}
