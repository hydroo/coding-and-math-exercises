#include "../lib.hpp"

using namespace std;

void test1();
void testNumberBitMask();
void testDoubleBits();
void test2();
void test3();

int main(int argc, char **args) {
    (void) argc; (void) args;

    // test1();
    // testNumberBitMask();
    // testDoubleBits();
    // test2();
    test3();

    return 0;
}

s64 f(s64 n) {

    QVector<s64> ps;

    s64 i = 1;
    while (i <= n) {
        ps << i;
        i *= 2;
    }

    std::function<s64(s64, const QVector<s64>&, int)> recurse = [n, ps, &recurse](s64 sum, const QVector<s64>& sum2, int pIndex) -> s64 {

        if (sum == n) {
            //qDebug () << "  " << sum << " = " << sum2;
            return 1;
        }
        if (sum  > n) { return 0; }
        if (pIndex >= ps.size()) { return 0; }

        s64 ret = 0;

        QVector<s64> sum3 = sum2;

        // qDebug() << sum3;
        ret += recurse(sum               , sum3, pIndex + 1);
        sum3 << ps[pIndex];
        // qDebug() << sum3;
        ret += recurse(sum + ps[pIndex]  , sum3, pIndex + 1);
        sum3 << ps[pIndex];
        // qDebug() << sum3;
        ret += recurse(sum + ps[pIndex]*2, sum3, pIndex + 1);

        return ret;
    };

    return recurse(0, QVector<s64>{}, 0);
}

void test1() {

    const s64 min  = 1;
    const s64 max  = 10000;
    const s64 step = 10;
    const int printWidth = (int) ceil(log10(max + 1));

    for (s64 n = min; n <= max; n *= step) {
        qDebug().noquote() << QString("f(%1) = %2").arg(n, printWidth).arg(f(n), printWidth*2);
    }
}

// f(      1) =         1
// f(     10) =         5
// f(    100) =        19
// f(   1000) =        39
// f(  10000) =       205
// f( 100000) =       713
// f(1000000) =      1287

// f(     1) =          1
// f(     5) =          2
// f(    25) =          5
// f(   125) =          6
// f(   625) =         33
// f(  3125) =         78
// f( 15625) =        141
// f( 78125) =        726
// f(390625) =        725

// f(    1) =           1
// f(    2) =           2
// f(    4) =           3
// f(    8) =           4
// f(   16) =           5
// f(   32) =           6
// f(   64) =           7
// f(  128) =           8
// f(  256) =           9
// f(  512) =          10
// f( 1024) =          11
// f( 2048) =          12
// f( 4096) =          13
// f( 8192) =          14
// f(16384) =          15
// f(32768) =          16

std::vector<bool> numberBitMask(mpz_class n) {

    int bitCount = 0;
    mpz_class p(1);
    while (p <= n) {
        bitCount += 1;
        p *= 2;
    }

    p /= 2;

    std::vector<bool> bits(bitCount);

    int bit = 0;
    while (n > 0) {
        if (n >= p) {
            n -= p;
            bits[bit] = true; // set right of the two
        }
        p /= 2;
        bit += 1;
    }

    return bits;
}

std::vector<bool> doubleBits(const vector<bool>& v) {
    std::vector<bool> w(v.size()*2);

    for (int i = 0; i < (int) v.size(); i += 1) {
        w[i*2]     = v[i];
        w[i*2 + 1] = false;
    }

    return w;
}

std::vector<bool> halveBits(const vector<bool>& v) {
    std::vector<bool> w(v.size()/2);

    for (int i = 0; i < (int) w.size(); i += 1) {
        w[i  ] = v[i*2  ];
        w[i+1] = v[i*2+1];
    }

    return w;
}

