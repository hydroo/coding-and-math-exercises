#include <cassert>
#include <cstdio>

#include <QtDebug>

/* *** cuboid ****************************************************************/
struct Cuboid {
    int width, height, depth;
    bool ***m;
};

static Cuboid *newCuboid(int width, int height, int depth) {
    Cuboid *ret = (Cuboid*) malloc(sizeof(Cuboid));
    ret->width = width;
    ret->height = height;
    ret->depth = depth;

    ret->m = (bool***) malloc(sizeof(bool**) * width);
    for (int i = 0; i < width; i += 1) {
        ret->m[i] = (bool**) malloc(sizeof(bool*) * height);
        for (int j = 0; j < height; j += 1) {
            ret->m[i][j] = (bool*) malloc(sizeof(bool) * depth);
        }
    }

    return ret;
}

static Cuboid *newBasicCuboid(int width, int height, int depth) {
    Cuboid *ret = newCuboid(width, height, depth);
    for (int i = 0; i < width; i += 1) {
        for (int j = 0; j < height; j += 1) {
            for (int k = 0; k < depth; k += 1) {
                ret->m[i][j][k] = true;
            }
        }
    }
    return ret;
}

static void deleteCuboid(Cuboid *c) {
    for (int i = 0; i < c->width; i += 1) {
        for (int j = 0; j < c->height; j += 1) {
            free(c->m[i][j]);
        }
        free(c->m[i]);
    }
    free(c->m);
    free(c);
}

static void printShapeSlice(const Cuboid *c, int depth) {
    for (int i = 0; i < c->width; i += 1) {
        for (int j = 0; j < c->height; j += 1) {
            if (c->m[i][j][depth] == true) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

static int coveringCubeCount(const Cuboid *c) {
    int count = 0;

    bool ***m = c->m;

    for (int i = 0; i < c->width; i += 1) {
        for (int j = 0; j < c->height; j += 1) {
            for (int k = 0; k < c->depth; k += 1) {
                if (m[i][j][k] == false) {
                } else if (i == 0 || i == c->width-1 || j == 0 || j == c->height-1 || k == 0 || k == c->depth-1) {
                    count += 1;
                } else if (m[i][j][k-1] == false || m[i][j][k+1] == false || m[i][j-1][k] == false || m[i][j+1][k] == false || m[i-1][j][k] == false || m[i+1][j][k] == false) {
                    count += 1;
                } else {
                }
            }
        }
    }

    return count;
}

static Cuboid *addLayer(Cuboid *c) {
    Cuboid *ret = newCuboid(c->width+2, c->height+2, c->depth+2);

    // reset new Cuboid
    for (int i = 0; i < ret->width; i += 1) {
        for (int j = 0; j < ret->height; j += 1) {
            memset(ret->m[i][j], 0, sizeof(bool) * ret->depth);
        }
    }

    // copy old Cuboid and add new layer
    for (int i = 1; i < ret->width-1; i += 1) {
        for (int j = 1; j < ret->height-1; j += 1) {
            for (int k = 1; k < ret->depth-1; k += 1) {
                if (c->m[i-1][j-1][k-1] == true) {
                    ret->m[i][j][k] = true;
                    ret->m[i][j][k-1] = true;
                    ret->m[i][j][k+1] = true;
                    ret->m[i][j-1][k] = true;
                    ret->m[i][j+1][k] = true;
                    ret->m[i-1][j][k] = true;
                    ret->m[i+1][j][k] = true;
                }
            }
        }
    }

    return ret;
}

/* *** counting **************************************************************/
int cuboidCount(int wantedCoveringCubeCount) {
    int count = 0;

    for (int width = 1; width < wantedCoveringCubeCount; width += 1) {
        for (int height = width; height < wantedCoveringCubeCount; height += 1) {
            for (int depth = height; depth < wantedCoveringCubeCount; depth += 1) {

                Cuboid *c = newBasicCuboid(width, height, depth);

                for(;;) {
                    Cuboid *tmp = c;
                    c = addLayer(tmp);
                    deleteCuboid(tmp);

                    int cubeCount = coveringCubeCount(c);

                    if (cubeCount < wantedCoveringCubeCount) {
                        continue;
                    } else if (cubeCount > wantedCoveringCubeCount) {
                        break;
                    } else {
                        count += 1;
                        break;
                    }
                }

                deleteCuboid(c);
            }
        }
    }

    return count;
}

/* *** test 1 ****************************************************************/
static void test1() {
    Cuboid *s1 = newBasicCuboid(3, 2, 1);
    Cuboid *s2 = addLayer(s1);
    Cuboid *s3 = addLayer(s2);
    Cuboid *s4 = addLayer(s3);
    Cuboid *s5 = addLayer(s4);

    assert(coveringCubeCount(s1) == 6);
    assert(coveringCubeCount(s2) == 22);
    assert(coveringCubeCount(s3) == 46);
    assert(coveringCubeCount(s4) == 78);
    assert(coveringCubeCount(s5) == 118);

    deleteCuboid(s1);
    deleteCuboid(s2);
    deleteCuboid(s3);
    deleteCuboid(s4);
    deleteCuboid(s5);
}

/* *** test 2 ****************************************************************/
static void test2() {
    assert(cuboidCount(22) == 2);
    assert(cuboidCount(46) == 4);
    //assert(cuboidCount(78) == 5);
    //assert(cuboidCount(118) == 8);
}

/* *** main ******************************************************************/
int main(int argc, char **args) {

    (void) argc;
    (void) args;

    test1();
    test2();

    return 0;
}
