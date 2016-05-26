#include <cassert>
#include <cmath>

#include <QSet>
#include <QtDebug>

using s64 = int64_t;

using namespace std;

bool isPrime(s64 n) {
    if (n == 2 ) {
        return true;
    } else if (n % 2 == 0 || n == 1) {
        return false;
    }
    s64 sqrtn = floor(sqrt(n));
    for (int d = 3; d <= sqrtn; d += 2) {
        if (n % 3 == 0) {
            return false;
        }
    }
    return true;
}

bool isSquareFree(s64 n) {
    s64 sqrtn = floor(sqrt(n));
    for (s64 i = 2; i <= sqrtn; i += 1) {
        if (n % (i*i) == 0 && isPrime(i)) {
            return false;
        }
    }
    return true;
}

void testIsPrime();
void doIt();

int main() {

    testIsPrime();
    doIt();

    return 0;
}

void doIt() {

    int max = (51-1);

    QSet<s64> distinctNumbers;

    QVector<s64> lastRow(max+1);
    QVector<s64> currentRow(max+1);

    for (int row = 0; row <= max; row += 1) {
        for (int pos = 0; pos <= row; pos += 1) {

            if (pos == 0 || pos == row) {
                currentRow[pos] = 1;
            } else {
                currentRow[pos] = lastRow[pos] + lastRow[pos-1];
            }

            if (distinctNumbers.contains(currentRow[pos]) == false) {
                //qDebug() << currentRow[pos];
                distinctNumbers.insert(currentRow[pos]);
            }
        }
        //qDebug() << currentRow;
        lastRow = currentRow;
    }

    //qDebug() << "Size:" << distinctNumbers.size();

    s64 sum = 0;
    foreach (s64 n, distinctNumbers) {
        if (isSquareFree(n)) {
            //qDebug() << n;
            sum += n;
        } else {
            //qDebug() << n;
        }
    }
    qDebug() << "sum (solution):" << sum;
}

void testIsPrime() {
    assert(isPrime( 1) == false);
    assert(isPrime( 2) == true );
    assert(isPrime( 3) == true );
    assert(isPrime( 4) == false);
    assert(isPrime( 5) == true );
    assert(isPrime( 6) == false);
    assert(isPrime( 7) == true );
    assert(isPrime( 8) == false);
    assert(isPrime( 9) == false);
    assert(isPrime(10) == false);
    assert(isPrime(11) == true );
    assert(isPrime(12) == false);
    assert(isPrime(13) == true );
    assert(isPrime(14) == false);
    assert(isPrime(15) == false);
    assert(isPrime(16) == false);
    assert(isPrime(17) == true );
    assert(isPrime(18) == false);
    assert(isPrime(19) == true );
    assert(isPrime(20) == false);
}
