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

struct GeometricProgressionParameters { // k*(rn/rd)^p, k*(rn/rd)^(p+1), k*(rn/rd)^(p+2)
    s64 k, rn, rd, p;
};

// // this is crap isGeometricProgression() should be better
// bool isGeometricProgressionSearch(s64 a1, s64 a2, s64 a3, s64 maxSearchSpace, QList<GeometricProgressionParameters>* progressions) {
//     assert(a1 <= a2);
//     assert(a2 <= a3);
// 
//     if (progressions != nullptr) { progressions->clear(); }
// 
//     bool ret = false;
// 
//     for (s64 k = 0; k <= maxSearchSpace; k += 1) {
//         for (s64 rn = 1; rn <= maxSearchSpace; rn += 1) {
//             for (s64 rd = 1; rd <= maxSearchSpace; rd += 1) {
//                 for (s64 p = 0; p <= maxSearchSpace; p += 1) {
// 
//                     f64 b1 = k*pow(((f64) rn / (f64) rd), p  );
//                     f64 b2 = k*pow(((f64) rn / (f64) rd), p+1);
//                     f64 b3 = k*pow(((f64) rn / (f64) rd), p+2);
// 
//                     if (fabs(a1 - b1) <= 0.0000001 && fabs(a2 - b2) <= 0.0000001 && fabs(a3 - b3) <= 0.0000001) {
//                         //qDebug() << a1 << a2 << a3 << b1 << b2 << b3 << fabs(a1 - b1) << fabs(a2 - b2) << fabs(a3 - b3);
//                         if (progressions != nullptr) {
//                             progressions->append(GeometricProgressionParameters{k, rn, rd, p});
//                             ret = true;
//                         } else { // return immediatelly when are not interested in the parameters
//                             return true;
//                         }
//                     }
//                 }
//             }
//         }
//     }
// 
//     return ret;
// }

bool isGeometricProgression(s64 a1, s64 a2, s64 a3) {
    assert(a1 <= a2);
    assert(a2 <= a3);

    auto q1n = a2;
    auto q1d = a1;
    auto q2n = a3;
    auto q2d = a2;

    //if (q1n > 1000000000 || q1d > 1000000000 || q2n > 1000000000 || q2d > 1000000000) {// if we multiply too big numbers, s64 doesn't suffice
    //    qDebug() << "Fatal: One is too large: " << q1n << q1d << q2n << q2d;
    //    assert(false);
    //}

    auto q1n2 = q1n * q2d; // equalize denominators
    auto q2n2 = q2n * q1d;

    if (q1n2 < 0 || q2n2 < 0) {// if we multiply too big numbers, s64 doesn't suffice. (Above, alternative condition happens too fast)
        qDebug() << "Fatal: Integeroverflow: " << q1n << q1d << q2n << q2d << " -> " << q1n2 << q2n2;
        assert(false);
    }

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
    s64 maxN = squareRootFloor(100000000);
    for (s64 n = 1; n <= maxN; n += 1) {
        s64 nn = n*n;
        for (s64 d = 1; d <= n; d += 1) {
            s64 q = nn/d;
            s64 r = nn - q*d;

            // if (r == 0) { continue; } // 0 is not part of a geometric progression unless all terms are 0

            assert(q >= d);
            assert(d >= r);

            //bool nHasGeometricProgression = isGeometricProgressionSearch(r, d, q, 10, nullptr);
            bool nHasGeometricProgression = isGeometricProgression(r, d, q);

            if (nHasGeometricProgression) {
                sum += nn;
                qDebug() << QString("%1 = %2 * %3 + %4, %5").arg(nn, 10).arg(q, 5).arg(d, 5).arg(r, 5).arg(sum, 10);
            }
        }
    }
}

//        n =     q *     d +     r,        sum                                  n                q               d                  r
//        9 =     4 *     2 +     1,          9                                3 3,             2 2,              2,                 1
//    10404 =   144 *    72 +    36,      10413,                     2 2 3 3 17 17,     2 2 2 2 3 3,      2 2 2 3 3,           2 2 3 3
//    16900 =   225 *    75 +    25,      27313,                     2 2 5 5 13 13,         3 3 5 5,          3 5 5,               5 5
//    97344 =  1058 *    92 +     8,     124657,             2 2 2 2 2 2 3 3 13 13,         2 23 23,         2 2 23,             2 2 2
//   576081 =  1600 *   360 +    81,     700738,                   3 3 11 11 23 23, 2 2 2 2 2 2 5 5,    2 2 2 3 3 5,           3 3 3 3
//  6230016 =  4232 *  1472 +   512,    6930754, 2 2 2 2 2 2 2 2 2 2 2 2 3 3 13 13,     2 2 2 23 23, 2 2 2 2 2 2 23, 2 2 2 2 2 2 2 2 2
//  7322436 =  3025 *  2420 +  1936,   14253190
// 12006225 =  4900 *  2450 +  1225,   26259415
// 36869184 =  6400 *  5760 +  5184,   63128599
// 37344321 =  7056 *  5292 +  3969,  100472920
// 70963776 =  9522 *  7452 +  5832,  171436696
