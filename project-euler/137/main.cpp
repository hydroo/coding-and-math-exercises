#include <cassert>
#include <cmath>
#include <gmpxx.h>

#include <QtDebug>

using s64 = int64_t;
using f64 = double;

QDebug operator<<(QDebug s, const mpq_class& m) {
    char b[65536] = "";
    gmp_sprintf (b, "%Qd", m.get_mpq_t());
    s << b;
    return s;
}

QDebug operator<<(QDebug s, const mpz_class& m) {
    char b[65536] = "";
    gmp_sprintf (b, "%Zd", m.get_mpz_t());
    s << b;
    return s;
}

QDebug operator<<(QDebug s, const mpf_class& m) {
    char b[65536] = "";
    gmp_sprintf (b, "%.9Ff", m.get_mpf_t());
    s << b;
    return s;
}

QList<mpz_class> initLazyFibonacci() {
    return {0, 1, 1};
}

mpz_class lazyFibonacci(int k, QList<mpz_class>* F ) {
    while (k >= F->size()) {
        (*F) << (*F)[F->size()-1] + (*F)[F->size()-2];
    }
    return (*F)[k];
}

QList<s64> generateFibonacciSequenceS64(int upTo) {

    QList<s64> ret = {0, 1, 1};
    for (int i = 3; i <= upTo; i += 1) {
        ret << ret[i-1] + ret[i-2];
    }
    return ret;
}

bool isSquare(const mpz_class& i) {
    mpz_class dummy, remainder;
    mpz_rootrem(dummy.get_mpz_t(), remainder.get_mpz_t(), i.get_mpz_t(), 2);
    return remainder == 0;
}

mpf_class x_mpf(const mpz_class& square_, const mpz_class& minus, const mpz_class& div) {
    mpf_class square = square_;
    mpf_class ret    = square;

    mpf_sqrt(ret.get_mpf_t(), square.get_mpf_t());
    ret = (ret - minus) / div;
    return ret;
}

//f64 A(f64 x, const QVector<s64> fibonacciSequence) {
//    f64 ret = 0;
//
//    for (s64 degree = 1; degree < fibonacciSequence.size(); degree += 1) {
//        ret += pow(x, degree)*fibonacciSequence[degree];
//    }
//
//    return ret;
//}

//f64 A(s64 num, s64 den, const QVector<s64> fibonacciSequence) {
//    f64 ret = 0;
//
//    s64 numPow = num;
//    s64 denPow = den;
//
//    f64 last = 0;
//
//    s64 degree = 1;
//    for (; degree < fibonacciSequence.size(); degree += 1) {
//        last = ret;
//        if (numPow * fibonacciSequence[degree] < 0) {
//            break;
//        } else if (numPow < 0) {
//            break;
//        } else if (denPow < 0) {
//            break;
//        }
//
//        ret += ((double) (numPow * fibonacciSequence[degree])) / denPow;
//
//        if (ret < 0) {
//            // shouldn't happen?
//            ret = last;
//            break;
//        }
//
//        numPow *= num;
//        denPow *= den;
//
//        //qDebug() << degree << numPow << denPow << numPow * fibonacciSequence[degree] << ret;
//    }
//
//    if (ret - last >= 0.0001) {
//        qDebug() << QString("%1 / %2 diverged?! A = %3, degree = %4").arg(num, 3).arg(den, 3).arg(ret).arg(degree);
//    }
//
//    if (ret - floor(ret) <= 0.0001 || ret - ceil(ret) <= 0.0001) {
//        qDebug() << QString("+ %1 / %2, deg = %3, A = %4").arg(num, 3).arg(den, 3).arg(degree).arg(ret);
//    } else {
//        qDebug() << QString("- %1 / %2, deg = %3, A = %4").arg(num, 3).arg(den, 3).arg(degree).arg(ret) << ret - floor(ret) << ret - ceil(ret);
//    }
//
//    return ret;
//}

//mpf_class (mpf_class x, const QList<mpz_class> F) {
//    mpf_class ret = 0;
//
//    mpf_class xp = x;
//
//    for (s64 k = 1; k < F.size(); k += 1) {
//        ret += xp * F[k];
//        xp *= x;
//    }
//
//    return ret;
//}

f64 A_f64(f64 x, const QList<s64>& F) {
    f64 ret = 0;

    f64 xp = x;

    for (s64 k = 1; k < F.size(); k += 1) {
        ret += xp * F[k];
        xp *= x;
    }

    return ret;
}

