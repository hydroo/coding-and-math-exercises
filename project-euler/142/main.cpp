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
void test2();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    test1();
    test2();

    return 0;
}

void test1() {

    s64 minX = 3;
    s64 maxX = 10000;
    for (s64 x = minX; x < maxX; x += 1) {
        if (x % 30000 == 0) {
            qDebug() << x;
        }
        for (s64 y = 2; y < x; y += 1) {

            if (isSquare(x + y) == false || isSquare(x - y) == false) { continue; }

            for (s64 z = 1; z < y; z += 1) {
                if (isSquare(x + z) && isSquare(x - z) && isSquare(y + z) && isSquare(y - z)) {
                    qDebug() << x + y + z << x << y << z;
                }
            }
        }
    }
}

void test2() {

    s64 maxN = squareRootFloor(1000000);

    QSet<s64> squares;

    for (s64 n = 1; n <= maxN; n += 1) {
        s64 nn = n*n;

        squares << nn;

        if (n % 100 == 0) {
            qDebug() << nn;
        }

        for (s64 y = 2; y < n*n/2; y += 1) {
            s64 x= nn - y;
            //assert(x > y); // holds, commented out for more speed

            s64 mm = x-y;

            if (squares.contains(mm) == false) { continue; }

            for (s64 z = 1; z < y; z += 1) {

                if (squares.contains(x+z) && squares.contains(x-z) && squares.contains(y+z) && squares.contains(y-z)) {
                    qDebug() << x + y + z << x << y << z;
                }
            }
        }
    }
}
