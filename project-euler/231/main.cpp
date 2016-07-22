#include "../lib.hpp"

s64 binomialCoefficient(s64 n, s64 k) {
    if      (n == 1)           { return 1; }
    else if (k == 0 || k == n) { return 1; }

    return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}

s64 factorial(s64 n) {
    s64 f = 1;
    for (s64 i = 2; i <=n; i += 1) {
        f *= i;
    }
    return f;
}

s64 binomialCoefficient2(s64 n, s64 k) {
    return factorial(n) / (factorial(k)* factorial(n - k));
}

QMap<s64, s64> factor(s64 n) {
    QMap<s64, s64> factors;
    s64 f = 2;
    while (n > 1) {
        if (n % f == 0) {
            factors[f] = 0;
            while (n % f == 0) {
                n /= f;
                factors[f] += 1;
            }
        }

        do {
            f += 1;
        } while (isPrime(f) == false);
    }
    return factors;
}

s64 factorSum(const QMap<s64, s64>& factors) {
    s64 ret = 0;
    QMapIterator<s64, s64> i(factors);
    while (i.hasNext()) {
        i.next();
        ret += i.key() * i.value();
    }
    return ret;
}

void addFactors(QMap<s64, s64>* f1, const QMap<s64, s64>& f2) {
    QMapIterator<s64, s64> i(f2);
    while(i.hasNext()) {
        i.next();

        if (f1->contains(i.key()) == false) {
            (*f1)[i.key()]  = i.value();
        } else {
            (*f1)[i.key()] += i.value();
        }
    }
}

QMap<s64, s64> factorialFactors(s64 n) {

    QVector<s64> primes;
    primesToAtLeast(n, &primes);

    QHash<s64, QMap<s64, s64>> prev;
    QMap<s64, s64> sum;

    prev.insert(1, {});

    for (int i = 2; i <= n; i += 1) {
        s64 p = -1;
        foreach (auto p_, primes) {
            if (i % p_ == 0) {
                p = p_;
                break;
            }
        }

        assert(p != -1);
        assert(prev.contains(i/p));

        prev[i] = prev[i/p];
        if (prev[i].contains(p) == false) {
            prev[i][p]  = 1;
        } else {
            prev[i][p] += 1;
        }

        addFactors(&sum, prev[i]);
    }

    //qDebug() << "n" << n << ", prev" << prev << ", sum" << sum;

    return sum;
}

s64 factorialFactorsSum(s64 n) {

    QVector<s64> primes;
    primesToAtLeast(n, &primes);

    QVector<s64> prev(n+1);
    s64 sum = 0;

    prev[0] = -1;
    prev[1] =  0;

    s64 p = -1;
    for (int i = 2; i <= n; i += 1) {
        for (int j = 0; j <= primes.size(); j += 1) {
            if (i % primes[j] == 0) {
                p = primes[j];
                break;
            }
        }

        prev[i] = prev[i/p] + p;

        sum += prev[i];
    }

    return sum;
}

s64 factorialFactorsSum2(s64 n) {

    QVector<s64> primes;
    primesToAtLeast(n, &primes);

    QVector<s64> f(n+1);
    fill(begin(f), end(f), 0);

    foreach (auto p, primes) {

        auto pk = p;
        while (pk <= n) {

            int step = pk;
            while (step <= n) {
                f[step] += p;
                step += pk;
            }

            pk *= p;
        }
    }

    s64 sum = 0;

    for (int i = 0; i <= n; i += 1) {
        sum += f[i];
    }

    return sum;
}

void test1();
void test2();
void test3();
void test4();
void test5();
void testBinomialCoefficient();
void testFactorial();
void testBinomialCoefficient2();
void testFactor();
void testFactorialFactors();
void testFactorialFactorsSum();
void testFactorialFactorsSum2();

int main() {
    testBinomialCoefficient();
    testFactorial();
    testBinomialCoefficient2();
    testFactor();
    testFactorialFactors();
    testFactorialFactorsSum();
    testFactorialFactorsSum2();
    //test1();
    //test2();
    //test3();
    //test4();
    test5();
    return 0;
}