mpf_class A_mpf(const mpf_class& x, QList<mpz_class>* F, const f64 threshold = 0.000000001) {
    if (x >= 1) { return -1; }

    mpf_class ret = 0;
    mpf_class xp = x;

    int k = 1;
    for (;;) {

        mpf_class add = xp * lazyFibonacci(k, F);
        ret += add;
        //qDebug() << ret << add << xp << lazyFibonacci(k, F);

        xp *= x;
        k += 1;

        if (k >= 200000) { // use this to not lock up due to too long numbers
            //qDebug() << x << "k = 100000 too big";
            break;
        }
        if (add < threshold) {
            break;
        }
    }

    return ret;
}

//s64 gcd(s64 a, s64 b) {
//    s64 t;
//    while (b != 0) {
//        t = b;
//        b = a % b;
//        a = t;
//    }
//    return a;
//}

mpq_class A_mpq(const mpz_class& afx_, const mpq_class& startX, const QList<mpz_class> F) {

    mpq_class x = startX;

restart:

    mpq_class xp = x;
    mpq_class afx = afx_;

    for (int i = 1; i < F.size(); i += 1) {
        afx -= xp*F[i];

        if (afx < 0) {
            mpz_class afxden;
            mpq_get_den(afxden.get_mpz_t(), x.get_mpq_t());
            afxden += 1;
            mpq_set_den(x.get_mpq_t(), afxden.get_mpz_t());
            qDebug() << "increase den x: " << x;
            goto restart;
        }

        xp *= x;
    }

    double afxd = mpq_get_d(afx.get_mpq_t());

    if (afxd > 0.00001) {
        mpz_class afxnum;
        mpq_get_num(afxnum.get_mpz_t(), x.get_mpq_t());
        afxnum += 1;
        mpq_set_num(x.get_mpq_t(), afxnum.get_mpz_t());
        qDebug() << "afxd" << afxd << "increase num x: " << x;
        goto restart;
    }

    return x;
}

void testGenerateFibonacciSequence();
void testLazyFibonacci();
void testFibonacciNumbersThatAreSquares();
void test1();
void test2(const QList<mpz_class>& fibonacciSequence);
void testDoubleFibonacci(const QList<s64>& fibonacciSequence);
void testA_mpf();
void testInputOutputCorrelation();
void testInputOutputCorrelation2();


int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    const int maxKS64 = 92;

    testGenerateFibonacciSequence();
    testLazyFibonacci();
    //testFibonacciNumbersThatAreSquares();

    auto F_s64 = generateFibonacciSequenceS64(maxKS64);

    //test1();
    //test2(fibonacciSequence);
    //testDoubleFibonacci(F_s64);

    //testA_mpf();
    //testInputOutputCorrelation();
    testInputOutputCorrelation2();

    return 0;
}

void testGenerateFibonacciSequence() {
    auto v1 = generateFibonacciSequenceS64(9);
    assert(v1[0] ==  0);
    assert(v1[1] ==  1);
    assert(v1[2] ==  1);
    assert(v1[3] ==  2);
    assert(v1[4] ==  3);
    assert(v1[5] ==  5);
    assert(v1[6] ==  8);
    assert(v1[7] == 13);
    assert(v1[8] == 21);
    assert(v1[9] == 34);
}

void testLazyFibonacci() {
    QList<mpz_class> F = initLazyFibonacci();
    assert(lazyFibonacci( 0, &F) ==  0);
    assert(lazyFibonacci( 1, &F) ==  1);
    assert(lazyFibonacci( 2, &F) ==  1);
    assert(lazyFibonacci( 3, &F) ==  2);
    assert(lazyFibonacci( 4, &F) ==  3);
    assert(lazyFibonacci( 5, &F) ==  5);
    assert(lazyFibonacci( 6, &F) ==  8);
    assert(lazyFibonacci( 7, &F) == 13);
    assert(lazyFibonacci( 8, &F) == 21);
    assert(lazyFibonacci( 9, &F) == 34);
    assert(lazyFibonacci(92, &F) == 7540113804746346429);
}

void testFibonacciNumbersThatAreSquares() {

    // only F_11 = 144
    // none until F_150000

    auto F = initLazyFibonacci();

    for (int i = 1; i < 1000000; i += 1) {

        if (i % 30000 == 0) {
            qDebug() << i;
        }

        if (isSquare(lazyFibonacci(i, &F))) {
            mpz_class root;
            mpz_sqrt(root.get_mpz_t(), lazyFibonacci(i, &F).get_mpz_t());
            qDebug() << i << lazyFibonacci(i, &F) << root;
        }
    }
}

