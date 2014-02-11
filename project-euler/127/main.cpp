#include <cassert>

#include <QHash>
#include <QPair>
#include <QSet>
#include <QtDebug>
#include <QtGlobal>
#include <QVector>

/* *** helpers ***************************************************************/
// assumes:
//  * all primes smaller than 'n' are contained in 'primes'
//  * all numbers smaller than 'n' are contained in 'numbers'
void factorize(int n, QSet<int> *primes, QHash<int, QPair<QSet<int>, bool>> *numbers) {

    foreach(int prime, *primes) {
        if (n % prime == 0) {

            if ((*numbers)[n/prime].first.contains(prime) == true) {
                (*numbers)[n].second = false;
            } else {
                (*numbers)[n].second = (*numbers)[n/prime].second;
            }

            (*numbers)[n].first = (*numbers)[n/prime].first;
            (*numbers)[n].first.insert(prime);
            return;
        }
    }

    (*numbers)[n].first.insert(n);
    (*numbers)[n].second = true;
    primes->insert(n);
}

/* *** abc hit ***************************************************************/
static bool isAbcHit(int a_, int b_, int c_, const QHash<int, QPair<QSet<int>, bool>>& numbers) {
    Q_ASSERT(a_ + b_ == c_); // condition 3
    Q_ASSERT(a_ < b_); // condition 2

    const QSet<int>& a = numbers[a_].first;
    const QSet<int>& b = numbers[b_].first;
    const QSet<int>& c = numbers[c_].first;

    const QSet<int> aAndB = a + b;
    const int aAndBsize = aAndB.size();

    if (aAndBsize != a.size()+ b.size()) { // condition 1: coprimeness of a, b
        return false;
    }

    const QSet<int> factors = aAndB + c;

    if (factors.size() != aAndBsize + c.size()) { // condition 1: coprimeness of a, b, c
        return false;
    }

    qint64 radical = 1;
    foreach(int prime, factors) {
        radical *= prime;
        if (radical >= c_) { // condition 4: rad(a*b*c) < c
            return false;
        } else if (prime > c_) {
            return true;
        }
    }

    return true;
}

static qint64 sumOfAbcHits(int maxC, bool silent = true) {
    QSet<int> primes;
    QHash<int, QPair<QSet<int>, bool>> numbers;
    qint64 sum = 0;

    for (int c = 2; c <= maxC; c += 1) {

        factorize(c, &primes, &numbers);

        if (numbers[c].second == true) {
            continue;
        }

        for (int a = 1; a < (int) ((c/2.0)+0.5); a += 1) {
            Q_ASSERT(a < (c-a));

            if (isAbcHit(a, c-a, c, numbers) == true) {
                if (silent == false) {
                    //qDebug() << QString("hit: %1 + %2 = %3, sum: %4").arg(a).arg(c-a).arg(c).arg(sum);
                }
                sum += c;
            }
        }
    }

    return sum;
}

/* *** tests *****************************************************************/
static void test1() {
    //qDebug() << sumOfAbcHits(999);
    assert(sumOfAbcHits(999) == 12523);
}

/* *** main ******************************************************************/
int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    test1();

    qDebug() << 119999 << sumOfAbcHits(119999, false);

    return 0;
}