void testNumberBitMask() {
    assert(numberBitMask(0) == (std::vector<bool>{       }));
    assert(numberBitMask(1) == (std::vector<bool>{      1}));
    assert(numberBitMask(2) == (std::vector<bool>{   1, 0}));
    assert(numberBitMask(3) == (std::vector<bool>{   1, 1}));
    assert(numberBitMask(4) == (std::vector<bool>{1, 0, 0}));
    assert(numberBitMask(5) == (std::vector<bool>{1, 0, 1}));
    assert(numberBitMask(6) == (std::vector<bool>{1, 1, 0}));
    assert(numberBitMask(7) == (std::vector<bool>{1, 1, 1}));
}

void testDoubleBits() {
    assert(doubleBits(std::vector<bool>{0      }) == (std::vector<bool>{0, 0      }));
    assert(doubleBits(std::vector<bool>{1      }) == (std::vector<bool>{1, 0      }));
    assert(doubleBits(std::vector<bool>{0, 0   }) == (std::vector<bool>{0, 0, 0, 0}));
    assert(doubleBits(std::vector<bool>{0, 1   }) == (std::vector<bool>{0, 0, 1, 0}));
    assert(doubleBits(std::vector<bool>{1, 0   }) == (std::vector<bool>{1, 0, 0, 0}));
    assert(doubleBits(std::vector<bool>{1, 1   }) == (std::vector<bool>{1, 0, 1, 0}));
    assert(doubleBits(std::vector<bool>{1, 0, 1}) == (std::vector<bool>{1, 0, 0, 0, 1, 0}));
}

s64 f2(mpz_class n) {

    std::vector<bool> bits = doubleBits(numberBitMask(n));

    // qDebug() << n << " " << numberBitMask(n);

    std::function<s64(const std::vector<bool>&, int)> recurse = [&recurse](const std::vector<bool>& v, int bit) -> s64 {

        if (bit - 2 < 0) {
            // qDebug() << v << " " << halveBits(v);
            return 1;
        }

        s64 sum = recurse(v, bit-2);

        if (v[bit] == false) {
            assert(v[bit+1] == false);

            if (v[bit-2] == true) {
                std::vector<bool> v2 = v;

                int whichBit = bit - 2;
                if (v[bit-1] == true) {
                    whichBit = bit - 1;
                }

                v2[whichBit] = false;
                v2[bit     ] = true;
                v2[bit+1   ] = true;

                if (bit+2 < (int) v.size()) {
                    sum += recurse(v2, bit+2);
                } else {
                    sum += recurse(v2, bit);
                }
            }
        }

        return sum;
    };

    return recurse(bits, bits.size()-2);
}

void test2() {
    const s64 min  = 1;
    const s64 max  = 100;
    const s64 step = 1;
    const int printWidth = (int) ceil(log10(max + 1));

    for (s64 n = min; n <= max; n += step) {
        s64 c1 = f(n);
        s64 c2 = f2(n);

        qDebug().noquote() << QString("f(%1) = %2 %3 %4").arg(n, printWidth).arg(c1, printWidth*2).arg(c1 == c2 ? "  " : "!=").arg(c2, 2*printWidth);
        assert(c1 == c2);
    }

    mpz_class    base2    = 10;
    unsigned int minpow2  = 1;
    unsigned int maxpow2  = 16;

    for (unsigned int p = minpow2; p <= maxpow2; p += 1) {

        mpz_class n(base2);
        mpz_pow_ui(n.get_mpz_t(), n.get_mpz_t(), p);

        s64 c = f2(n);

        mpz_class n2 = n;
        while (n2 % 5 == 0) {
            n2 /= 5;
        }
        mpz_class n5 = n;
        while (n5 % 2 == 0) {
            n5 /= 2;
        }

        s64 c2 = f2(n2);
        s64 c5 = f2(n5);

        // qDebug().noquote() << QString("f(10^%1)) = %2").arg(p, 2).arg(c, maxpow2);
        qDebug().noquote() << QString("f(10^%1)) = %2,   f(2^%1) = %3,    f(5^%1) = %4").arg(p, 2).arg(c, 18).arg(c2, 2).arg(c5, 18/2);
    }
}

