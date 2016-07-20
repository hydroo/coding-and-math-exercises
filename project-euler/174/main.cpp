#include "../lib.hpp"

int squareLamina(int holeDiameter, int thickness) {
    if (thickness <= 0) { return 0; }
    else                { return (holeDiameter+2) * 2 + holeDiameter*2 + squareLamina(holeDiameter+2, thickness-1); }
}

QHash<s64, s64> squareLaminaeTypeCount(int minTiles, int maxTiles) {

    QHash<s64 /*tiles*/, s64 /*type*/> types;
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
            if (n >= minTiles && n <= maxTiles) {

                if (types.contains(n) == false) { types.insert(n, 0); }
                types[n] += 1;

                ret += 1;
            }
            thickness += 1;
        } while (n < maxTiles);
        holeDiameter += 1;

    } while (!(n >= maxTiles && n2 >= maxTiles));

    QHash<s64, s64> reverseTypes;
    QHashIterator<s64, s64> i(types);
    while (i.hasNext()) {
        i.next();
        if (reverseTypes.contains(i.value()) == false) {
            reverseTypes.insert(i.value(), 0);
        }
        reverseTypes[i.value()] += 1;
    }

    return reverseTypes;
}

void test1();

int main() {
    test1();
    return 0;
}

void test1() {

    //qDebug() << squareLaminaeTypeCount(8 ,8);
    assert(squareLaminaeTypeCount(8, 8)[1] == 1);
    //qDebug() << squareLaminaeTypeCount(32 ,32);
    assert(squareLaminaeTypeCount(32, 32)[2] == 1);

    auto m = squareLaminaeTypeCount(1, 1000 * 1000);
    qDebug() << m;
    s64 sum = 0;
    for (int i = 1; i <= 10; i += 1) {
        qDebug() << i << m[i];
        sum += m[i];
    }
    qDebug() << sum << "!!!";

    assert(m[15] == 832);
}
