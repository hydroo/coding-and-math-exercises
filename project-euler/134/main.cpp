#include <cassert>
#include <cmath>

#include <QHash>
#include <QList>
#include <QString>
#include <QtDebug>
#include <QtGlobal>

struct Primes {
    int max;
    QHash<int, int> s; // quick lookup
    QList<int> l; // sorted
};

static Primes* newPrimes() {
    Primes *ret = new Primes;
    ret->max = 1;
    return ret;
}

static void deletePrimes(Primes *primes) {
    delete primes;
}

static void updatePrimes(int n, Primes *primes) {
    if (n <= primes->max) return;

    for (int i = primes->max + 1; i <= n; i += 1) {
        bool p = true;
        foreach (int prime, primes->l) {
            if (i % prime == 0) {
                p = false;
                break;
            }
        }
        if (p == true) {
            primes->s.insert(i, primes->l.size());
            primes->l.append(i);
        }
    }

    primes->max = n;
}

static bool isPrime(int n, const Primes& primes) {
    Q_ASSERT(n <= primes.max);
    return primes.s.contains(n);
}


// returns greatest common divisor of a, b
static int extendedEuclid(int a, int b, int *amul, int *bmul) {
    if (a > b) {
        int t1 = a; a = b; b = t1;
        int *t2 = amul; amul = bmul; bmul = t2;
    }

    if (b % a == 1) {
        *bmul = 1;
        *amul = -(b/a);
        return 1;
    }

    int ret = extendedEuclid(b % a, a, amul, bmul);

    int t = *bmul;
    *bmul = *amul;
    *amul = t + *amul * -(b/a);

    return ret;
}

int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    Primes *primes = newPrimes();

    int i = 0;
    int p1;
    int dmul;
    int p2mul;
    int d;
    qint64 sum = 0;
    for (int p2 = 7; p2 <= 1000003; p2 += 2) { /* last p2 == 1000003*/
        updatePrimes(p2, primes);

        if (isPrime(p2, *primes) == false) continue;

        i += 1;

        p1 = primes->l[primes->s[p2] - 1];

        d = pow(10, floor(log10(p1))+1);
        Q_ASSERT(d > p1 && p1*10 > d);

        int t = extendedEuclid(d, p2, &dmul, &p2mul);
        Q_ASSERT(t == 1);
        Q_ASSERT((qint64) d * (qint64) dmul + (qint64) p2 * (qint64) p2mul == 1);

        qint64 x = (qint64) -p1 * (qint64) dmul;
        while (x < 0) {
            x += p2;
        }
        x = (x + p2) % p2;

        qint64 wantedNumber = (qint64)x * (qint64)d + p1;

        Q_ASSERT(wantedNumber > p1 && wantedNumber > p2);
        Q_ASSERT(wantedNumber % p2 == 0);
        Q_ASSERT((wantedNumber - p1) % d == 0);

        if (i % 1000 == 0 || p2 > 998999 || p2 < 200) {
            qDebug() << QString("%1 %2: %3 % %4 == 0").arg(p1, 7).arg(p2, 7).arg(wantedNumber, 20).arg(p2, 7);
        }

        sum += wantedNumber;
        Q_ASSERT(sum > 0);
    }

    qDebug() << sum;

    deletePrimes(primes);

    return 0;
}
