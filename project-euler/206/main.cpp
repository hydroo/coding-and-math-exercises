#include <cassert>
#include <cmath>

#include <QtDebug>

using s64 = int64_t;

s64 squareRootFloor(s64 nn) {
    return (s64) floor(sqrt(nn));
}

bool isSquare(s64 nn) {
    assert(nn >= 1);
    s64 n = squareRootFloor(nn);
    return n*n == nn || (n+1)*(n+1) == nn;
}

void test1();

int main() {

    test1();

    return 0;
}

void test1() {

    for (s64 i1 = 0; i1 < 10; i1 += 1) {
    for (s64 i2 = 0; i2 < 10; i2 += 1) {
    for (s64 i3 = 0; i3 < 10; i3 += 1) {
    for (s64 i4 = 0; i4 < 10; i4 += 1) {
    for (s64 i5 = 0; i5 < 10; i5 += 1) {
    for (s64 i6 = 0; i6 < 10; i6 += 1) {
    for (s64 i7 = 0; i7 < 10; i7 += 1) {
    for (s64 i8 = 0; i8 < 10; i8 += 1) {
    for (s64 i9 = 0; i9 < 10; i9 += 1) {

        s64 n =    1 * 1000000000000000000
                + i1 * 100000000000000000
                + 2  * 10000000000000000
                + i2 * 1000000000000000
                + 3  * 100000000000000
                + i3 * 10000000000000
                + 4  * 1000000000000
                + i4 * 100000000000
                + 5  * 10000000000
                + i5 * 1000000000
                + 6  * 100000000
                + i6 * 10000000
                + 7  * 1000000
                + i7 * 100000
                + 8  * 10000
                + i8 * 1000
                + 9  * 100
                + i9 * 10
                + 0  * 1;

        if (isSquare(n)) {
            qDebug() << squareRootFloor(n);
        }
    }
    }
    }
    }
    }
    }
    }
    }
    }
}
