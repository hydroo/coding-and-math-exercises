#include "../lib.hpp"

u64 nimSum(u64 a, u64 b, u64 c) {
    return a ^ b ^ c;
}

void test1();

int main() {
    test1();
    return 0;
}

void test1() {
    assert(nimSum(1, 2, 3) == 0);

    s64 count = 0;
    for (u64 n = 1; n <= 1<<30; n += 1) {
        if (nimSum(n, 2*n, 3*n) == 0) {
            count += 1;
        }
    }

    qDebug() << count << "!!!";
}
