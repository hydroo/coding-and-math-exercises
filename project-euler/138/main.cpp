#include <cassert>
#include <cmath>
#include <gmpxx.h>

#include <QtDebug>

QDebug operator<<(QDebug s, const mpz_class& m) {
    char b[65536] = "";
    gmp_sprintf (b, "%Zd", m.get_mpz_t());
    s << b;
    return s;
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

void isSpecialIsoscelesTriangle(mpz_class b /* base */, mpz_class* cc1_, mpz_class* cc2_) {
    assert(b % 2 == 0); //isEven

    mpz_class a = b / 2;
    mpz_class b1 = b-1;
    mpz_class b2 = b+1;

    mpz_class cc1 = a*a + b1*b1;
    mpz_class cc2 = a*a + b2*b2;

    if (isSquare(cc1)) { *cc1_ = cc1; }
    else               { *cc1_ = -1;  }
    if (isSquare(cc2)) { *cc2_ = cc2; }
    else               { *cc2_ = -1;  }
}

void test1();
void test2();

int main() {

    //test1();
    test2();

    return 0;
}

void test1() {

    struct SpecialIsoscelesTriange {
        mpz_class b, h, L;
    };

    QList<SpecialIsoscelesTriange> triangles;
    triangles << SpecialIsoscelesTriange{0, 0, 0};

    mpz_class L1, L2;

    mpz_class b = 2;
    int i = 1;

    for (;;) {
        isSpecialIsoscelesTriangle(b, &L1, &L2);

        if (L1 != -1) {
            qDebug() << i << b << b-1 << squareRoot(L1) << "diff" << b - triangles.last().b << (b-1) - (triangles.last().h) << squareRoot(L1) - triangles.last().L;
            triangles << SpecialIsoscelesTriange{b, b-1, squareRoot(L1)};
            i += 1;
        }
        if (L2 != -1) {
            qDebug() << i << b << b+1 << squareRoot(L2) << "diff" << b - triangles.last().b << (b-1) - (triangles.last().h) << squareRoot(L2) - triangles.last().L;
            triangles << SpecialIsoscelesTriange{b, b-1, squareRoot(L2)};
            i += 1;
        }

        if (i == 13) {
            break;
        }

        b += 2;
    }
}

void test2() {

    mpz_class sumOfL = 0;

    mpz_class L1, L2;

    mpz_class b = 0;
    mpz_class bAddRoot = 1;
    mpz_class lastSucessfulB = 0;
    int i = 1;

    for (;;) {

        b = lastSucessfulB + bAddRoot*bAddRoot;

        if (b % 2 == 0) {

            isSpecialIsoscelesTriangle(b, &L1, &L2);

            if (L1 != -1) {
                sumOfL += squareRoot(L1);
                qDebug() << i << b << b-1 << squareRoot(L1) << sumOfL;
                lastSucessfulB = b;
                //bAddRoot = 0;
                i += 1;
                if (i == 13) { break; }
            }
            if (L2 != -1) {
                sumOfL += squareRoot(L2);
                qDebug() << i << b << b+1 << squareRoot(L2) << sumOfL;
                lastSucessfulB = b;
                //bAddRoot = 0;
                i += 1;
                if (i == 13) { break; }
            }

            if (L1 != -1 && L2 != -1) {
                qDebug() << "Warning: Surprise L1 and are hits.";
            }
        }

        bAddRoot += 1;
    }

    qDebug() << "Solution:" << sumOfL;
}

// 1       16       15       17
// 2      272      273      305
// 3     4896     4895     5473
// 4    87840    87841    98209
// 5  1576240  1576239  1762289
// 6 28284464 28284465 31622993
//
// 1       16       15       17 diff       16       15       17
// 2      272      273      305 diff      256      256      288
// 3     4896     4895     5473 diff     4624     4624     5168
// 4    87840    87841    98209 diff    82944    82944    92736
// 5  1576240  1576239  1762289 diff  1488400  1488400  1664080
// 6 28284464 28284465 31622993 diff 26708224 26708224 29860704
