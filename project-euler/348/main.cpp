#include "../lib.hpp"

bool isPalindrome(s64 n) {

    const QString s = QString("%1").arg(n);
    int l = s.length();
    for (int i = 0; i < l/2; i += 1) {
        if (s[i] != s[s.length()-1-i]) {
            return false;
        }
    }

    return true;
}

void test1();

int main(int argc, char **args) {
    (void) argc; (void) args;

    test1();

    return 0;
}

void test1() {

    s64 min = 1;
    s64 max = 1000000000;

    int ways = 0;
    s64 sum = 0;

    for (s64 n = min; n <= max; n += 1) {

        if (isPalindrome(n) == false) {
            continue;
        }

        s64 s = 2;
        s64 ss = s*s;
        while (ss < n) {

            int c = 2;
            int ccc = c*c*c;

            while (ss + ccc <= n) {

                if (ss + ccc == n) {
                    ways += 1;
                    //qDebug() << QString("%1 = %2^2 + %3^3, ways %4").arg(n, 10).arg(s, 4).arg(c, 4).arg(ways);

                    if (ways > 4) { break; }
                }

                c += 1;
                ccc = c*c*c;
            }

            if (ways > 4) { break; }

            s += 1;
            ss = s*s;
        }

        if (ways == 4) {
            sum += n;
            qDebug() << QString("%1 !!!!, sum %2").arg(n, 10).arg(sum, 12);
        }

        ways = 0;
    }

}

// "   5229225 !!!!, sum      5229225"
// "  37088073 !!!!, sum     42317298"
// "  56200265 !!!!, sum     98517563"
// " 108909801 !!!!, sum    207427364"
// " 796767697 !!!!, sum   1004195061"
