#include "../lib.hpp"

s64 priceStringCount(int maxN) {

    function<s64(int, int, int)> traverse = [&traverse, maxN](int n, int late, int consecutivelyAbsent) -> s64 {

        if (late == 2 || consecutivelyAbsent == 3) {
            return 0;
        } else if (n == maxN) {
            return 1;
        }

        s64 ret = 0;

        ret += traverse(n+1, late    , 0);
        ret += traverse(n+1, late + 1, 0);
        ret += traverse(n+1, late    , consecutivelyAbsent + 1);

        return ret;
    };

    return traverse(0, 0, 0);
}

void test1();

int main() {

    test1();

    return 0;
}

void test1() {
    qDebug() << 4 << priceStringCount(4);
    assert(priceStringCount(4) == 43);

    qDebug() << 10 << priceStringCount(10);
    qDebug() << 20 << priceStringCount(20);
    qDebug() << 25 << priceStringCount(25);
    qDebug() << 30 <<  priceStringCount(30);
}
