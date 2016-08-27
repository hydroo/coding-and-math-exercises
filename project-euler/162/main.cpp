#include "../lib.hpp"

bool leadingZero(u64 n, int length) {
    return (n>>(length-4)) == 0x0;
}

bool has0(u64 n) {
    int i = 60;
    for ( ; i >= 0; i -= 4) {
        if ((n>>i & 0xf) != 0x0) {
            break;
        }
    }
    i -= 4;

    for ( ; i >= 0; i -= 4) {
        if ((n>>i & 0xf) == 0x0) {
            return true;
        }
    }
    return false;
}

bool has1(u64 n) {
    for (int i = 60 ; i >= 0; i -= 4) {
        if ((n>>i & 0xf) == 0x1) {
            return true;
        }
    }
    return false;
}

bool hasA(u64 n) {
    for (int i = 60 ; i >= 0; i -= 4) {
        if ((n>>i & 0xf) == 0xA) {
            return true;
        }
    }
    return false;
}

s64 bruteForceCount(int length, int initialLength) {

    s64 ret = 0;

    if (length >= 4) {
        ret += bruteForceCount(length-1, initialLength);
    } else if (length == 3) {
        return 4;
    }

    function<s64(int, u64)> recurse = [length, initialLength, &recurse](int pos, u64 n) -> s64 {
        if (pos == length) {
            if (leadingZero(n, length*4) == false && has0(n) && has1(n) && hasA(n)) {
                if (length == initialLength) {
                    //qDebug() << QString("%1").arg(n, 0, 16);
                }
                return 1;
            } else {
                return 0;
            }
        }

        s64 ret = 0;
        for (u64 b = 0x0; b <= 0xf; b += 1) {
            ret += recurse(pos+1, (n<<4) + b);
        }
        return ret;

    };

    return ret + recurse(0, 0);
}

s64 count(int length, int initialLength) {

    auto posToString = [length](int pos0, int pos1, int posA) -> QString {
        QString ret;
        QTextStream s(&ret);
        for (int i = 0; i < length; i += 1) {
            if (i == pos0) {
                s << "0";
            } else if (i == pos1) {
                s << "1";
            } else if (i == posA) {
                s << "A";
            } else {
                s << "x";
            }
        }
        return ret;
    };
    (void) posToString;

    s64 ret = 0;

    if (length >= 4) {
        ret += count(length-1, initialLength);
    }

    for (int pos0 = 1; pos0 < length; pos0 += 1) {
        for (int pos1 = 0; pos1 < length; pos1 += 1) {
            if (pos0 == pos1) { continue; }
            for (int posA = 0; posA < length; posA += 1) {
                if (posA == pos0 || posA == pos1) { continue; }

                vector<int> pos = {pos0, pos1, posA};
                std::sort(begin(pos), end(pos));

                s64 add = 1;

                //qDebug() << "pos" << posToString(pos0, pos1, posA);

                int before = pos[0];
                //qDebug() << "  before" << before;
                if (before > 0) {
                    add *= (s64) pow(13, before); // in front of 0 and 1
                }

                int between1 = pos[1] - pos[0] - 1;
                //qDebug() << "  between1" << between1;
                if (between1 > 0) {
                    add *= (s64) pow(14, between1);
                }

                int between2 = pos[2] - pos[1] -1;
                //qDebug() << "  between2" << between2;
                if (between2 > 0) {
                    add *= (s64) pow(15, between2);
                }

                int after = length - pos[2] - 1;
                //qDebug() << "  after" << after;
                if (after > 0) {
                    add *= (s64) pow(16, after);
                }

                //qDebug() << "  add" << add;

                ret += add;
            }
        }
    }

    return ret;
}


void test1();
void test2();
void testHas01A();
void mainEasy();

int main() {
    testHas01A();
    test1();
    test2();
    //mainEasy();
    return 0;
}

void test2() {

    s64 c = 0;

    for (int length = 2; length <= 16; length += 1) {
        c = count(length, length);
        qDebug() << "length" << length << "count" << c;
    }

    qDebug() << "Solution:" << c << ". Now use python to hex(" << c << ") and make everything upper case.";
}

