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
    int max;
    QSet<int> s; // quick lookup
    QList<int> l; // sorted
};

Primes* newPrimes() {
    Primes *ret = new Primes;
    ret->max = 2;
    return ret;
}

void deletePrimes(Primes *primes) {
    delete primes;
}

static void updatePrimes(int n, Primes *primes) {
    if (n < primes->max) return;

    for (int i = primes->max; i <= n; i += 1) {
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

static bool isPrime(int n, const Primes& primes) {
    Q_ASSERT(n <= primes.max);
    return primes.s.contains(n);
}

/* *** ring ******************************************************************/
static int ring(int n) {
    Q_ASSERT(n > 1);
    int x = (n-2) / 6; // partition things into buckets of 6, ignoring n < 2
    return -0.5 + sqrt(0.25 + 2*x) + 1; // solution to the equation n = (1+x)*(x/2)
}

// starts with 0, not with 2
static int ringOffset(int r) {
    Q_ASSERT(r > 0);
    return 6*((1+(r-1))*((r-1)/2.0));
}

static int positionInRing(int n) {
    Q_ASSERT(n > 1);
    return n - ringOffset(ring(n)) - 2;
}

static int modInRing(int n, int r) {
    return (((n - ringOffset(r) - 2) + 6*r) % (6*r)) + ringOffset(r) + 2;
}

static QSet<int> neighbors(int n) {
    Q_ASSERT(n > 7);

    QSet<int> b;

    int r  = ring(n);
    int p  = positionInRing(n);

    int corner = p / r; // 0 = top, counterclockwise
    int offsetFromCorner = p % r; //counterclockwise

    int o = ringOffset(r+1) + 2 + corner*(r+1) + offsetFromCorner; // outer neighbor
    int i = ringOffset(r-1) + 2 + corner*(r-1) + offsetFromCorner; // inner neighbor

    if (offsetFromCorner == 0) { // corner
        b.insert(o    );
        b.insert(o + 1);
        //b.insert(n + 1); // diff = 1 -> not prime
        b.insert(i    );
        if (corner == 0) {
            b.insert(modInRing(o - 1, r+1));
            b.insert(modInRing(n - 1, r  ));
        } else {
            b.insert(o - 1);
            //b.insert(n - 1); // diff = 1 -> not prime
        }
    } else { // side
        b.insert(o    );
        b.insert(o + 1);
        //b.insert(n - 1); // diff = 1 -> not prime
        b.insert(i - 1);
        if (corner == 5 && offsetFromCorner == r-1) {
            b.insert(modInRing(n + 1, r  ));
            b.insert(modInRing(i    , r-1));
        } else {
            //b.insert(n + 1); // diff = 1 -> not prime
            b.insert(i);
        }
    }

    return b;
}

static bool hasThreePrimeDifferences(int n, Primes *primes) {
    Q_ASSERT(n > 7);

    int maxDiff = (ring(n))*6 + (ring(n)+1)*6 - 1; // exact

    updatePrimes(maxDiff, primes);

    const QSet<int> b = neighbors(n);
    int primeCount = 0;
    foreach(int i, b) {
        int diff = abs(i - n);
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

    assert(neighbors(8 ) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({20, 21,      2, 19, 37})))); // TopCorner
    assert(neighbors(20) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({38, 39,      8, 37, 61}))));
    assert(neighbors( 9) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({21, 22,      3,  2    })))); // TopLeftSide
    assert(neighbors(21) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({39, 40,      9,  8    }))));
    assert(neighbors(22) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({40, 41,     10,  9    }))));
    assert(neighbors(10) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({22, 23, 24,      3    })))); // TopLeftCorner
    assert(neighbors(23) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({41, 42, 43,     10    }))));
    assert(neighbors(11) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    24, 25,      4,  3})))); // LeftSide
    assert(neighbors(24) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    43, 44,     11, 10}))));
    assert(neighbors(25) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    44, 45,     12, 11}))));
    assert(neighbors(12) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    25, 26, 27,      4})))); // BottomLeftCorner
    assert(neighbors(26) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    45, 46, 47,     12}))));
    assert(neighbors(13) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({ 4,     27, 28,      5})))); // BottomLeftSide
    assert(neighbors(27) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({12,     47, 48,     13}))));
    assert(neighbors(28) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({13,     48, 49,     14}))));
    assert(neighbors(14) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({ 5,     28, 29, 30    })))); // BottomCorner
    assert(neighbors(29) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({14,     49, 50, 51    }))));
    assert(neighbors(15) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({ 6,  5,     30, 31    })))); // BottomRightSide
    assert(neighbors(30) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({15, 14,     51, 52    }))));
    assert(neighbors(31) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({16, 15,     52, 53    }))));
    assert(neighbors(16) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({     6,     31, 32, 33})))); // BottomRightCorner
    assert(neighbors(32) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    16,     53, 54, 55}))));
    assert(neighbors(17) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({     7,  6,     33, 34})))); // RightSide
    assert(neighbors(33) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    17, 16,     55, 56}))));
    assert(neighbors(34) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({    18, 17,     56, 57}))));
    assert(neighbors(18) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({36,      7,     34, 35})))); // TopRightCorner
    assert(neighbors(35) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({59,     18,     57, 58}))));
    assert(neighbors(19) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({37,  8,  2,  7,     36})))); // TopRightSide
    assert(neighbors(36) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({60,     19, 18,     59}))));
    assert(neighbors(37) == QSet<int>::fromList(QList<int>::fromVector(QVector<int>::fromStdVector({61, 20,  8, 19,     60}))));

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

    int count = 2;
    for (int n = 8; n < 100000000; n += 1) {
        if (hasThreePrimeDifferences(n, primes)) {
            count += 1;

            int r = ring(n);
            int corner = positionInRing(n) / r;
            int offsetFromCorner = positionInRing(n) % r;

            qDebug() << count << n << ((offsetFromCorner == 0 && corner == 0) || (corner == 5 && offsetFromCorner == r-1));
        }
    }

    deletePrimes(primes);

    return 0;
}
