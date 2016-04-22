#include <cassert>
#include <cmath>

#include <QtDebug>

using s64 = int64_t;

//int log10floori(int64_t a) {
//    assert(a != 0);
//    int l = 0;
//    while (a > 9) {
//        a /= 10;
//        l += 1;
//    }
//    return l;
//}

int64_t reverse(int64_t a) {
    assert(a >= 0);

    int64_t b = 0;
    int p = 1;

    while (a > 0) {
        b *= 10;
        b += (a % 10);
        a /= 10;
        p += 1;
    }
    return b;
}

bool onlyOddDigits(int64_t a) {
    while (a > 0) {
        if (a % 2 == 0) {
            return false;
        }
        a /= 10;
    }
    return true;
}

//void test_log10floori();
void test_reverse();
void test_onlyOddDigits();
void test1();
void test2();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    //test_log10floori();
    test_reverse();
    test_onlyOddDigits();

    test1();
    test2();

    return 0;
}

//void test_log10floori() {
//    assert(log10floori(-100) == 0);
//    assert(log10floori(-  1) == 0);
//    assert(log10floori(   1) == 0);
//    assert(log10floori(   9) == 0);
//    assert(log10floori(  10) == 1);
//    assert(log10floori(  99) == 1);
//    assert(log10floori( 100) == 2);
//}

void test_reverse() {
    assert(reverse(  0) ==   0);
    assert(reverse(  9) ==   9);
    assert(reverse( 10) ==   1);
    assert(reverse( 45) ==  54);
    assert(reverse(120) ==  21);
    assert(reverse(123) == 321);
}

void test_onlyOddDigits() {
    assert(onlyOddDigits(  1) == true );
    assert(onlyOddDigits(  2) == false);
    assert(onlyOddDigits( 34) == false);
    assert(onlyOddDigits( 55) == true );
    assert(onlyOddDigits( 67) == false);
    assert(onlyOddDigits( 68) == false);
    assert(onlyOddDigits(135) == true );
}

void test1() {
    int count = 0;
    for (auto a = 0; a < 1000; a += 1) {
        if (a % 10 == 0) { continue; }
        if (onlyOddDigits(a + reverse(a)) == true) {
            count += 1;
        }
    }
    assert(count == 120);
}

void test2() {
    int count = 0;
    for (auto a = 0; a < 1000000000; a += 1) {
        if (a % 10 == 0) { continue; }
        if (onlyOddDigits(a + reverse(a)) == true) {
            count += 1;
        }
    }
    qDebug() << count;
}