void test1() {

    for (int length = 2; length <= 6; length += 1) {
        auto bfc = bruteForceCount(length, length);
        auto c = count(length, length);

        if (bfc != c) {
            qDebug() << "length" << length << "count" << c << " != " << bfc;
            assert(bfc == c);
        } else {
            //qDebug() << "length" << length << "count" << c << " == " << bfc;
        }
    }
}

void testHas01A() {
    assert(leadingZero(0x0    , 4)  == true);
    assert(leadingZero(0x0A   , 8)  == true);
    assert(leadingZero(0x0AA  , 12) == true);
    assert(leadingZero(0x010A , 16) == true);
    assert(leadingZero(0x0010A, 20) == true);
    assert(leadingZero(0xA0   , 8)  == false);
    assert(leadingZero(0xA01  , 12) == false);
    assert(leadingZero(0xA1   , 8)  == false);
    assert(has0(0x0)   == false);
    assert(has0(0x0A)  == false);
    assert(has0(0x0AA) == false);
    assert(has0(0xA0)  == true);
    assert(has0(0xA01) == true);
    assert(has0(0xA1)  == false);
    assert(has1(0x0)   == false);
    assert(has1(0x10)  == true);
    assert(has1(0xBA1) == true);
    assert(has1(0x1BA) == true);
    assert(has1(0xA10) == true);
    assert(has1(0xA0B) == false);
    assert(hasA(0x0)   == false);
    assert(hasA(0xA0)  == true);
    assert(hasA(0x1A1) == true);
    assert(hasA(0x1BA) == true);
    assert(hasA(0x1B0) == false);
}

// ### try a simpler version #################################################

// alphabet: 0,1,2. at least 0, 1 are in.
s64 bruteForceCountEasy(int length, int initialLength) {
    s64 ret = 0;

    if (length >= 3) {
        ret += bruteForceCountEasy(length-1, initialLength);
    } else if (length == 2) {
        return 1; // 10
    }

    function<s64(int, u64)> recurse = [length, initialLength, &recurse](int pos, u64 n) -> s64 {
        if (pos == length) {
            if (leadingZero(n, length*4) == false && has0(n) && has1(n)) {
                if (initialLength == length) {
                    //qDebug() << QString("%1").arg(n, 0, 16);
                }
                return 1;
            } else {
                return 0;
            }
        }

        s64 ret = 0;
        for (u64 b = 0x0; b <= 0x2; b += 1) {
            ret += recurse(pos+1, (n<<4) + b);
        }
        return ret;

    };

    return ret + recurse(0, 0);
}

s64 countEasy(int length, int initialLength) {

    auto posToString = [length](int pos0, int pos1) -> QString {
        QString ret;
        QTextStream s(&ret);
        for (int i = 0; i < length; i += 1) {
            if (i != pos0 && i != pos1) {
                s << "x";
            } else if (i == pos0) {
                s << "0";
            } else {
                s << "1";
            }
        }
        return ret;
    };
    (void) posToString;

    s64 ret = 0;

    if (length >= 3) {
        ret += countEasy(length-1, initialLength);
    }

    for (int pos0 = 1; pos0 < length; pos0 += 1) {
        for (int pos1 = 0; pos1 < length; pos1 += 1) {
            if (pos0 == pos1) { continue; }

            int add = 1;

            //qDebug() << "pos" << posToString(pos0, pos1);

            int before = std::min(pos0, pos1);
            //qDebug() << "  before" << before;
            if (before > 0) {
                add *= (s64) pow(1, before); // in front of 0 and 1
            }

            int after = length - std::max(pos0, pos1) - 1;
            //qDebug() << "  after" << after;
            if (after > 0) {
                add *= (s64) pow(3, after);
            }

            int between = std::max(pos0, pos1) - std::min(pos0, pos1) - 1;
            //qDebug() << "  between" << between;
            if (between > 0) {
                add *= (s64) pow(2, between);
            }

            //qDebug() << "  add" << add;

            ret += add;
        }
    }

    return ret;
}

void test1Easy();

void mainEasy() {
    test1Easy();
}

void test1Easy() {
    for (int length = 2; length <= 16; length += 1) {
        qDebug() << "";
        qDebug() << "length" << length;
        auto bfc = bruteForceCountEasy(length, length);
        auto c = countEasy(length, length);

        if (bfc != c) {
            qDebug() << c << " != " << bfc;
            assert(bfc == c);
        } else {
            qDebug() << c << " == " << bfc;
        }
    }
}