// f(                      10 (10^ 1)) =           5
// f(                     100 (10^ 2)) =          19
// f(                    1000 (10^ 3)) =          39
// f(                   10000 (10^ 4)) =         205
// f(                  100000 (10^ 5)) =         713
// f(                 1000000 (10^ 6)) =        1287
// f(                10000000 (10^ 7)) =        9469
// f(               100000000 (10^ 8)) =        7901
// f(              1000000000 (10^ 9)) =       73411
// f(             10000000000 (10^10)) =       77695
// f(            100000000000 (10^11)) =      417293
// f(           1000000000000 (10^12)) =     2077157
// f(          10000000000000 (10^13)) =     4384367
// f(         100000000000000 (10^14)) =     5946265
// f(        1000000000000000 (10^15)) =    22274375
// f(       10000000000000000 (10^16)) =    17165857 (  4s)
// f(      100000000000000000 (10^17)) =   233403727 ( 48s)
// f(     1000000000000000000 (10^18)) =   554817437 (120s)
// f(    10000000000000000000 (10^19)) =  1153744559
// f(   100000000000000000000 (10^20)) =  5483345119
// f(  1000000000000000000000 (10^21)) = 18953059023
// f( 10000000000000000000000 (10^22)) = 20058384877

// f(10^ 1)) =        5,   f(2^ 1) =  2,    f(5^ 1) =      2
// f(10^ 2)) =       19,   f(2^ 2) =  3,    f(5^ 2) =      5
// f(10^ 3)) =       39,   f(2^ 3) =  4,    f(5^ 3) =      6
// f(10^ 4)) =      205,   f(2^ 4) =  5,    f(5^ 4) =     33
// f(10^ 5)) =      713,   f(2^ 5) =  6,    f(5^ 5) =     78
// f(10^ 6)) =     1287,   f(2^ 6) =  7,    f(5^ 6) =    141
// f(10^ 7)) =     9469,   f(2^ 7) =  8,    f(5^ 7) =    726
// f(10^ 8)) =     7901,   f(2^ 8) =  9,    f(5^ 8) =    725
// f(10^ 9)) =    73411,   f(2^ 9) = 10,    f(5^ 9) =   4804
// f(10^10)) =    77695,   f(2^10) = 11,    f(5^10) =   4985
// f(10^11)) =   417293,   f(2^11) = 12,    f(5^11) =  20182
// f(10^12)) =  2077157,   f(2^12) = 13,    f(5^12) = 127409
// f(10^13)) =  4384367,   f(2^13) = 14,    f(5^13) = 199472
// f(10^14)) =  5946265,   f(2^14) = 15,    f(5^14) = 290307
// f(10^15)) = 22274375,   f(2^15) = 16,    f(5^15) = 842330
// f(10^16)) = 17165857,   f(2^16) = 17,    f(5^16) = 853713

s64 f3(mpz_class n) {
    // TODO
    return 0;
}

void test3() {
    const s64 min  = 1;
    const s64 max  = 10;
    const s64 step = 1;
    const int printWidth = (int) ceil(log10(max + 1));

    for (s64 n = min; n <= max; n += step) {
        s64 c1 = f(n);
        s64 c3 = f3(n);

        qDebug().noquote() << QString("f(%1) = %2 %3 %4").arg(n, printWidth).arg(c1, printWidth*2).arg(c1 == c3 ? "  " : "!=").arg(c3, 2*printWidth);
        assert(c1 == c3);
    }

    mpz_class    base2    = 10;
    unsigned int minpow2  = 1;
    unsigned int maxpow2  = 16;

    for (unsigned int p = minpow2; p <= maxpow2; p += 1) {

        mpz_class n(base2);
        mpz_pow_ui(n.get_mpz_t(), n.get_mpz_t(), p);

        s64 c = f3(n);

        qDebug().noquote() << QString("f(10^%1)) = %2").arg(p, 2).arg(c, maxpow2);
    }
}
