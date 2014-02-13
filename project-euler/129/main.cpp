#include <cassert>

#include <QtDebug>
#include <QtGlobal>

/* *** helpers ***************************************************************/

/* *** repunit ***************************************************************/
static qint64 repunit(int k) { // R(k)
    Q_ASSERT(k > 0);
    if (k > 19) { return -1; }

    qint64 r = 1;
    for (int i = 1; i < k; i += 1) {
        r = r*10 + 1;
    }
    return r;
}

static qint64 leastRepunit(int div) { // A(n)
    for (int i = 1;; i += 1) {
        qint64 r = repunit(i);
        if (r % div == 0 || r == -1) {
            return r;
        }
    }
}

/* *** tests *****************************************************************/
static void test1() {
    assert(repunit(1) == 1);
    assert(repunit(3) == 111);
    assert(repunit(9) == 111111111);

    assert(leastRepunit(7)  == 111111);
    assert(leastRepunit(41) == 11111);

    //                                                     3 5 7 11 13 17 19 23 29 31 37 41
    for (int i =  2; i < 20; i +=  2) assert(repunit(i) % (      11                                             ) == 0);
    for (int i =  3; i < 20; i +=  3) assert(repunit(i) % (3*                         37                        ) == 0);
    for (int i =  4; i < 20; i +=  4) assert(repunit(i) % (      11*                          101               ) == 0);
    for (int i =  5; i < 20; i +=  5) assert(repunit(i) % (                              41*  271               ) == 0);
    for (int i =  6; i < 20; i +=  6) assert(repunit(i) % (3*  7*11*13*               37                        ) == 0);
    for (int i =  7; i < 20; i +=  7) assert(repunit(i) % (                                   239*4649          ) == 0);
    for (int i =  8; i < 20; i +=  8) assert(repunit(i) % (      11*                          73*101*137        ) == 0);
    for (int i =  9; i < 20; i +=  9) assert(repunit(i) % (3*3*                       37*     333667            ) == 0);
    for (int i = 10; i < 20; i += 10) assert(repunit(i) % (      11*                     41*  271*9091          ) == 0);
    for (int i = 11; i < 20; i += 11) assert(repunit(i) % (                                   21649*513239LL    ) == 0);
    for (int i = 12; i < 20; i += 12) assert(repunit(i) % (3*  7*11*13*               37*     101*9901LL        ) == 0);
    for (int i = 13; i < 20; i += 13) assert(repunit(i) % (                                   53*79*265371653LL ) == 0);
    for (int i = 14; i < 20; i += 13) assert(repunit(i) % (      11*                          239*4649*909091LL ) == 0);
    for (int i = 15; i < 20; i += 13) assert(repunit(i) % (3*                      31*37*41*  271*2906161LL     ) == 0);
}

/* *** main ******************************************************************/
int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    test1();

    //for (int i = 1; i < 100; i += 1) {
    //    if ( i % 2 == 0 || i % 5 == 0) continue;
    //    qDebug() << i << leastRepunit(i) << leastRepunit(i) / i;
    //}

    return 0;
}
