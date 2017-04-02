#include "../lib.hpp"

#include <omp.h>

bool isPrime2(s64 n) {
    if (n > 10000) {
        mpz_t n2;
        mpz_init(n2);
        mpz_set_si(n2, n);
        int p = mpz_probab_prime_p(n2, 20);
        if (p == 0) {
            return false;
        } else if (p == 2) {
            return true;
        }
    }
    return isPrime(n);
}

bool isPrime3(s64 i, const QVector<s64>& primes) {
    s64 a = i*i+1;
    s64 b = i*i+3;
    s64 c = i*i+7;
    s64 d = i*i+9;
    s64 e = i*i+13;
    s64 f = i*i+27;

    s64 sqrtn = (s64) floor(sqrt(f));
    assert(sqrtn <= primes.last());

    for (int i = 0; i < primes.size(); i += 1) {
        if (primes[i] > sqrtn) { break; }
        if (a % primes[i] == 0 ||
                b % primes[i] == 0 ||
                c % primes[i] == 0 ||
                d % primes[i] == 0 ||
                e % primes[i] == 0 ||
                f % primes[i] == 0) {
            return false;
        }
    }

    return true;
}

void test3();
void test2();
void test1();

int main() {

    test3();
    //test2();
    //test1();
    return 0;
}

void test3() {

    s64 min = 10;
    //s64 max = 100;
    s64 max = 150 * 1000 * 1000;

    qDebug() << "Generating primes";

    QVector<s64> primes;
    primesToAtLeast(floor(sqrt(max*max+27)), &primes);

    qDebug() << "Generating primes done";

    s64 sum = 0;

    #pragma omp parallel for shared(primes) reduction(+:sum) schedule(static, 10000)
    for (auto i = min; i <= max; i += 10) {

        s64 a = i*i+1;
        s64 b = i*i+3;
        s64 c = i*i+7;
        s64 d = i*i+9;
        s64 e = i*i+13;
        s64 f = i*i+27;

        if (isPrime3(i, primes)) {

            //qDebug() << a << b << c << d << e << f;

            bool isConsecutive = true;
            for (auto j = a+2 /*odd*/; j <= f-2 /*odd*/; j += 2) {
                if (j == b || j == c || j == d || j == e) {
                    continue;
                } else {
                    if (isPrime(j, primes)) {
                        isConsecutive = false;
                        //qDebug() << "nope" << j;
                        break;
                    }
                }
            }

            if (isConsecutive) {
                qDebug() << i;
                sum += i;
            }
        }
    }

    qDebug() << "sum" << sum;
}

void test2() {

    s64 min = 10;
    //s64 max = 100;
    s64 max = 1 * 1000 * 1000;

    qDebug() << "Generating primes";

    QVector<s64> primes;
    primesToAtLeast(floor(sqrt(max*max+27)), &primes);

    qDebug() << "Generating primes done";

    s64 sum = 0;

    #pragma omp parallel for shared(primes) reduction(+:sum) schedule(static, 10000)
    for (auto i = min; i <= max; i += 10) {

        s64 a = i*i+1;
        s64 b = i*i+3;
        s64 c = i*i+7;
        s64 d = i*i+9;
        s64 e = i*i+13;
        s64 f = i*i+27;

        // if (isPrime(a, primes) && isPrime(b, primes) && isPrime(c, primes) && isPrime(d, primes)) {
        //     auto factors = primeFactors(i, primes);
        //     factors.remove(2);
        //     factors.remove(5);
        //     qDebug() << i << factors << "--" << e << primeFactors(d, primes);
        // }

        if (isPrime(a, primes) && isPrime(b, primes) && isPrime(c, primes) && isPrime(d, primes) && isPrime(e, primes) && isPrime(f, primes)) {

            //qDebug() << a << b << c << d << e << f;

            bool isConsecutive = true;
            for (auto j = a+2 /*odd*/; j <= f-2 /*odd*/; j += 2) {
                if (j == b || j == c || j == d || j == e) {
                    continue;
                } else {
                    if (isPrime(j, primes)) {
                        isConsecutive = false;
                        //qDebug() << "nope" << j;
                        break;
                    }
                }
            }

            if (isConsecutive) {
                qDebug() << i;
                sum += i;
            }
        }
    }

    qDebug() << "sum" << sum;
}

void test1() {

    s64 min = 1;
    //s64 max = 100;
    s64 max = 1000 * 1000;

    s64 sum = 0;

    #pragma omp parallel for reduction(+:sum) schedule(static, 10000)
    for (auto i = min; i <= max; i += 1) {

        // if (i == min) {
        //     qDebug() << omp_get_num_threads();
        //     omp_sched_t kind;
        //     int chunksize;
        //     omp_get_schedule(&kind, &chunksize);
        //     qDebug() << kind << chunksize;
        // }

        s64 a = i*i+1;
        s64 b = i*i+3;
        s64 c = i*i+7;
        s64 d = i*i+9;
        s64 e = i*i+13;
        s64 f = i*i+27;

        if (isPrime2(a) && isPrime2(b) && isPrime2(c) && isPrime2(d) && isPrime2(e) && isPrime2(f)) {

            bool isConsecutive = true;
            for (auto j = a+2 /*odd*/; j <= f-2; j += 2) {
                if (j == b || j == c || j == d || j == e) {
                    continue;
                } else {
                    if (isPrime2(j)) {
                        isConsecutive = false;
                        break;
                    }
                }
            }

            if (isConsecutive) {
                qDebug() << i;
                sum += i;
            }
        }
    }

    qDebug() << "sum" << sum;
}