void test5() {
    assert(factorialFactorsSum2(10) - factorialFactorsSum2(3) - factorialFactorsSum2(10 - 3) == 14);

    qDebug() << "        2 * 1000" << factorialFactorsSum2(        2 * 1000);
    qDebug() << "       20 * 1000" << factorialFactorsSum2(       20 * 1000);
    qDebug() << "      200 * 1000" << factorialFactorsSum2(      200 * 1000);
    qDebug() << " 2 * 1000 * 1000" << factorialFactorsSum2( 2 * 1000 * 1000);
    s64 nk = factorialFactorsSum2(5 * 1000 * 1000);
    qDebug() << " 5 * 1000 * 1000" << nk;
    s64 k = factorialFactorsSum2(15 * 1000 * 1000);
    qDebug() << "15 * 1000 * 1000" << k;
    s64 n = factorialFactorsSum2(20 * 1000 * 1000);
    qDebug() << "20 * 1000 * 1000" << n;

    qDebug() << n - k - nk << "!!!!";
}

void test4() {
    // factorialFactorsSum(n - k) = 1441290326614
    qDebug() << "k!" << factorialFactorsSum(15 * 1000 * 1000) ;
    //qDebug() << "n! / k!" << ;
    //qDebug() << "n! / k!" << ;
}

void test3() {
    qDebug() << "        2 * 1000" << factorialFactorsSum(        2 * 1000);
    qDebug() << "       20 * 1000" << factorialFactorsSum(       20 * 1000);
    qDebug() << "      200 * 1000" << factorialFactorsSum(      200 * 1000);
    qDebug() << " 2 * 1000 * 1000" << factorialFactorsSum( 2 * 1000 * 1000);
    qDebug() << "20 * 1000 * 1000" << factorialFactorsSum(20 * 1000 * 1000);
}

void test2() {
    //qDebug() <<     2000 << factorialFactors(    2000);
    //qDebug() <<    20000 << factorialFactors(   20000);
    qDebug() <<   200000 << factorialFactors(  200000);
    //qDebug() <<  2000000 << factorialFactors( 2000000);
    //qDebug() << 20000000 << factorialFactors(20000000);
}

void test1() {

    for (s64 n = 0; n <= 20; n += 1) {
        for (s64 k = 0; k <= n; k += 1) {
            qDebug() << n << k << ", binCoeff:" << binomialCoefficient2(n, k) << ", sum:" << factorSum(factor(binomialCoefficient2(n, k)));
        }
        qDebug() << "";
    }

    qDebug() << binomialCoefficient(      20,       15);
    //qDebug() << binomialCoefficient(     200,      150);
    //qDebug() << binomialCoefficient(    2000,     1500);
    //qDebug() << binomialCoefficient(   20000,    15000);
    //qDebug() << binomialCoefficient(  200000,   150000);
    //qDebug() << binomialCoefficient( 2000000,  1500000);
    //qDebug() << binomialCoefficient(20000000, 15000000);

}

void testBinomialCoefficient() {
    assert(binomialCoefficient(0, 0) ==  1);

    assert(binomialCoefficient(1, 0) ==  1);
    assert(binomialCoefficient(1, 1) ==  1);

    assert(binomialCoefficient(2, 0) ==  1);
    assert(binomialCoefficient(2, 1) ==  2);
    assert(binomialCoefficient(2, 2) ==  1);

    assert(binomialCoefficient(3, 0) ==  1);
    assert(binomialCoefficient(3, 1) ==  3);
    assert(binomialCoefficient(3, 2) ==  3);
    assert(binomialCoefficient(3, 3) ==  1);

    assert(binomialCoefficient(4, 0) ==  1);
    assert(binomialCoefficient(4, 1) ==  4);
    assert(binomialCoefficient(4, 2) ==  6);
    assert(binomialCoefficient(4, 3) ==  4);
    assert(binomialCoefficient(4, 4) ==  1);

    assert(binomialCoefficient(5, 0) ==  1);
    assert(binomialCoefficient(5, 1) ==  5);
    assert(binomialCoefficient(5, 2) == 10);
    assert(binomialCoefficient(5, 3) == 10);
    assert(binomialCoefficient(5, 4) ==  5);
    assert(binomialCoefficient(5, 5) ==  1);
}