void test1() {
    qDebug() << "sqrt(2)-1      = " << sqrt(2)-1     ;
    qDebug() << "1/2            = " << 1/2.0         ;
    qDebug() << "(sqrt(13)-2)/3 = " << (sqrt(13)-2)/3;
    qDebug() << "(sqrt(89)-5)/8 = " << (sqrt(89)-5)/8;
    qDebug() << "(sqrt(34)-8)/5 = " << (sqrt(34)-3)/5;
}

void test2(const QList<mpz_class>& fibonacciSequence) {

    auto aa  = A_mpq(74049690, mpq_class(4,5), fibonacciSequence);
    qDebug() << "A(?) = 74049690:" << aa;

    //auto a2  = A_mpq(2 , mpq_class(1,2), fibonacciSequence);
    //qDebug() << "A(?) = 2 :" << toString(a2);
    //auto a3  = A_mpq(3 , a2 , fibonacciSequence);
    //qDebug() << "A(?) = 3 :" << toString(a3);
    //auto a4  = A_mpq(4 , a3 , fibonacciSequence);
    //qDebug() << "A(?) = 4 :" << toString(a4);
    //auto a5  = A_mpq(5 , a4 , fibonacciSequence);
    //qDebug() << "A(?) = 5 :" << toString(a5);
    //auto a6  = A_mpq(6 , a5 , fibonacciSequence);
    //qDebug() << "A(?) = 6 :" << toString(a6);
    //auto a7  = A_mpq(7 , a6 , fibonacciSequence);
    //qDebug() << "A(?) = 7 :" << toString(a7);
    //auto a8  = A_mpq(8 , a7 , fibonacciSequence);
    //qDebug() << "A(?) = 8 :" << toString(a8);
    //auto a9  = A_mpq(9 , a8 , fibonacciSequence);
    //qDebug() << "A(?) = 9 :" << toString(a9);
}

void testDoubleFibonacci(const QList<s64>& F) {
    qDebug() << A_f64((sqrt(F[ 3])-F[ 1])/F[ 2], F) << A_f64( sqrt( 2)-1   , F);
    qDebug() << A_f64(0.5           , F)            << A_f64(0.5           , F);
    qDebug() << A_f64((sqrt(F[ 7])-F[ 3])/F[ 4], F) << A_f64((sqrt(13)-2)/3, F);
    qDebug() << A_f64((sqrt(F[11])-F[ 5])/F[ 6], F) << A_f64((sqrt(89)-5)/8, F);
    qDebug() << A_f64((sqrt(F[ 9])-F[ 4])/F[ 5], F) << A_f64((sqrt(34)-3)/5, F);
    //qDebug() << A_f64((sqrt(F[13])-F[ 6])/F[ 7], F);
    //qDebug() << A_f64((sqrt(F[14])-F[ 6])/F[ 8], F);
    //qDebug() << A_f64((sqrt(F[15])-F[ 7])/F[ 8], F);
}

void testA_mpf() {
    auto F = initLazyFibonacci();

    qDebug() << " sqrt(      8) -   2  /    2" << x_mpf(      8,   2,    2) << A_mpf(x_mpf(      8,   2,    2), &F, 0.00000000001);
    qDebug() << "(sqrt(     25) -   3) /    4" << x_mpf(     25,   3,    4) << A_mpf(x_mpf(     25,   3,    4), &F, 0.00000000001) << "nugget 1";
    qDebug() << "(sqrt(     52) -   4) /    6" << x_mpf(     52,   4,    6) << A_mpf(x_mpf(     52,   4,    6), &F, 0.00000000001);
    qDebug() << "(sqrt(     89) -   5) /    8" << x_mpf(     89,   5,    8) << A_mpf(x_mpf(     89,   5,    8), &F, 0.00000000001);
    qDebug() << "(sqrt(    136) -   6) /   10" << x_mpf(    136,   6,   10) << A_mpf(x_mpf(    136,   6,   10), &F, 0.00000000001);

    qDebug() << "(sqrt(   1156) -  16) /   30" << x_mpf(   1156,   6,   30) << A_mpf(x_mpf(   1156,  16,   30), &F, 0.00000000001) << "nugget 2";
    qDebug() << "(sqrt(  54289) - 105) /  208" << x_mpf(  54289, 105,  208) << A_mpf(x_mpf(  54289, 105,  208), &F, 0.000000000001) << "nugget 3";
    qDebug() << "(sqrt(2550409) - 715) / 1428" << x_mpf(2550409, 715, 1428) << A_mpf(x_mpf(2550409, 715, 1428), &F, 0.0000000000001) << "nugget 4";
    qDebug() << "(sqrt(  10000) -  45) /   89" << x_mpf(  10000,   45,  89) << A_mpf(x_mpf(  10000,  45,   89), &F, 0.00000000000001) << "nugget 5";

    QMultiMap<mpf_class, QList<int>> xs;

    for (int a = 1; a < 10000; a += 1) {
        //if (isSquare(a) == false) { continue; } // show only nuggets
            for (int c = 1; c <= 100; c += 1) {
                xs.insert(x_mpf(a, c/2+1, c), {a, c/2+1, c});
            }
    }

    QMapIterator<mpf_class, QList<int>> i(xs);
    while (i.hasNext()) {
        i.next();
        if (i.key() >= 0.5 && i.key() < 1.0) {

            mpf_class result = A_mpf(i.key(), &F, 0.000000001);
            mpf_class resultCeil;
            mpf_ceil(resultCeil.get_mpf_t(), result.get_mpf_t());

            if (resultCeil - result <= 0.0001 && 2*resultCeil == i.value()[2]) { // reduce results to specific c values
            //if (resultCeil - result <= 0.0001) {
                qDebug() << i.key() << i.value() << result << isSquare(i.value()[0]);
            }
        }
    }
}

