#include "../lib.hpp"

int squareLamina(int holeDiameter, int thickness) {
    if (thickness <= 0) { return 0; }
    else                { return (holeDiameter+2) * 2 + holeDiameter*2 + squareLamina(holeDiameter+2, thickness-1); }
}

int numberOfSquareLaminae(int maxTiles) {

    int ret = 0;
    int n = 0;
    int n2 = 0;

    int holeDiameter = 1;
    do {
        int thickness = 1;
        do {
            //qDebug() << holeDiameter << thickness << n;
            n2 = n;
            n = squareLamina(holeDiameter, thickness);
            if (n <= maxTiles) {
                ret += 1;
            }
            thickness += 1;
        } while (n < maxTiles);
        holeDiameter += 1;

    } while (!(n >= maxTiles && n2 >= maxTiles));

    return ret;
}

void test1();

int main() {
    test1();
    return 0;
}

void test1() {
    assert(squareLamina(2, 2) == 32);
    assert(squareLamina(7, 1) == 32);

    qDebug() << numberOfSquareLaminae(100);
    assert(numberOfSquareLaminae(100) == 41);

    qDebug() << "10^3" << numberOfSquareLaminae(1000);
    qDebug() << "10^4" << numberOfSquareLaminae(10000);
    qDebug() << "10^5" << numberOfSquareLaminae(100000);
    qDebug() << "10^6" << numberOfSquareLaminae(1000000) << "!!!";
}