void testFactorial() {
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(2) == 2);
    assert(factorial(3) == 6);
    assert(factorial(4) == 24);
}

void testBinomialCoefficient2() {
    for (s64 n = 0; n < 6; n += 1) {
        for (s64 k = 0; k <= n; k += 1) {
            assert(binomialCoefficient(n, k) == binomialCoefficient2(n, k));
        }
    }
}

void testFactor() {
    auto f1    = factor( 1);          QMap<s64, s64> g1   {};
    auto f2    = factor( 2);          QMap<s64, s64> g2   {{2, 1}};
    auto f3    = factor( 3);          QMap<s64, s64> g3   {{3, 1}};
    auto f4    = factor( 4);          QMap<s64, s64> g4   {{2, 2}};
    auto f5    = factor( 5);          QMap<s64, s64> g5   {{5, 1}};
    auto f6    = factor( 6);          QMap<s64, s64> g6   {{2, 1}, {3, 1}};
    auto f7    = factor( 7);          QMap<s64, s64> g7   {{7, 1}};
    auto f8    = factor( 8);          QMap<s64, s64> g8   {{2, 3}};
    auto f9    = factor( 9);          QMap<s64, s64> g9   {{3, 2}};
    auto f10   = factor(10);          QMap<s64, s64> g10  {{2, 1}, {5, 1}};
    auto f11   = factor(11);          QMap<s64, s64> g11  {{11, 1}};
    auto f12   = factor(12);          QMap<s64, s64> g12  {{2, 2}, {3, 1}};
    auto f13   = factor(13);          QMap<s64, s64> g13  {{13, 1}};
    auto f14   = factor(14);          QMap<s64, s64> g14  {{2, 1}, {7, 1}};
    auto f15   = factor(15);          QMap<s64, s64> g15  {{3, 1}, {5, 1}};
    auto f16   = factor(16);          QMap<s64, s64> g16  {{2, 4}};
    auto f4410 = factor(2*3*3*5*7*7); QMap<s64, s64> g4410{{2, 1}, {3, 2}, {5, 1}, {7, 2}};

    assert(f1    == g1   );
    assert(f2    == g2   );
    assert(f3    == g3   );
    assert(f4    == g4   );
    assert(f5    == g5   );
    assert(f6    == g6   );
    assert(f7    == g7   );
    assert(f8    == g8   );
    assert(f9    == g9   );
    assert(f10   == g10  );
    assert(f11   == g11  );
    assert(f12   == g12  );
    assert(f13   == g13  );
    assert(f14   == g14  );
    assert(f15   == g15  );
    assert(f16   == g16  );
    assert(f4410 == g4410);

}

void testFactorialFactors() {
    for (int i = 0; i <= 9; i += 1) {
        //qDebug() << i << factorial(i) << factor(factorial(i)) << factorialFactors(i);
        assert(factor(factorial(i)) == factorialFactors(i));
    }
}

void testFactorialFactorsSum() {
    for (int i = 0; i <= 9; i += 1) {
        //qDebug() << i << factorialFactorsSum(i) << factorSum(factorialFactors(i));
        assert(factorialFactorsSum(i) == factorSum(factorialFactors(i)));
    }
}

void testFactorialFactorsSum2() {
    for (int i = 0; i <= 30; i += 1) {
        //qDebug() << i << factorial(i) << factorialFactorsSum2(i) << "!=" << factorialFactorsSum(i);
        assert(factorialFactorsSum2(i) == factorialFactorsSum(i));
    }
}
