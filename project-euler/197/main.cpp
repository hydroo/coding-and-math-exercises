#include "../lib.hpp"

using namespace std;

void test1();

int main(int argc, char **args) {
    (void) argc; (void) args;

    test1();

    return 0;
}

mpf_class f(mpf_class x) {
    return  mpf_class(floor(std::pow(2, mpf_class(30.403243784 - x*x).get_d()))) / (1000 * 1000 * 1000);
}

mpf_class u(int n) {
    if (n == 0) {
        return -1;
    } else {
        return f(u(n-1));
    }
}

void test1() {

    const int max = 10000;

    mpf_class prev = -1;
    for (int n = 0; n <= max; n += 1) {
        mpf_class un = u(n);
        gmp_printf("u(%5d) = %.12Ff, u(n-1) + u(n) = %.12Ff\n", n, un.get_mpf_t(), mpf_class(un + prev).get_mpf_t());
        prev = un;
    }
}
