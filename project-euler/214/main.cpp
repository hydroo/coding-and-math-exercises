#include "../lib.hpp"

using namespace std;

void testTotientFunction();
void test1();
void test2();

int main(int argc, char **args) {
    (void) argc; (void) args;

    // testTotientFunction();
    // test1();
    test2();

    return 0;
}

s64 totientFunction(s64 n) {
    s64 sum = 0;
    for (s64 i = 1; i <= n; i += 1) {
        if (gcd(i, n) == 1) {
            sum += 1;
        }
    }
    return sum;
}

s64 totientFunction(QMap<s64, s64> factors) {

    s64 phi = 1;

    QMapIterator<s64, s64> i(factors);

    while (i.hasNext()) {
        i.next();
        const s64 p = i.key();
        const s64 k = i.value();

        phi *= std::pow(p, k) - std::pow(p, k-1);
    }

    return phi;
}

void testTotientFunction() {
    assert(totientFunction( 1) ==  1);
    assert(totientFunction( 2) ==  1);
    assert(totientFunction( 3) ==  2);
    assert(totientFunction( 4) ==  2);
    assert(totientFunction( 5) ==  4);
    assert(totientFunction( 6) ==  2);
    assert(totientFunction( 7) ==  6);
    assert(totientFunction( 8) ==  4);
    assert(totientFunction( 9) ==  6);
    assert(totientFunction(10) ==  4);
    assert(totientFunction(11) == 10);
    assert(totientFunction(12) ==  4);
    assert(totientFunction(13) == 12);
    assert(totientFunction(14) ==  6);
    assert(totientFunction(15) ==  8);
    assert(totientFunction(16) ==  8);
    assert(totientFunction(17) == 16);
    assert(totientFunction(18) ==  6);
    assert(totientFunction(19) == 18);
    assert(totientFunction(20) ==  8);

    auto primes = primesTo(200);
    for (s64 n = 1; n <= 100; n += 1) {
        auto f = primeFactors(n, primes);
        assert(totientFunction(n) == totientFunction(f));
    }
}

void test1() {

    const s64 max = 10000;
    const int printWidth = (int) ceil(log10(max + 1));

    for (int n = 1; n < max; n += 1) {
        QString s;
        s64 i = n;
        do {
            i = totientFunction(i);
            s += QString("%1 ").arg(i, printWidth);
        } while (i > 1);

        qDebug().noquote() << QString("%1 ").arg(n, printWidth) << s;
    }

}

// Would be faster to generate all phi(n) first by enumerating all prime factorizations from 1 to max
// then just follow the phis and calculate chain lengths.
//
// This here runs in <30mins
void test2() {
    const s64 max    = 40 * 1000 * 1000;
    const s64 length = 25;
    const int printWidth = (int) ceil(log10(max + 1));

    QVector<s64> primes = primesTo(max);

    QHash<s64, s64> totients;
    QHash<s64, s64> chainLengths;

    s64 sum = 0;

    QVector<QPair<s64, s64>> stack;

    for (int i = 0; i < primes.size(); i += 1) {
        const s64 p = primes[i];
        s64 q = p;
        s64 l = 1;

        stack.clear();
        do {
            if (chainLengths.contains(q)) {
                l += chainLengths[q] - 1;
                break;
            }

            stack << QPair<s64, s64>(q, l);

            if (totients.contains(q)) {
                q = totients[q];
            } else {
                s64 q_ = q;

                if (q == p) {
                    q = p-1;
                } else {
                    auto f = primeFactors(q, primes);
                    q = totientFunction(f);
                }
                totients.insert(q_, q);
            }
            l += 1;
        } while (q > 1);

        if (i % 30000 == 0 || l == length) {
            qDebug().noquote() << QString("sum %1 p %2, l %3 :  ").arg(sum, 2*printWidth).arg(p, printWidth).arg(l, printWidth); // << s;
        }

        if (l == length) {
            sum += p;
        }

        while(stack.isEmpty() == false) {
            auto ql = stack.takeLast();
            chainLengths[ql.first] = l - ql.second + 1;
        }

    }

    qDebug() << "Sum " << sum;
}
