#include <cassert>
#include <cmath>
#include <gmpxx.h>

#include <QtDebug>
#include <QTime>

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

QList<mpz_class> initLazySecondOrderRecurrenceRelation() {
    return {-1, 1, 4};
}

mpz_class lazySecondOrderRecurrenceRelation(int k, QList<mpz_class>* F ) {
    assert(k >= 1);
    while (k >= F->size()) {
        (*F) << (*F)[F->size()-1] + (*F)[F->size()-2];
    }
    return (*F)[k];
}

QList<mpz_class> initLazyFibonacci() {
    return {0, 1, 1};
}

mpz_class lazyFibonacci(int k, QList<mpz_class>* F ) {
    assert(k >= 0);
    while (k >= F->size()) {
        (*F) << (*F)[F->size()-1] + (*F)[F->size()-2];
    }
    return (*F)[k];
}

bool isSquare(const mpz_class& i) {
    mpz_class dummy, remainder;
    mpz_rootrem(dummy.get_mpz_t(), remainder.get_mpz_t(), i.get_mpz_t(), 2);
    return remainder == 0;
}

mpz_class squareRoot(const mpz_class& i) {
    mpz_class root, remainder;
    mpz_rootrem(root.get_mpz_t(), remainder.get_mpz_t(), i.get_mpz_t(), 2);
    assert(remainder == 0);
    return root;
}

mpf_class x_mpf(const mpz_class& square_, const mpz_class& minus, const mpz_class& div) {
    mpf_class square = square_;
    mpf_class ret    = square;

    mpf_sqrt(ret.get_mpf_t(), square.get_mpf_t());
    ret = (ret - minus) / div;
    return ret;
}