// 0           (      1,   1,    0)    0 (virtual)
// 0.414213562 (      8,   2,    2)    1 false
// 0.500000000 (     25,   3,    4)    2 true  sqrt(     25) = 5
// 0.535183758 (     52,   4,    6)    3 false
// 0.554247642 (     89,   5,    8)    4 false
// 0.566190379 (    136,   6,   10)    5 false
// 0.574370332 (    193,   7,   12)    6 false
// 0.580322535 (    260,   8,   14)    7 false
// 0.584847484 (    337,   9,   16)    8 false
// 0.588403349 (    424,  10,   18)    9 false
// 0.591271221 (    521,  11,   20)   10 false
// 0.593633099 (    628,  12,   22)   11 false
// 0.595612005 (    745,  13,   24)   12 false
// 0.597294082 (    872,  14,   26)   13 false
// 0.598741441 (   1009,  15,   28)   14 false
// 0.600000000 (   1156,  16,   30)   15 true  sqrt(   1156) = 34
// 0.601104433 (   1313,  17,   32)   16 false
// 0.602081415 (   1480,  18,   34)   17 false
// 0.615384615 (  54289, 105,  208)  104 true  sqrt(  54289) = 233
// 0.617647059 (2550409, 715, 1428)  714 true  sqrt(2550409) = 1597
// 0.617977528 (  10000,  45,   89) 4895 true  sqrt(  10000) = 100

void testInputOutputCorrelation() {

    //auto F = initLazyFibonacci();
    //for (int i = 0; i < 100; i += 1) {
    //    qDebug() << "F("<< i << ") = "<< lazyFibonacci(i, &F);
    //}

    struct Nugget {
        mpz_class a, b, c, afx;
    };

    QList<Nugget> nuggets;

    mpz_class afx  = 0;
    mpz_class c    = 0;
    mpz_class b    = 1;
    mpz_class a    = 1;
    mpz_class addA = 7;

    nuggets << Nugget{a, b, c, afx};

    int i = 1;
    while (true) {

        a  += addA;
        b  += 1;
        c  += 2;
        afx += 1;

        addA += 10;

        if (isSquare(a)) {

            const auto& n = nuggets.last();

            qDebug() << i << a << b << c << " AF(x) = " << afx << "| diff:" << (mpz_class) (a-n.a) << (mpz_class) (b-n.b) << (mpz_class) (c-n.c) << (mpz_class) (afx-n.afx);

            nuggets << Nugget{a, b, c, afx};

            i += 1;
        }
    }

}

// Nuggets:
//  1                25        3         4 AF(x) =         2
//  2              1156       16        30 AF(x) =        15
//  3             54289      105       208 AF(x) =       104
//  4           2550409      715      1428 AF(x) =       714
//  5         119814916     4896      9790 AF(x) =      4895
//  6        5628750625    33553     67104 AF(x) =     33552
//  7      264431464441   229971    459940 AF(x) =    229970
//  8    12422650078084  1576240   3152478 AF(x) =   1576239
//  9   583600122205489 10803705  21607408 AF(x) =  10803704
// 10 27416783093579881 74049691 148099380 AF(x) =  74049690

void testInputOutputCorrelation2() {

    auto F = initLazyFibonacci();

    int k = 3;

    mpz_class afx = 0;

    for (int i = 1; i <= 15; i += 1) {

        afx += lazyFibonacci(k, &F);

        //qDebug() << i << afx;
        if (i == 15) {
            qDebug() << afx;
        }

        k += 4;
    }
}
