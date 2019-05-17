#include <../lib.hpp>

using namespace std;
using s64 = int64_t;

void asdf2();
void asdf();

int main(int argc, char **args) {
    (void) argc;
    (void) args;

    constexpr s64 divisorPowerMax = 500500;

    QVector<s64> primes = primesTo(100*1000*1000);
    QVector<s64> powers(primes.size(), 0);

    s64 divisorPower = 0;

    mpz_class n(1);

    do {
        // Search for the smallest possible increase for n
        s64       smallestFactorIndex = -1;
        mpz_class smallestFactorPower = -1;

        s64 i;
        for (i = 0; i < primes.size();) {

            // powers is always sorted as follows: [15, 7, 7, 3, 3, 3, 1, 1, 1, 1, 0, 0, 0, ...]
            //
            // 0 is the first prime not a factor of n
            if (powers[i] == 0) {

                if (primes[i] < smallestFactorPower || smallestFactorIndex == -1) {
                    smallestFactorIndex = i;
                    smallestFactorPower = primes[i];
                }
                break; // no larger prime can be a candidate

            } else {

                // Difference in the power of the prime to be added: powers[i]+1 == (powers[i]+1)*2-1 - powers[i];
                // E.g. 1 -> 3, 3->7, 7 -> 15
                //
                // This is necessary for maintaining that the number of divisors is a power of 2
                //
                // Each new prime with a factor of 1, means divisors *= 2;
                // A prime with a factor of 1 contributed 2 divisors, 3 contribute 4, 7 contribute 8, etc.
                // So each power^factor increase of this kind (and each new prime with a factor of 1) raises the divisorPower by exactly 1.
                mpz_class f(primes[i]);
                mpz_pow_ui(f.get_mpz_t(), f.get_mpz_t(), powers[i]+1);

                if (f < smallestFactorPower || smallestFactorIndex == -1) {
                    smallestFactorIndex = i;
                    smallestFactorPower = f;
                }

                // Since powers are sorted as mentioned above, powers of the same size always make a larger prime^power.
                // Therefore, when looking for a smaller prime^power it needs to have a lower power.
                //   E.g. when looking at power[i] == 3, the next possible power has to be less than 3.
                auto p = powers[i];
                while (i < primes.size() && p == powers[i]) {
                    i += 1;
                }
            }
        }
        assert(i < primes.size());

        divisorPower += 1;
        powers[smallestFactorIndex] += powers[smallestFactorIndex]+1;
        n = (n * smallestFactorPower) % 500500507;


        //QVector<s64> powers2 = powers;
        //auto firstZero = powers2.indexOf(0);
        //powers2.remove(firstZero, powers2.size()-firstZero);

        //qDebug() << qSetFieldWidth(12) << n.get_ui() << qSetFieldWidth(0) << ", divisor power " << qSetFieldWidth(1+(int)ceil(log10(divisorPowerMax))) << divisorPower << qSetFieldWidth(0) << powers2;
        qDebug() << qSetFieldWidth(12) << n.get_ui() << qSetFieldWidth(0) << ", divisor power " << qSetFieldWidth(1+(int)ceil(log10(divisorPowerMax))) << divisorPower;

    } while (divisorPower < divisorPowerMax);

    return 0;
}


//           n          divisors log2
//           2              1
//           6              2
//          24              3
//         120              4
//         840              5
//        7560              6
//       83160              7
//     1081080              8
//    17297280              9
//   294053760             10
//
//    35407281         500500
