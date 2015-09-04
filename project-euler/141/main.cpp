#include <cassert>
#include <cmath>

#include <QtDebug>
#include <QTime>

using s64 = int64_t;
using f64 = double;

s64 squareRootCeil(s64 nn) {
    return (s64) ceil(sqrt(nn));
}

s64 squareRootFloor(s64 nn) {
    return (s64) floor(sqrt(nn));
}

bool isSquare(s64 nn) {
    assert(nn >= 1);
    s64 n = squareRootFloor(nn);
    return n*n == nn || (n+1)*(n+1) == nn;
}

bool isGeometricProgression(s64 a1, s64 a2, s64 a3) {
    //assert(a1 <= a2); // holds, commented out for greater speed
    //assert(a2 <= a3);

    auto q1n = a2;
    auto q1d = a1;
    auto q2n = a3;
    auto q2d = a2;

    //if (q1n > 1000000000 || q1d > 1000000000 || q2n > 1000000000 || q2d > 1000000000) {// if we multiply too big numbers, s64 doesn't suffice
    //    qDebug() << "Fatal: One is too large: " << q1n << q1d << q2n << q2d;
    //    assert(false);
    //}

    // Idea:
    // a2 / a1 = s // (k*(s)^(x+1)) / (k*(s)^(x+0)) = s
    // a3 / a2 = s // (k*(s)^(x+2)) / (k*(s)^(x+1)) = s
    // Then check if a2/a1 == a3/a2. I.e. s is the same for both cases

    auto q1n2 = q1n * q2d; // equalize denominators
    auto q2n2 = q2n * q1d;

    ////Note: We can likely leave this out, because:
    ////n = d*q + r, a1 = r, a2 = d, a3 = q
    ////n < 10^12
    ////d < sqrt(10^12) = 10^6
    ////d*q <= n
    ////therefore q1n2 and q2n2 should not excede n = 10^12, which is smaller than 2^63-1, or ~10^18
    //if (q1n2 < 0 || q2n2 < 0) {// if we multiply too big numbers, s64 doesn't suffice. (Above, alternative condition happens too fast)
    //    qDebug() << "Fatal: Integeroverflow: " << q1n << q1d << q2n << q2d << " -> " << q1n2 << q2n2;
    //    assert(false);
    //}

    //if (q1n2 == q2n2) {
    //    qDebug() << "s" << a2 / (f64) a1 << a2 << a1;
    //}

    return q1n2 == q2n2;
}

void test1();
void test2();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    test1();
    test2();

    return 0;
}

void test1() {
    qDebug() << QString("%1 = %2 * %3 + %4").arg("  n").arg("  q").arg("  d").arg("  r");
    for (s64 n = 1; n <= 1000; n += 1) {
        for (s64 d = 1; d <= squareRootFloor(n); d += 1) {
            s64 q = n/d;
            s64 r = n - q*d;

            // if (r == 0) { continue; } // 0 is not part of a geometric progression unless all terms are 0

            assert(q >= d);
            assert(d >= r);

            //bool nHasGeometricProgression = isGeometricProgressionSearch(r, d, q, 10, nullptr);
            bool nHasGeometricProgression = isGeometricProgression(r, d, q);

            if (nHasGeometricProgression) {
                qDebug() << QString("%1 = %2 * %3 + %4").arg(n, 3).arg(q, 3).arg(d, 3).arg(r, 3);
            }
        }
    }
}

//   9 =   4 *   2 +   1
//  28 =   9 *   3 +   1
//  34 =   8 *   4 +   2
//  58 =   9 *   6 +   4
//  65 =  16 *   4 +   1
//  75 =  12 *   6 +   3
// 110 =  18 *   6 +   2
// 126 =  25 *   5 +   1
// 132 =  16 *   8 +   4
// 201 =  16 *  12 +   9
// 205 =  20 *  10 +   5
// 217 =  36 *   6 +   1
// 224 =  18 *  12 +   8
// 246 =  27 *   9 +   3
// 254 =  25 *  10 +   4
// 258 =  32 *   8 +   2
// 294 =  24 *  12 +   6

void test2() {
    qDebug() << QString("%1 = %2 * %3 + %4, %5").arg("         n").arg("    q").arg("    d").arg("    r").arg("       sum");
    s64 sum = 0;
    s64 minN = squareRootFloor( 1);
    s64 maxN = squareRootFloor(1000000000000);
    s64 nn, q, r;
    for (s64 n = minN; n <= maxN; n += 1) {
        nn = n*n;

        // if (n % 10000 == 0) { // progress indicator
        //     qDebug() << nn;
        // }

        for (s64 d = 1; d <= n; d += 1) {
            q = nn/d;
            r = nn - q*d;

            //if (r == 0) { continue; } // 0 is not part of a geometric progression unless all terms are 0

            //assert(q >= d); // holds, commented out for greater speed
            //assert(d >= r);

            if (isGeometricProgression(r, d, q)) {
                sum += nn;
                qDebug() << QString("%1 = %2 * %3 + %4, %5").arg(nn, 10).arg(q, 5).arg(d, 5).arg(r, 5).arg(sum, 10);
            }
        }
    }
}

//            n =      q *      d +      r                      n                q            d        r
//            9 =      4 *      2 +      1,                   3 3,             2 2,           2,       1
//        10404 =    144 *     72 +     36,         2 2 3 3 17 17,     2 2 2 2 3 3,   2 2 2 3 3, 2 2 3 3
//        16900 =    225 *     75 +     25,         2 2 5 5 13 13,         3 3 5 5,       3 5 5,     5 5
//        97344 =   1058 *     92 +      8, 2 2 2 2 2 2 3 3 13 13,         2 23 23,      2 2 23,   2 2 2
//       576081 =   1600 *    360 +     81,       3 3 11 11 23 23, 2 2 2 2 2 2 5 5, 2 2 2 3 3 5, 3 3 3 3
//      6230016 =   4232 *   1472 +    512,
//      7322436 =   3025 *   2420 +   1936
//     12006225 =   4900 *   2450 +   1225
//     36869184 =   6400 *   5760 +   5184
//     37344321 =   7056 *   5292 +   3969
//     70963776 =   9522 *   7452 +   5832
//    196112016 =  44652 *   4392 +    432
//    256160025 =  39204 *   6534 +   1089
//   1361388609 =  44100 *  30870 +  21609
//   1380568336 =  53361 *  25872 +  12544
//   8534988225 = 112896 *  75600 +  50625
//   9729849600 = 123201 *  78975 +  50625
//  12551169024 = 178608 *  70272 +  27648
//  13855173264 = 166464 *  83232 +  41616
//  16394241600 = 156816 * 104544 +  69696
// 123383587600 = 608400 * 202800 +  67600
// 142965659664 = 401868 * 355752 + 314928
// 547674002500 = 831744 * 658464 + 521284
//
// sum of all n's = solution = 878454337159
//
//           n   s
//           9   2
//       10404   2
//       16900   3
//       97344  11.5
//      576081   4.44444 =   360 /   81
//     6230016   2.875   =  1472 /  512
//     7322436   1.25
//    12006225   2
//    36869184   1.11111 =  5760 / 5184
//    37344321   1.33333 =  5292 / 3969
//    70963776   1.27778 =  7452 / 5832
//   196112016  10.1667  =  4392 /  432
//   256160025   6
//  1361388609   1.42857 = 30870 / 21609
//  1380568336   2.0625  = 25872 / 12544
//  8534988225   1.49333 = 75600 / 50625
//  9729849600   1.56    = 78975 / 50625
// 12551169024   2.54167 = 70272 / 27648
// 13855173264   2
// 16394241600   1.5
