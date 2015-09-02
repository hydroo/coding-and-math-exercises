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

    f64 r1 = a2 / (f64) a1; // (k*(r^p+1)) / (k*(r^p  )) = r
    f64 r2 = a3 / (f64) a2; // (k*(r^p+2)) / (k*(r^p+1)) = r

    return fabs(r1 - r2) <= 0.0000001;
}

void test1();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    test1();

    return 0;
}

void test1() {
    qDebug() << "Warning: Results have to be verified. False positives are possible.";
    qDebug() << QString("%1 = %2 * %3 + %4, %5").arg("  n").arg("  q").arg("  d").arg("  r").arg("hit");
    for (s64 n = 1; n < 300; n += 1) {
        for (s64 d = 1; d <= squareRootFloor(n); d += 1) {
            s64 q = n/d;
            s64 r = n - q*d;

            if (r == 0) { continue; } // 0 is not part of a geometric progression unless all terms are 0

            assert(q >= d);
            assert(d >= r);

            //bool nHasGeometricProgression = isGeometricProgressionSearch(r, d, q, 10, nullptr);
            bool nHasGeometricProgression = isGeometricProgression(r, d, q);

            if (nHasGeometricProgression) {
                qDebug() << QString("%1 = %2 * %3 + %4, %5").arg(n, 3).arg(q, 3).arg(d, 3).arg(r, 3).arg(nHasGeometricProgression ? 'x' : ' ');
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
