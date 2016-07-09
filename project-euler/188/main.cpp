#include "../lib.hpp"


mpz_class hyperexpmod(const mpz_class& n, int exp, const mpz_class& mod) {
    mpz_class ret;

    if (exp == 1) {
        mpz_mod(ret.get_mpz_t(), n.get_mpz_t(), mod.get_mpz_t());
    } else {
        mpz_powm(ret.get_mpz_t(), n.get_mpz_t(), hyperexpmod(n, exp-1, mod).get_mpz_t(), mod.get_mpz_t());
    }

    return ret;
}

void test1();

int main() {

    test1();
    
    qDebug() << hyperexpmod(1777, 1855, 100000000);

    return 0;
}

void test1() {
    assert(hyperexpmod(3, 2,            100) ==            27);
    assert(hyperexpmod(3, 3, 10000000000000) == 7625597484987);
}
