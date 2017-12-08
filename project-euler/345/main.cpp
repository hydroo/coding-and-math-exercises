#include "../lib.hpp"

using namespace std;

array<array<s64, 5>, 5> m1{{{{  7,  53, 183, 439, 863}},
                            {{497, 383, 563,  79, 973}},
                            {{287,  63, 343, 169, 583}},
                            {{627, 343, 773, 959, 943}},
                            {{767, 473, 103, 699, 303}}}};

array<array<s64, 15>, 15> m2{{{{  7,  53, 183, 439, 863, 497, 383, 563,  79, 973, 287,  63, 343, 169, 583}},
                              {{627, 343, 773, 959, 943, 767, 473, 103, 699, 303, 957, 703, 583, 639, 913}},
                              {{447, 283, 463,  29,  23, 487, 463, 993, 119, 883, 327, 493, 423, 159, 743}},
                              {{217, 623,   3, 399, 853, 407, 103, 983,  89, 463, 290, 516, 212, 462, 350}},
                              {{960, 376, 682, 962, 300, 780, 486, 502, 912, 800, 250, 346, 172, 812, 350}},
                              {{870, 456, 192, 162, 593, 473, 915,  45, 989, 873, 823, 965, 425, 329, 803}},
                              {{973, 965, 905, 919, 133, 673, 665, 235, 509, 613, 673, 815, 165, 992, 326}},
                              {{322, 148, 972, 962, 286, 255, 941, 541, 265, 323, 925, 281, 601,  95, 973}},
                              {{445, 721,  11, 525, 473,  65, 511, 164, 138, 672,  18, 428, 154, 448, 848}},
                              {{414, 456, 310, 312, 798, 104, 566, 520, 302, 248, 694, 976, 430, 392, 198}},
                              {{184, 829, 373, 181, 631, 101, 969, 613, 840, 740, 778, 458, 284, 760, 390}},
                              {{821, 461, 843, 513,  17, 901, 711, 993, 293, 157, 274,  94, 192, 156, 574}},
                              {{ 34, 124,   4, 878, 450, 476, 712, 914, 838, 669, 875, 299, 823, 329, 699}},
                              {{815, 559, 813, 459, 522, 788, 168, 586, 966, 232, 308, 833, 251, 631, 107}},
                              {{813, 883, 451, 509, 615,  77, 281, 613, 459, 205, 380, 274, 302,  35, 805}}}};

void test1();

int main(int argc, char **args) {
    (void) argc; (void) args;

    test1();

    return 0;
}

void test1() {

    //constexpr auto& m = m1;
    constexpr auto& m = m2;
    assert(m.size() == m[0].size());
    constexpr int s = m.size();

    qDebug() << m;
    qDebug() << "";

    array<tuple<s64, int, int>, s*s> sorted_;
    for (int i = 0; i < (int) sorted_.size(); i += 1) {
        sorted_[i] = {-1, -1, -1};
    }

    for (int x = 0; x < s; x += 1) {
        for (int y = 0; y < s; y += 1) {
            sorted_[y*s + x] = make_tuple(m[y][x], x, y);
        }
    }

    std::sort(begin(sorted_), end(sorted_), [](const tuple<s64, int, int>a, const tuple<s64, int, int>& b){ return a > b; });

    for (int i = 0; i < (int) sorted_.size(); i += 1) {
        qDebug() << std::get<0>(sorted_[i]) << std::get<1>(sorted_[i]) << std::get<2>(sorted_[i]);
    }
    qDebug() << "";

    // This is probably considered cheating, but trimming the sorted list of matrix entries made the recursion manageable
    // this hack takes away the guarantee to find the global optimum
    array<tuple<s64, int, int>, s*s/4 /*this*/> sorted; 
    for (int i = 0; i < (int) sorted.size(); i += 1) {
        sorted[i] = sorted_[i];
    }

    array<int, s> xs;
    array<int, s> ys;
    for (int i = 0; i < s; i += 1) {
        xs[i] = i;
        ys[i] = i;
    }

    s64 maxsum = 0;

    array<s64, s> sol;
    for (int i = 0; i < s; i += 1) {
        sol[i] = -1;
    }

    function<void(int, array<int, s>, array<int, s>, s64, array<s64, s>, int)> recurse = [&recurse, &maxsum, &sorted](int cur, array<int, s> xs, array<int, s> ys, s64 sum, array<s64, s> sol, int soli) {

        if (sum > maxsum) {
            maxsum = sum;
            qDebug() << "maxsum" << maxsum << "sol" << sol;
        }

        for (int i = cur; i < (int) sorted.size(); i += 1) {

            int x = get<1>(sorted[i]);
            int y = get<2>(sorted[i]);

            if (xs[x] == -1 || ys[y] == -1) {
                continue;
            } else {
                xs[x] = -1;
                ys[y] = -1;

                sol[soli] = get<0>(sorted[i]);

                recurse(i+1, xs, ys, sum + std::get<0>(sorted[i]), sol, soli + 1);

                xs[x] = x;
                ys[y] = y;

            }
        }
    };

    recurse(0, xs, ys, 0, sol, 0);
}
