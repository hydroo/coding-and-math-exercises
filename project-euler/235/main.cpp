#include "../lib.hpp"

using namespace std;

void testTotientFunction();
void test1(int argc, char** args);

mpf_class u(const mpf_class& r, int k) {
    mpf_class uu;
    mpf_pow_ui(uu.get_mpf_t(), r.get_mpf_t(), (unsigned int) k-1);
    return uu * (900-3*k);
}

mpf_class s(const mpf_class& r, int n) {
    mpf_class sum(0);
    for (int k = 1; k <= n; k +=1) {
        auto uu = u(r, k);
        sum += uu;
    }
    return sum;
}

int main(int argc, char **args) {
    (void) argc; (void) args;

    test1(argc, args);

    return 0;
}

void test1(int argc, char** args) {

    if (argc < 3) {
        qDebug() << "Usage " << args[0] << " <r2> <n>, where r = 1 + r2 / 100";
    }

    // 1.00232210863287614253 is reasonably close
    //
    // = 1.002322108633 rounded to 12 places

    mpf_class r(atof(args[1])); // circumvents double precision ending too early
    r /= 100;
    r += 1;
    int n = atoi(args[2]);

    mpf_class diff = s(r, n) + (s64) (600LL * 1000LL * 1000LL * 1000LL);
    qDebug().noquote() << "s(" << n << ") = " << diff;

    gmp_printf ("r = %.20Ff\n", r.get_mpf_t());
}
