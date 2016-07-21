#include "../lib.hpp"

// straight forward
s64 numberCount1(int digits) {

    function<s64(int, int, int, int)> recurse = [&recurse, digits](int digit, int s1, int s2, int s3) -> s64 {

        if (s1 + s2 + s3 > 9) {
            return 0;
        } else if (digit == 1 && s3 == 0) {
            return 0;
        } else if (digit >= digits) {
            return 1;
        }

        s64 ret = 0;
        for (int d = 0; d <= 9 ; d += 1) {
            ret += recurse(digit + 1, s2, s3, d);
        }
        return ret;

    };

    return recurse(0, 0, 0, 0);
}

// a little more efficient
s64 numberCount2(int digits) {

    function<s64(int, int, int, int)> recurse = [&recurse, digits](int digit, int s1, int s2, int s3) -> s64 {

        if (s1 + s2 + s3 > 9) {
            return 0;
        } else if (digit >= digits) {
            //qDebug() << digit << s1 << s2 << s3;
            return 1;
        }

        s64 ret = 0;
        for (int d = 0; d <= 9 - (s2 + s3); d += 1) {
            ret += recurse(digit + 1, s2, s3, d);
        }
        return ret;

    };

    s64 ret = 0;
    for (int d = 1; d <= 9; d += 1) {
        ret += recurse(1, 0, 0, d);
    }

    return ret;
}

// split the task into two halves, one from the left and one from the right, and then glue the results together in the middle
s64 numberCount3(int digits) {

    function<s64(int, int, int, int, int, QHash<QPair<int, int>, s64>*)> recurse = [&recurse](int digits, int digit, int d1, int d2, int d3, QHash<QPair<int, int>, s64>* last) -> s64 {

        if (digits == 0) {
            return 0;
        } else if (d1 + d2 + d3 > 9) {
            return 0;
        } else if (digit >= digits) {
            //qDebug() << digit << d1 << d2 << d3;
            return 1;
        }

        s64 ret = 0;
        for (int d = 0; d <= 9 - (d2 + d3); d += 1) {
            s64 count = recurse(digits, digit + 1, d2, d3, d, last);

            if (digit >= digits - 1) { // record the first/last two digits along with the number of numbers that end/start this way
                if (last->contains(QPair<int, int>(d3, d)) == false) {
                    (*last)[QPair<int, int>(d3, d)] = 0;
                }
                (*last)[QPair<int, int>(d3, d)] += count;
            }
        }

        return ret;
    };

    QHash<QPair<int, int>, s64> left, right;

    // left-most digits
    for (int d = 1; d <= 9; d += 1) {
        recurse(floor(digits/2.0), 1, 0, 0, d, &left);
    }

    // right-most digits
    for (int d = 0; d <= 9; d += 1) {
        recurse(ceil(digits/2.0), 1, 0, 0, d, &right);
    }

    // multiply numbers if the glue digits fulfill the criterion
    s64 ret = 0;
    QHashIterator<QPair<int, int>, s64> il(left);
    while (il.hasNext()) {
        il.next();

        QHashIterator<QPair<int, int>, s64> ir(right);
        while (ir.hasNext()) {
            ir.next();

            int d1 = il.key().first;
            int d2 = il.key().second;
            int d3 = ir.key().second;
            int d4 = ir.key().first;

            if (d1 + d2 + d3 <= 9 && d2 + d3 + d4 <= 9) {
                ret += il.value() * ir.value();
            }
        }
    }

    return ret;
}

void test1();
void test2();

int main() {
    test1();
    test2();
    return 0;
}

void test2() {

    for (int d = 1; d <= 20; d += 1) {
        //qDebug() << d << numberCount2(d) << numberCount3(d);
        qDebug() << d << numberCount3(d) << (d == 20 ? "!!!!" : "");
    }
}
void test1() {

    assert(numberCount1(1) ==   9);
    assert(numberCount1(2) ==  45);
    assert(numberCount1(3) == 165);
    assert(numberCount1(4) == 990);

    for (int i = 1; i <= 10; i += 1) {
        assert(numberCount1(i) == numberCount2(i));
    }
    for (int i = 4; i <= 10; i += 1) {
        assert(numberCount1(i) == numberCount3(i));
    }
}
