#include "../lib.hpp"

using namespace std;

void test1();
void test2();

void testNchooseK();

int main(int argc, char **args) {
    (void) argc; (void) args;

    testNchooseK();
    test1();
    test2();

    return 0;
}

mpz_class nChooseK(int n, int k) {

    assert(k >= 0);
    assert(k <= n);
    assert(n >= 0);

    static QHash<QPair<int, int>, mpz_class> cache;

    std::function<mpz_class(int, int)> recurse = [&recurse](int n, int k) -> mpz_class {
        if (k == n || k == 0) { return 1; }

        auto lp = QPair<int, int>(n-1, k-1);
        auto rp = QPair<int, int>(n-1, k  );

        mpz_class l;
        mpz_class r;

        if (cache.contains(lp)) {
            l = cache[lp];
        } else {
            l = recurse(n-1, k-1);
            cache[lp] = l;
        }

        if (cache.contains(rp)) {
            r = cache[rp];
        } else {
            r = recurse(n-1, k);
            cache[rp] = r;
        }

        return l + r;
    };

    return recurse(n, k);
}

void testNchooseK() {
    assert(nChooseK(0, 0) == 1);

    assert(nChooseK(1, 0) == 1);
    assert(nChooseK(1, 1) == 1);

    assert(nChooseK(2, 0) == 1);
    assert(nChooseK(2, 1) == 2);
    assert(nChooseK(2, 2) == 1);

    assert(nChooseK(3, 0) == 1);
    assert(nChooseK(3, 1) == 3);
    assert(nChooseK(3, 2) == 3);
    assert(nChooseK(3, 3) == 1);

    assert(nChooseK(4, 0) == 1);
    assert(nChooseK(4, 1) == 4);
    assert(nChooseK(4, 2) == 6);
    assert(nChooseK(4, 3) == 4);
    assert(nChooseK(4, 4) == 1);
}

s64 numberOfEntriesNotDivBySeven(int nMax) {

    s64 sum = 0;

    for (int n = 0; n <= nMax; n += 1) {
        for (int k = 0; k <= n; k += 1) {
            sum += nChooseK(n, k) % 7 != 0 ? 1 : 0;
        }
    }

    return sum;
}

void test1() {

    int nMax = 20;
    int printWidth = ceil(log10(nMax+1));

    for (int n = 0; n <= nMax; n += 1) {
        QString l = QString("%1: ").arg(n, ceil(log10(nMax+1)));
        for (int k = 0; k <= n; k += 1) {
            l += QString("%1 ").arg(nChooseK(n, k).get_si(), 2*printWidth);
        }
        qDebug().noquote() << l;
    }

    nMax = 100;
    printWidth = ceil(log10(nMax+1));

    for (int n = 0; n <= nMax; n += 1) {
        QString l = QString("%1: (%2) ").arg(n, printWidth).arg(numberOfEntriesNotDivBySeven(n), 2*printWidth);
        for (int k = 0; k <= n; k += 1) {
            l += QString("%1").arg(mpz_class(nChooseK(n, k) % 7).get_si() == 0 ? "0" : "-" , 1);
        }
        qDebug().noquote() << l;
    }
}

s64 numberOfEntriesNotDivBySeven2(int nMax) {

    if (nMax < 7) {
        return (nMax+2)*(nMax+1) / 2;
    } else {
        int x = 7;
        while (nMax >= x) {
            x *= 7;
        }

        int r = (nMax % (x/7)) + 1;

        int nUp = nMax / (x/7);

        s64 non = numberOfEntriesNotDivBySeven2(x/7 - 1);

        return ((nUp+1)*(nUp) * non / 2) + numberOfEntriesNotDivBySeven2(r-1)*(nUp+1);
    }
}


void test2() {

    int nMin = 0;
    int nMax = 120;
    int printWidth = ceil(log10(nMax+1));

    for (int n = nMin; n <= nMax; n += 1) {
        s64 s = numberOfEntriesNotDivBySeven (n);
        s64 t = numberOfEntriesNotDivBySeven2(n);

        QString l = QString("%1: (%2 %3 %4) ").arg(n, printWidth).arg(s, 2*printWidth).arg(s == t ? "  " : "!=").arg(t, 2*printWidth);

        for (int k = 0; k <= n; k += 1) {
            l += QString("%1").arg(mpz_class(nChooseK(n, k) % 7).get_si() == 0 ? "0" : "-" , 1);
        }
        qDebug().noquote() << l;

        assert(s == t);
    }

    qDebug().noquote() << "";
    qDebug().noquote() << "Answer:" << numberOfEntriesNotDivBySeven2(1000 * 1000 * 1000 - 1);
}

