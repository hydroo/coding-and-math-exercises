#include <cassert>
#include <cmath>

#include <QString>
#include <QtDebug>
#include <QtGlobal>

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

int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    int max = 1000000;

    Primes *primes = newPrimes();
    qDebug() << "init primes";
    updatePrimes(max, primes);
    qDebug() << "done";

    qint64 q, q_3, q_3l, q_3h, x, n;

    for (qint64 y = 1; y <= max; y += 1) {

        foreach(int p, primes->l) {

            q_3 = y*y*y + p;
            q = pow(q_3, 1/3.0);
            q_3l = q*q*q;
            q_3h = (q+1)*(q+1)*(q+1);

            if (q_3l == q_3 || q_3h == q_3) {

                if (q_3l == q_3) {
                    q = q;
                } else {
                    q = q+1;
                }

                n = y*y*y;
                x = q*y*y;

                qDebug() << QString("%1^3 + %1^2 * %2 == %3^3").arg(n).arg(p).arg(x);
            }
        }
    }


    deletePrimes(primes);

    return 0;
}
