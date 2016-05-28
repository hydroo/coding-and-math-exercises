#include <cassert>
#include <cmath>

#include <QtDebug>

using s64 = int64_t;

using namespace std;

bool isPrime(s64 n) {
    if (n == 2) {
        return true;
    } else if (n % 2 == 0 || n == 1) {
        return false;
    }
    s64 sqrtn = floor(sqrt(n));
    for (s64 d = 3; d <= sqrtn; d += 2) {
        if (n % 3 == 0) {
            return false;
        }
    }
    return true;
}

