#include "../lib.hpp"

using namespace std;

void test1();

int main(int argc, char **args) {
    (void) argc; (void) args;

    test1();

    return 0;
}

void test1() {

    const int maxDays = 15;
    const int maxA    = 5;

    std::function<mpf_class(const QVector<int>&, int)> recurse = [&recurse](const QVector<int>& envelope, int day) -> mpf_class {

        if (day > maxDays) { return 0.0; }

        // qDebug() << day << envelope;

        int sheets = std::accumulate(begin(envelope), end(envelope), 0);

        mpf_class e = 0;

        if (sheets == 1) {
            // qDebug() << "  " << envelope << " !!! ";
            e += 1;
        }

        for (int a = 1; a <= maxA; a += 1) {

            if (envelope[a] == 0) { continue; }

            mpf_class p(envelope[a]);
            p /= sheets;

            QVector<int> newEnvelope = envelope;

            newEnvelope[a] -= 1;

            for (int i = a+1; i <= maxA; i += 1) {
                newEnvelope[i] += 1;
            }

            // if (day < maxDays) {
            //     qDebug() << p;
            // }

            e += recurse(newEnvelope, day + 1) * p;

        }

        return e;

    };

    QVector<int> envelope{0, 1};
    for (int i = 2; i <= maxA; i += 1) {
        envelope << 0;
    }

    mpf_class e = recurse(envelope, 1) - 1;

    qDebug().noquote() << QString("Days %1, maxA %2, Expected number of times the envelope contains exactly one sheet (rounded to 6 decimal places):").arg(maxDays).arg(maxA);
    gmp_printf("  %.6Ff\n", e.get_mpf_t());
}
