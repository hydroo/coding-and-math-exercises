#include <cassert>

#include <QtDebug>
#include <gmpxx.h>

using s64 = int64_t;

bool isSquare(const mpz_class& i) {
    mpz_class dummy, remainder;
    mpz_rootrem(dummy.get_mpz_t(), remainder.get_mpz_t(), i.get_mpz_t(), 2);
    return remainder == 0;
}

s64 squareRoot(const mpz_class& i, bool* isSquare = 0) {
    mpz_class root, remainder;
    mpz_rootrem(root.get_mpz_t(), remainder.get_mpz_t(), i.get_mpz_t(), 2);

    if (isSquare != 0) {
        *isSquare = remainder == 0;
    }

    assert(root.fits_slong_p()); // is 64bit on my system. Might become a problem elsewhere

    return mpz_get_si(root.get_mpz_t());
}

void test1(s64 max); // brute force
void test2(s64 max); // brute force + different counting
void test3(s64 max); // more clever

int main() {

    //test1(999);
    //test2(999);
    test3(99999999);

    return 0;
}

void test1(s64 max) {

    //const int places = 5;

    s64 count = 0;

    for(s64 c = 1; c <= max; c += 1) {

        for (s64 b = 1; b < c; b += 1) {

            s64 aa = c*c - b*b;


            bool aIsSquare;
            s64 a = squareRoot(aa, &aIsSquare);

            if (aIsSquare == false) { continue; }

            if (a > b) { continue; }

            if (a + b + c > max /* perimeter */) { continue; }

            bool remainingAreaIsSquare;
            s64 rootOfRemainingArea = squareRoot(c*c - 2*b*a, &remainingAreaIsSquare);

            if (remainingAreaIsSquare == false) { continue; }

            if (c % rootOfRemainingArea == 0) {
                count += 1;
                //qDebug() << QString("(%1, %2, %3): [%4, %4], [%5, %5], count: %8").arg(a, places).arg(b, places).arg(c, places).arg(c, places).arg(rootOfRemainingArea, places).arg(count);
            }

        }
    }

    qDebug() << count;
}

void test2(s64 max) {

    //const int places = 5;

    s64 count = 0;

    QMap<QPair<s64 /*c*/, s64/*b*/>, s64/*count*/> cToCount;

    for(s64 c = 1; c <= max; c += 1) {

        for (s64 b = 1; b < c; b += 1) {

            s64 aa = c*c - b*b;

            bool aIsSquare;
            s64 a = squareRoot(aa, &aIsSquare);

            if (aIsSquare == false) { continue; }

            if (a > b) { continue; }

            if (a + b + c > max) { continue; }

            bool remainingAreaIsSquare;
            s64 rootOfRemainingArea = squareRoot(c*c - 4*(b*a/2), &remainingAreaIsSquare);

            if (remainingAreaIsSquare == false) { continue; }

            if (c % rootOfRemainingArea == 0) {
                count += 1;

                QPair<s64, s64> cb = QPair<s64, s64>(c, b);
                QPair<s64, s64> foundCB = cb;

                QMapIterator<QPair<s64, s64>, s64> i(cToCount);
                while(i.hasNext()) {
                    i.next();
                    if (c % i.key().first == 0 && b % i.key().second == 0) {
                        foundCB = i.key();
                        break;
                    }
                }

                if (cToCount.contains(foundCB) == false) {
                    cToCount[foundCB] = 0;
                }

                cToCount[foundCB] += 1;

                //qDebug() << QString("(%1, %2, %3): [%4, %4], [%5, %5], foundCB: (%6, %7), count: %8").arg(a, places).arg(b, places).arg(c, places).arg(c, places).arg(rootOfRemainingArea, places).arg(foundCB.first, places).arg(foundCB.second, places).arg(count);
            }

        }
    }

    qDebug() << count;

    qDebug() << cToCount;

    s64 count2 = 0;
    QMapIterator<QPair<s64, s64>, s64> i(cToCount);
    while (i.hasNext()) {
        i.next();
        count2 += i.value();
    }

    assert(count == count2);
}

void test3(s64 max) {

    s64 a = 1;
    s64 b = 2;

    s64 count = 0;

    for (;; b += 1) {

        a = b-1;
        s64 cc = a*a + b*b;

        bool cIsSquare;
        s64 c = squareRoot(cc, &cIsSquare);
        if (cIsSquare == false) { continue; }

        if (a + b + c > max) { break; }

        s64 remainingArea = cc - 2*b*a;

        if (remainingArea == 1) {

            count                       += max / (a + b + c);

            qDebug() << QString("(%1, %2, %3), newCount: %4, count: %5").arg(a).arg(b).arg(c).arg(max/(a+b+c)).arg(count);
        }

    }

    qDebug() << "Solution:" << count;
}

