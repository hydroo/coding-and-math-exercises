#include "../lib.hpp"

#include <QSet>

bool isSquareFree(s64 n) {
    s64 sqrtn = floor(sqrt(n));
    for (s64 i = 2; i <= sqrtn; i += 1) {
        if (n % (i*i) == 0 && isPrime(i)) {
            return false;
        }
    }
    return true;
}


int main() {

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

    return 0;
}
