#include <cassert>

#include <QString>
#include <QtDebug>
#include <QtGlobal>

/* *** helpers ***************************************************************/
struct Primes {
    qint64 max;
    QSet<qint64> s; // quick lookup
    QList<qint64> l; // sorted
};

static Primes* newPrimes() {
    Primes *ret = new Primes;
    ret->max = 2;
    return ret;
}

static void deletePrimes(Primes *primes) {
    delete primes;
}

static void updatePrimes(qint64 n, Primes *primes) {
    if (n < primes->max) return;

    for (qint64 i = primes->max; i <= n; i += 1) {
        bool p = true;
        for (int j = 0; j < primes->l.size(); j += 1) {
            if (i % primes->l[j] == 0) {
                p = false;
                break;
            }
        }
        if (p == true) {
            primes->s.insert(i);
            primes->l.append(i);
        }
    }

    primes->max = n;
}

static bool isPrime(qint64 n, const Primes& primes) {
    Q_ASSERT(n <= primes.max);
    return primes.s.contains(n);
}

/* *** repunit ***************************************************************/
static int A(int n) {
    int m = 1;
    int sum = 0;
    int i = 1;
    for(; i <= n; i += 1) {
        m = (m*10) % n;
        sum = (sum + m) % n;

        if (sum == 0) {
            break;
        }
    }
    return i;
}

int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    Primes *primes = newPrimes();

    int a;
    int count = 0;
    int sum = 0;
    for(int i = 3; i < 1000000; i += 2) {
        if (i % 2 == 0 || i % 5 == 0) continue;

        updatePrimes(i, primes);

        a = A(i);

        if ((i-1) % a == 0 && isPrime(i, *primes) == false) {
            count += 1;
            qDebug() << count << i << a;
            sum += i;
        }

        if (count == 25) {
            qDebug() << "sum" << sum;
            break;
        }

    }

    deletePrimes(primes);

    return 0;
}
