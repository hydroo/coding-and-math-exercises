#include <cassert>
#include <cmath>

#include <QtDebug>

using s64 = int64_t;

using namespace std;


int divisorCount(s64 n) {
    int ret = 0;

    s64 sqrtn = (s64) floor(sqrt(n));
    for (auto d = 1; d <= sqrtn; d += 1) {
        if (n % d == 0) {
            ret += 2;
        }
    }

    if (sqrtn*sqrtn == n) {
        ret -= 1;
    }

    return ret;
}

void test1();
void doIt();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    test1();

    doIt();

    return 0;
}

void doIt() {
    int solution = 0;
    int lastDivCount = -1;
    for (s64 n = 2; n < 10 * 1000 * 1000; n += 1) {
        auto divCount = divisorCount(n);

        if (divCount == lastDivCount) {
            solution += 1;
        }
        lastDivCount = divCount;

        if (n % 100000 == 0) {
            qDebug() << n << solution;
        }
    }
    qDebug() << solution;
}

void test1() {
    assert(divisorCount(1)  == 1);
    assert(divisorCount(2)  == 2);
    assert(divisorCount(3)  == 2);
    assert(divisorCount(4)  == 3);
    assert(divisorCount(5)  == 2);
    assert(divisorCount(6)  == 4);
    assert(divisorCount(7)  == 2);
    assert(divisorCount(8)  == 4);
    assert(divisorCount(9)  == 3);
    assert(divisorCount(10) == 4);
    assert(divisorCount(11) == 2);
    assert(divisorCount(12) == 6);
    assert(divisorCount(13) == 2);
    assert(divisorCount(14) == 4);
}
