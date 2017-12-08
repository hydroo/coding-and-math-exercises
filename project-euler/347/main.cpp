#include "../lib.hpp"

s64 M(s64 p, s64 q, s64 n) {

    s64 m = 0;
    for (auto pp = p; pp <= n; pp *= p) {
        auto qp = pp*q;
        while (qp*q <= n) {
            qp *= q;
        }
        if (qp <= n && qp >= m) {
            m = qp;
        }
    }

    //qDebug() << QString("M(%1, %2, %3) = %4").arg(p, 4).arg(q, 4).arg(n, 4).arg(m, 4);

    return m;
}

s64 S(s64 n) {

    QVector<s64> primes;
    primesToAtLeast(n, &primes);

    QSet<s64> distinctM;
    s64 sum = 0;

    foreach (s64 p, primes) {
        foreach (s64 q, primes) {
            if (p*q > n)     { break;    }
            else if (q <= p) { continue; }

            auto m = M(p, q, n);

            if (distinctM.contains(m) == false) {
                distinctM.insert(m);
                sum += m;
                qDebug() << QString("M(%1, %2, %3) = %4").arg(p, 3).arg(q, 3).arg(n, 3).arg(m, 3);
            }
        }
    }

    qDebug() << QString("S(%1) = %2").arg(n, 4).arg(sum, 4);

    return sum;
}


void testM();
void testS();

int main(int argc, char **args) {
    (void) argc; (void) args;

    testM();
    testS();

    return 0;
}

void testM() {
    assert(M(2, 3, 100) == 96);
    assert(M(3, 5, 100) == 75);
    assert(M(2, 73, 100) == 0);
}

void testS() {
    assert(S(100) == 2262);

    qDebug() << S(10 * 1000 * 1000); // Solution: 11109800204052
}
