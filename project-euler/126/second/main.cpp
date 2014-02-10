#include <cassert>
#include <cstdio>

#include <QtDebug>

/* *** cuboid ****************************************************************/
static int ring(int w, int d, int layer) {
    int count = 0;
    count += 2*w; // front, back
    count += 2*d; // left, right
    count += 4*(layer-1); //corners

    return count;
}

static int cubeCount(int w, int h, int d, int layer) {
    int count = 0;

    count += 2*w*d; // top, bottom area

    count += ring(w, d, layer)*h; // middlering

    for (int i = 1; i < layer; i += 1) { // rings from top to bottom
        count += 2*ring(w, d, i);
    }

    return count;
}

static int cuboidCount(int wantedCubeCount) {
    int count = 0;

    for (int w = 1; w < wantedCubeCount; w += 1) {
        for (int h = w; h < wantedCubeCount; h += 1) {
            for (int d = h; d < wantedCubeCount; d += 1) {

                for(int layer = 1;; layer += 1) {
                    int cubeCount_ = cubeCount(w, h, d, layer);

                    if (cubeCount_ < wantedCubeCount) {
                        continue;
                    } else if (cubeCount_ > wantedCubeCount) {
                        break;
                    } else {
                        count += 1;
                        break;
                    }
                }

            }
        }
    }

    return count;
}

/* *** test 1 ****************************************************************/
static void test1() {
    //qDebug() << 22 << cuboidCount(22);
    //qDebug() << 46 << cuboidCount(46);
    //qDebug() << 78 << cuboidCount(78);
    //qDebug() << 118 << cuboidCount(118);
    assert(cubeCount(3, 2, 1, 1) == 22);
    assert(cubeCount(3, 2, 1, 2) == 46);
    assert(cubeCount(3, 2, 1, 3) == 78);
    assert(cubeCount(3, 2, 1, 4) == 118);
}

/* *** test 2 ****************************************************************/
static void test2() {
    assert(cuboidCount(22) == 2);
    assert(cuboidCount(46) == 4);
    assert(cuboidCount(78) == 5);
    assert(cuboidCount(118) == 8);
    assert(cuboidCount(154) == 10);
    for (int i = 1; i < 154; i += 1) {
        assert(cuboidCount(i) != 10);
    }
}

/* *** main ******************************************************************/
int main(int argc, char **args) {
    (void) argc;
    (void) args;

    test1();
    test2();

    int max = 0;

    for (int i = 0; i < 30000; i += 1) {
        int c = cuboidCount(i);
        if (c > max) {
            max = c;
            qDebug() << i << max;
        }

        if (c == 1000) {
            qDebug() << QString("C(%1) = 1000 !!!!").arg(i);
        }
    }

    return 0;
}