mpf_class A_mpf(const mpf_class& x, QList<mpz_class>* F, const f64 threshold = 0.000000001) {
    if (x >= 1) { return -1; }

    mpf_class ret = 0;
    mpf_class xp = x;

    int k = 1;
    for (;;) {

        mpf_class add = xp * lazySecondOrderRecurrenceRelation(k, F);
        ret += add;
        //qDebug() << ret << add << xp << lazySecondOrderRecurrenceRelation(k, F);

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

void testLazySecondOrderRecurrenceRelation();
void test1();
void testInputOutputCorrelation();
void testInputOutputCorrelation2();
void testDiffOfDiffs();
void testInputOutputCorrelationWithDiffOfDiffs();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    testLazySecondOrderRecurrenceRelation();

    //test1();
    //testInputOutputCorrelation();
    //testInputOutputCorrelation2();
    //testDiffOfDiffs();
    testInputOutputCorrelationWithDiffOfDiffs();

    return 0;
}

void testLazySecondOrderRecurrenceRelation() {
    QList<mpz_class> F = initLazySecondOrderRecurrenceRelation();
    assert(lazySecondOrderRecurrenceRelation( 1, &F) ==  1);
    assert(lazySecondOrderRecurrenceRelation( 2, &F) ==  4);
    assert(lazySecondOrderRecurrenceRelation( 3, &F) ==  5);
    assert(lazySecondOrderRecurrenceRelation( 4, &F) ==  9);
    assert(lazySecondOrderRecurrenceRelation( 5, &F) == 14);
    assert(lazySecondOrderRecurrenceRelation( 6, &F) == 23);

    //for (int i = 1; i < 50; i += 1) {
    //    qDebug() << "SORR(" << i << ") = " << lazySecondOrderRecurrenceRelation(i, &F);
    //}
}

// SORR(  1 ) =      1 // SORR(  2 ) =      4 // SORR(  3 ) =      5 // SORR(  4 ) =      9
// SORR(  5 ) =     14 // SORR(  6 ) =     23 // SORR(  7 ) =     37 // SORR(  8 ) =     60
// SORR(  9 ) =     97 // SORR( 10 ) =    157 // SORR( 11 ) =    254 // SORR( 12 ) =    411
// SORR( 13 ) =    665 // SORR( 14 ) =   1076 // SORR( 15 ) =   1741 // SORR( 16 ) =   2817
// SORR( 17 ) =   4558 // SORR( 18 ) =   7375 // SORR( 19 ) =  11933 // SORR( 20 ) =  19308

void test1() {
    auto F = initLazySecondOrderRecurrenceRelation();

    qDebug() << " sqrt(      5) -   1  /    4" << x_mpf(      5,   1,    4) << A_mpf(x_mpf(      5,   1,    4), &F, 0.00000000001);
    qDebug() << "(sqrt(      4) -   0) /    5" << x_mpf(      4,   0,    5) << A_mpf(x_mpf(      4,   0,    5), &F, 0.00000000001);
    qDebug() << "(sqrt(     22) -   2) /    6" << x_mpf(     22,   2,    6) << A_mpf(x_mpf(     22,   2,    6), &F, 0.00000000001);
    qDebug() << "(sqrt(    137) -   5) /   14" << x_mpf(    137,   5,   14) << A_mpf(x_mpf(    137,   5,   14), &F, 0.00000000001);
    qDebug() << "(sqrt(      1) -   0) /    2" << x_mpf(      1,   0,    2) << A_mpf(x_mpf(      1,   0,    2), &F, 0.00000000001);

    QMultiMap<mpf_class, QList<int>> xs;

    for (int a = 1; a < 4000; a += 1) {
        //if (isSquare(a) == false) { continue; } // show only nuggets
        for (int b = 1; b < 1000; b += 1) {
            int c = 6 + (b-1)*2;
            xs.insert(x_mpf(a, b, c), {a, b, c});
        }
    }

    QMapIterator<mpf_class, QList<int>> i(xs);
    while (i.hasNext()) {
        i.next();
        if (i.key() >= 0.309 && i.key() < 0.6) {

            mpf_class result = A_mpf(i.key(), &F, 0.000000001);
            mpf_class resultCeil;
            mpf_ceil(resultCeil.get_mpf_t(), result.get_mpf_t());

            if (resultCeil - result <= 0.0001 && resultCeil+1 == i.value()[1]) { // reduce results to specific c values
            //if (resultCeil - result <= 0.0001) {
                qDebug() << i.key() << i.value() << result << isSquare(i.value()[0]);
            }
        }
    }
}

// 0.309016994 (20, 2, 8) 0.999999999 false a+= 29
// 0.400000000 (49, 3, 10) 1.999999999 true a+= 39
// 0.448402627 (88, 4, 12) 2.999999998 false a+= 49
// 0.478907136 (137, 5, 14) 3.999999997 false
// 0.500000000 (196, 6, 16) 4.999999996 true
// 0.515490033 (265, 7, 18) 5.999999995 false
// 0.527361850 (344, 8, 20) 6.999999995 false
// 0.536756911 (433, 9, 22) 7.999999994 false
// 0.544380216 (532, 10, 24) 8.999999993 false
// 0.550691454 (641, 11, 26) 9.999999992 false
// 0.556003482 (760, 12, 28) 10.999999992 false
// 0.560536768 (889, 13, 30) 11.999999991 false
// 0.564451221 (1028, 14, 32) 12.999999990 false
// 0.567865694 (1177, 15, 34) 13.999999989 false
// 0.570870382 (1336, 16, 36) 14.999999989 false
// 0.573534986 (1505, 17, 38) 15.999999987 false
// 0.575914226 (1684, 18, 40) 16.999999987 false
// 0.578051667 (1873, 19, 42) 17.999999986 false
// 0.579982425 (2072, 20, 44) 18.999999985 false
// 0.581735125 (2281, 21, 46) 19.999999985 false
// 0.583333333 (2500, 22, 48) 20.999999983 true
// 0.584796631 (2729, 23, 50) 21.999999983 false
// 0.586141421 (2968, 24, 52) 22.999999982 false
// 0.587381549 (3217, 25, 54) 23.999999982 false
// 0.588528784 (3476, 26, 56) 24.999999980 false
// 0.589593192 (3745, 27, 58) 25.999999980 false


void testInputOutputCorrelation() {

    QTime t; t.start();

    struct Nugget {
        mpz_class a, b, c, agx;
    };

    QList<Nugget> nuggets;

    mpz_class agx  =  0;
    mpz_class c    =  6;
    mpz_class b    =  1;
    mpz_class a    =  1;
    mpz_class addA = 19;

    nuggets << Nugget{a, b, c, agx};

    int i = 1;
    while (i <= 30) {

        a  += addA;
        b  += 1;
        c  += 2;
        agx += 1;

        addA += 10;

        if (isSquare(a)) {

            const auto& n = nuggets.last();

            qDebug() << int (t.elapsed() / 1000.0) << "s" << i << a << b << c << " AG(x) = " << agx << " sqrt(a)" << squareRoot(a) << "| diff:" << (mpz_class) (a-n.a) << (mpz_class) (b-n.b) << (mpz_class) (c-n.c) << (mpz_class) (agx-n.agx);

            nuggets << Nugget{a, b, c, agx};

            if      (i ==  1) { assert(agx ==   2); }
            else if (i ==  2) { assert(agx ==   5); }
            else if (i ==  3) { assert(agx ==  21); }
            else if (i ==  4) { assert(agx ==  42); }
            else if (i ==  5) { assert(agx == 152); }
            else if (i == 20) { assert(agx == 211345365); }

            i += 1;
        }
    }
}

// Nuggets:
//  1                    49          3          10  AG(x) =           2
//  2                   196          6          16  AG(x) =           5
//  3                  2500         22          48  AG(x) =          21
//  4                  9409         43          90  AG(x) =          42
//  5                117649        153         310  AG(x) =         152
//  6                442225        297         598  AG(x) =         296
//  7               5527201       1051        2106  AG(x) =        1050
//  8              20775364       2038        4080  AG(x) =        2037
//  9             259660996       7206       14416  AG(x) =        7205
// 10             976000081      13971       27946  AG(x) =       13970
// 11           12198539809      49393       98790  AG(x) =       49392
// 12           45851228641      95761      191526  AG(x) =       95760
// 13          573071710225     338547      677098  AG(x) =      338546
// 14         2154031746244     656358     1312720  AG(x) =      656357
// 15        26922171840964    2320438     4640880  AG(x) =     2320437
// 16       101193640845025    4498747     8997498  AG(x) =     4498746
// 17      1264769004815281   15904521    31809046  AG(x) =    15904520 takes ~ 14s
// 18      4753947087970129   30834873    61669750  AG(x) =    30834872 takes ~ 28s
// 19     59417221054477441  109011211   218022426  AG(x) =   109011210 takes ~100s
// 20    223334319493751236  211345366   422690736  AG(x) =   211345365 takes ~200s
// 21   2791344620555624644  747173958  1494347920  AG(x) =   747173957
// 22  10491959069118338161 1448582691  2897165386  AG(x) =  1448582690
// 23 131133779945059881025 5121206497 10242412998  AG(x) =  5121206496

// Nuggets with diff:
//  1                 49         3        10  AG(x) =          2, sqrt(a) 7         | diff:                 48         2         4         2
//  2                196         6        16  AG(x) =          5, sqrt(a) 14        | diff:                147         3         6         3
//  3               2500        22        48  AG(x) =         21, sqrt(a) 50        | diff:               2304        16        32        16
//  4               9409        43        90  AG(x) =         42, sqrt(a) 97        | diff:               6909        21        42        21
//  5             117649       153       310  AG(x) =        152, sqrt(a) 343       | diff:             108240       110       220       110
//  6             442225       297       598  AG(x) =        296, sqrt(a) 665       | diff:             324576       144       288       144
//  7            5527201      1051      2106  AG(x) =       1050, sqrt(a) 2351      | diff:            5084976       754      1508       754
//  8           20775364      2038      4080  AG(x) =       2037, sqrt(a) 4558      | diff:           15248163       987      1974       987
//  9          259660996      7206     14416  AG(x) =       7205, sqrt(a) 16114     | diff:          238885632      5168     10336      5168
// 10          976000081     13971     27946  AG(x) =      13970, sqrt(a) 31241     | diff:          716339085      6765     13530      6765
// 11        12198539809     49393     98790  AG(x) =      49392, sqrt(a) 110447    | diff:        11222539728     35422     70844     35422
// 12        45851228641     95761    191526  AG(x) =      95760, sqrt(a) 214129    | diff:        33652688832     46368     92736     46368
// 13       573071710225    338547    677098  AG(x) =     338546, sqrt(a) 757015    | diff:       527220481584    242786    485572    242786
// 14      2154031746244    656358   1312720  AG(x) =     656357, sqrt(a) 1467662   | diff:      1580960036019    317811    635622    317811
// 15     26922171840964   2320438   4640880  AG(x) =    2320437, sqrt(a) 5188658   | diff:     24768140094720   1664080   3328160   1664080
// 16    101193640845025   4498747   8997498  AG(x) =    4498746, sqrt(a) 10059505  | diff:     74271469004061   2178309   4356618   2178309
// 17   1264769004815281  15904521  31809046  AG(x) =   15904520, sqrt(a) 35563591  | diff:   1163575363970256  11405774  22811548  11405774
// 18   4753947087970129  30834873  61669750  AG(x) =   30834872, sqrt(a) 68948873  | diff:   3489178083154848  14930352  29860704  14930352
// 19  59417221054477441 109011211 218022426  AG(x) =  109011210, sqrt(a) 243756479 | diff:  54663273966507312  78176338 156352676  78176338
// 20 223334319493751236 211345366 422690736  AG(x) =  211345365, sqrt(a) 472582606 | diff: 163917098439273795 102334155 204668310 102334155
// 21 2791344620555624644 747173958 1494347920  AG(x) =  747173957  sqrt(a) 1670731762 | diff: 2568010301061873408 535828592 1071657184 535828592
// 22 10491959069118338161 1448582691 2897165386  AG(x) =  1448582690  sqrt(a) 3239129369 | diff: 7700614448562713517 701408733 1402817466 701408733
// 23 131133779945059881025 5121206497 10242412998  AG(x) =  5121206496  sqrt(a) 11451365855 | diff: 120641820875941542864 3672623806 7345247612 3672623806

//  1  AG(x) =          2, sqrt(a) 7
//  2  AG(x) =          5, sqrt(a) 14         = SORR( 5)
//  3  AG(x) =         21, sqrt(a) 50
//  4  AG(x) =         42, sqrt(a) 97         = SORR( 9)
//  5  AG(x) =        152, sqrt(a) 343
//  6  AG(x) =        296, sqrt(a) 665        = SORR(13)
//  7  AG(x) =       1050, sqrt(a) 2351
//  8  AG(x) =       2037, sqrt(a) 4558       = SORR(17)
//  9  AG(x) =       7205, sqrt(a) 16114
// 10  AG(x) =      13970, sqrt(a) 31241      = SORR(21)
// 11  AG(x) =      49392, sqrt(a) 110447
// 12  AG(x) =      95760, sqrt(a) 214129     = SORR(25)

// SORR(  1 ) =        1 // SORR(  2 ) =        4 // SORR(  3 ) =       5 // SORR(  4 ) =       9
// SORR(  5 ) =       14 // SORR(  6 ) =       23 // SORR(  7 ) =      37 // SORR(  8 ) =      60
// SORR(  9 ) =       97 // SORR( 10 ) =      157 // SORR( 11 ) =     254 // SORR( 12 ) =     411
// SORR( 13 ) =      665 // SORR( 14 ) =     1076 // SORR( 15 ) =    1741 // SORR( 16 ) =    2817
// SORR( 17 ) =     4558 // SORR( 18 ) =     7375 // SORR( 19 ) =   11933 // SORR( 20 ) =   19308
// SORR( 21 ) =    31241 // SORR( 22 ) =    50549 // SORR( 23 ) =   81790 // SORR( 24 ) =  132339
// SORR( 25 ) =   214129 // SORR( 26 ) =   346468 // SORR( 27 ) =  560597 // SORR( 28 ) =  907065

// fibonacci numbers QMap((0, 0)(1, 1)(2, 1)(3, 2)(4, 3)(5, 5)(6, 8)(7, 13)(8, 21)(9, 34)(10, 55)(11, 89)(12, 144)(13, 233)(14, 377)(15, 610)(16, 987)(17, 1597)(18, 2584)(19, 4181)(20, 6765)(21, 10946)(22, 17711)(23, 28657)(24, 46368)(25, 75025)(26, 121393)(27, 196418)(28, 317811)(29, 514229)(30, 832040)(31, 1346269)(32, 2178309)(33, 3524578)(34, 5702887)(35, 9227465)(36, 14930352)(37, 24157817)(38, 39088169)(39, 63245986))
void testInputOutputCorrelation2() { // yields sqrt(a) for even nuggets. Did not use this for the solution in the end.
    auto F = initLazySecondOrderRecurrenceRelation();

    mpz_class agx  =  0;
    mpz_class c    =  6;
    mpz_class b    =  1;
    mpz_class a    =  1;
    mpz_class addA = 19;

    int i = 0;
    while (i <= 30) {
        mpz_class sqrtA = lazySecondOrderRecurrenceRelation(1 + (i/2)*4, &F);
        qDebug() << i << sqrtA << 1 + (i/2)*4;
        i += 2;
    }
}

// Nugget             a              sqrt(a)    sqrt(a) = SORR(k)
//  0                          1             1         1
//  2                        196            14         5
//  4                       9409            97         9
//  6                     442225           665        13
//  8                   20775364          4558        17
// 10                  976000081         31241        21
// 12                45851228641        214129        25
// 14              2154031746244       1467662        29
// 16            101193640845025      10059505        33
// 18           4753947087970129      68948873        37
// 20         223334319493751236     472582606        41
// 22       10491959069118338161    3239129369        45
// 24      492898741929068142529   22201322977        49
// 26    23155748911597084360900  152170131470        53
// 28  1087827300103133896819969 1042989597313        57
// 30 51104727355935696066177841 7148757049721        61

void testDiffOfDiffs() {// yields the diffdiffs given the list of diffs

    QList<s64> diffs = { 0, 2, 3, 16, 21, 110, 144, 754, 987, 5168, 6765, 35422, 46368, 242786, 317811, 1664080, 2178309, 11405774, 14930352, 78176338, 102334155, 535828592, 701408733, 3672623806 };

    for (int i = 1; i < diffs.size(); i += 1) {
        qDebug() << i << diffs[i] << diffs[i] - diffs[i-1];
    }
}
// Nuggets with diff diff:
// Nugget      agx       diff       diffdiff   diffdiff's F_k
//  1,          2,         2,           2        3
//  2,          5,         3,           1        1
//  3,         21,        16,          13        7
//  4,         42,        21,           5        5
//  5,        152,       110,          89       11
//  6,        296,       144,          34        9
//  7,       1050,       754,         610       15
//  8,       2037,       987,         233       13
//  9,       7205,      5168,        4181       19

void testInputOutputCorrelationWithDiffOfDiffs() {

    mpz_class count = 0;

    auto F = initLazyFibonacci();

    mpz_class agx    = 2;
    s64 diffdiff_fib = 3;
    mpz_class diff   = 2;

    int i = 1;
    while (i <= 30) {

        count += agx;

        qDebug() << i << agx << count;

        if (i%2 == 1) {
            diffdiff_fib -= 2;
        } else {
            diffdiff_fib += 6;
        }

        diff += lazyFibonacci(diffdiff_fib, &F);
        agx += diff;

        i += 1;
    }

    qDebug() << "count:" << count << "(this is the solution)";
}
//  1 2
//  2 5
//  3 21
//  4 42
//  5 152
//  6 296
//  7 1050
//  8 2037
//  9 7205
// 10 13970
// 11 49392
// 12 95760
// 13 338546
// 14 656357
// 15 2320437
// 16 4498746
// 17 15904520
// 18 30834872
// 19 109011210
// 20 211345365
// 21 747173957
// 22 1448582690
// 23 5121206496
// 24 9928733472
// 25 35101271522
// 26 68052551621
// 27 240587694165
// 28 466439127882
// 29 1649012587640
// 30 3197021343560
// count: 5673835352990 (this is the solution)
