#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

#include <../lib.hpp>

using namespace std;
using u64 = uint64_t;


constexpr u64 bits = 32;

void main2();

int main(int argc, char **args) {
    (void) argc;
    (void) args;

    int i = 1;
    constexpr int i_max = 100;
    mpz_class den = 1;

    std::array<mpq_class, i_max+1> p;
    mpf_class E = 0;

    do {
        den *= 2;

        // probability of one bit not being 1 = 1 - (1/(2)^i)
        //
        // probability of all bits not being 1 = (1 - (1/(2)^i))^bits

        mpz_class nom(den-1);

        mpz_class nom2;
        mpz_class den2;
        mpz_pow_ui(nom2.get_mpz_t(), nom.get_mpz_t(), bits);
        mpz_pow_ui(den2.get_mpz_t(), den.get_mpz_t(), bits);

        // subtract all p's from lower i's from the current p
        p[i] = mpq_class(nom2) / mpq_class(den2);
        for (int j = 1; j < i; j += 1) {
            p[i] -= p[j];
        }

        // E = p*i;
        E += mpf_class(p[i])*i;
        std::cerr << "P(i <= " << setw(1 + (int)ceil(log10(i_max))) << i << ") = " << setprecision(15) << fixed << mpf_class(p[i]) << " " << E << std::endl;

        i += 1;

    } while (i <= i_max);

    return 0;
}
