#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int lessThanInt (const void *a, const void *b);


/* *** chest *************************************************************** */
typedef struct {
    int lock;
    int *keys;
    int keyCount;
} Chest;

static Chest* newChest() {
    Chest *c = (Chest*) malloc(sizeof(Chest));
    c->lock = -1;
    c->keys = NULL;
    c->keyCount = 0;
    return c;
}

static Chest* duplicateChest(const Chest *c) {
    Chest *d = (Chest*) malloc(sizeof(Chest));
    d->lock = c->lock;
    if (c->keys == NULL) {
        d->keys = NULL;
    } else {
        d->keys = (int*) malloc(sizeof(int) * c->keyCount);
    }
    d->keyCount = c->keyCount;
    for (int i = 0; i < d->keyCount; i += 1) {
        d->keys[i] = c->keys[i];
    }
    return d;
}

static void freeChest(Chest *c) {
    if (c == NULL) return;
    free(c->keys);
    free(c);
}

static void printChest(const Chest* c) {
    if (c == NULL) {
        printf("x");
    } else {
        printf("%3i:", c->lock);
        for (int i = 0; i < c->keyCount; i += 1) {
            printf("%3i, ", c->keys[i]);
        }
    }
    printf("\n");
}

/* *** state *************************************************************** */
typedef struct {
    int *keys;
    int keyCount;
    Chest **chests;
    int chestCount;
} State;

static State* newState() {
    State* s = (State*) malloc(sizeof(State));
    s->keys = NULL;
    s->keyCount = 0;
    s->chests = NULL;
    s->chestCount = 0;
    return s;
}

static State *duplicateState(const State* s) {
    State *t = (State*) malloc(sizeof(State));
    if (s->keys == NULL) {
        t->keys = NULL;
    } else {
        t->keys = (int*) malloc(sizeof(int) * s->keyCount);
    }
    t->keyCount = s->keyCount;
    for (int i = 0; i < t->keyCount; i += 1) {
        t->keys[i] = s->keys[i];
    }
    t->chests = (Chest**) malloc(sizeof(Chest*) * s->chestCount);
    t->chestCount = s->chestCount;
    for (int i = 0; i < t->chestCount; i += 1) {
        if (s->chests[i] == NULL) {
            t->chests[i] = NULL;
        } else {
            t->chests[i] = duplicateChest(s->chests[i]);
        }
    }
    return t;
}

static void freeState(State *s) {
    free(s->keys);
    for (int i = 0; i < s->chestCount; i += 1) {
        freeChest(s->chests[i]);
    }
    free(s->chests);
    free(s);
}

static void printState(const State* s) {
    printf("keys: ");
    for (int i = 0; i < s->keyCount; i += 1) {
        printf("%3i, ", s->keys[i]);
    }
    printf("\n");

    for (int i = 0; i < s->chestCount; i += 1) {
        printf("%3i: ", i);
        printChest(s->chests[i]);
    }
}

/* *** input *************************************************************** */
static int countLines(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    assert(f != NULL);
    char s[1024];
    int l;
    int newLineCount = 0;
    while ((l = fread(s, sizeof(char), 1024, f)) > 0) {
        for (int i = 0; i < l; i += 1) {
            if (s[i] == '\n') { newLineCount += 1; }
        }
    }
    fclose(f);
    return newLineCount;
}

static char **readLines(const char *fileName) {
    int lineCount = countLines(fileName);
    char **lines = (char**) malloc(sizeof(char*) * lineCount);

    FILE *f = fopen(fileName, "r");
    assert(f != NULL);

    int currentLine = 0;
    char *line = NULL;
    size_t lineLength;
    int l;
    while ((l = getline(&line, &lineLength, f)) != -1) {
        lines[currentLine] = strdup(line);
        currentLine += 1;
    }
    free(line);

    assert(currentLine == lineCount);

    return lines;
}

static void freeLines(char **lines, int lineCount) {
    for (int i = 0; i < lineCount; i += 1) {
        free(lines[i]);
    }
    free(lines);
}

static State **casesFromInput(const char *fileName, int *caseCount) {
    int lineCount = countLines(fileName);
    assert(lineCount > 0);
    char **lines = readLines(fileName);

    // input line: caseCount
    sscanf(lines[0], "%i", caseCount);
    State **cases = (State **) malloc(sizeof(State*) * (*caseCount));

    int currentLine = 1;

    for (int caseIndex = 0; caseIndex < *caseCount; caseIndex += 1) {
        State *s = cases[caseIndex] = newState();

        // input line: keyCount chestCount
        sscanf(lines[currentLine], "%i %i", &(s->keyCount), &(s->chestCount));
        s->keys = (int*) malloc(sizeof(int) * s->keyCount);
        s->chests = (Chest**) malloc(sizeof(Chest*) * s->chestCount);
        currentLine += 1;

        // input line: keys
        char *line = lines[currentLine];
        char *space = line;
        int i = 0;
        while ((space = strchr(line, ' ')) != NULL) {
            sscanf(line, "%i", &(s->keys[i]));
            line = space+1;
            i += 1;
        }
        sscanf(line, "%i", &(s->keys[i]));
        assert(i == (s->keyCount-1));
        currentLine += 1;

        qsort(s->keys, s->keyCount, sizeof(int), lessThanInt);

        // input lines chests
        for (int i = 0; i < s->chestCount; i += 1) {
            line = lines[currentLine];
            Chest *c = s->chests[i] = newChest();

            sscanf(line, "%i %i", &(c->lock), &(c->keyCount));

            if (c->keyCount != 0) {
                c->keys = (int*) malloc(sizeof(int) * c->keyCount);

                line = strchr(strchr(line, ' ') + 1, ' ') + 1;
                char *space = line;
                int j = 0;
                while ((space = strchr(line, ' ')) != NULL) {
                    sscanf(line, "%i", &(c->keys[j]));
                    line = space+1;
                    j += 1;
                }
                sscanf(line, "%i", &(c->keys[j]));
                assert(j == (c->keyCount-1));

                qsort(c->keys, c->keyCount, sizeof(int), lessThanInt);
            }

            currentLine += 1;
        }
    }

    freeLines(lines, lineCount);

    return cases;
}

/* *** helper ************************************************************** */
static int findIntRecursive(const int *v, int begin, int end, int key);

static int lessThanInt (const void *a_, const void *b_) {
    int a = *((int*)a_);
    int b = *((int*)b_);
    if (a > b) { return 1; } else if (a < b) { return -1; } else { return 0; }
}

/* returns -1 for not foudn or the first index of the searched element */
static int findInt(const int *v, int vLen, int key) {
    if (v == NULL) return -1;
    return findIntRecursive(v, 0, vLen-1, key);
}

static int findIntRecursive(const int *v, int begin, int end, int key) {
    if (begin > end) {
        return -1;
    }  else {
        int m = (end-begin) / 2 ;
        if (v[m] > key) {
            return findIntRecursive(v, key, begin, m-1);
        } else if (v[m] < key) {
            return findIntRecursive(v, key, m+1, end);
        } else {
            return m;
        }
    }
}

static int *removeInt(int *v, int vLen, int index) {
    assert(vLen > 0);
    assert(v != NULL);

    if (vLen == 1) {
        free(v);
        return NULL;
    }

    int *w = (int *) malloc(sizeof(int) * (vLen-1));

    int i = 0;
    while (i < index) {
        w[i] = v[i];
        i += 1;
    }
    i += 1;
    while (i > index && i < vLen) {
        w[i-1] = v[i];
        i += 1;
    }

    free(v);

    return w;
}

static int *mergeArrays(int *v, int vLen, int *w, int wLen) {
    int *x = (int*) malloc(sizeof(int) * (vLen + wLen));
    for (int i = 0; i < vLen; i += 1) {
        x[i] = v[i];
    }
    for (int i = 0; i < wLen; i += 1) {
        x[i+vLen] = w[i];
    }
    qsort(x, vLen+wLen, sizeof(int), lessThanInt);
    return x;
}

/* *** work **************************************************************** */
static int solve(State *s, int *solution, int step) {

    int allChestsNull = 1;

    for (int i = 0; i < s->chestCount; i += 1) {
        Chest *c = s->chests[i];

        allChestsNull &= (c == NULL);

        if (c == NULL) {
            continue;
        }

        int keyIndex;

        if ((keyIndex = findInt(s->keys, s->keyCount, c->lock)) == -1) { continue; }

        State *t = duplicateState(s);
        t->keys = removeInt(t->keys, t->keyCount, keyIndex);
        t->keyCount = t->keyCount-1;

        int *tmp = t->keys;
        t->keys = mergeArrays(t->keys, t->keyCount, t->chests[i]->keys, t->chests[i]->keyCount);
        t->keyCount += t->chests[i]->keyCount;
        free(tmp);
        freeChest(t->chests[i]);
        t->chests[i] = NULL;

        int ret = solve(t, solution, step + 1);
        freeState(t);

        if (ret == 1) {
            solution[step] = i;
            return 1;
        } else {
            continue;
        }
    }

    if (allChestsNull == 1) {
        return 1;
    } else {
        return 0;
    }
}

/* ************************************************************************* */
int main(int argc, char **args) {
    assert(argc > 1);
    char *inputFile = strdup(args[1]);

    /* read input */
    int caseCount;
    State **cases = casesFromInput(inputFile, &caseCount);

    /* work */
    //for (int i = 0; i < 1; i += 1) {
    for (int i = 0; i < caseCount; i += 1) {
        int *solution = (int*) malloc(sizeof(int) * cases[i]->chestCount);
        int solutionLen = cases[i]->chestCount;

        int ret = solve(cases[i], solution, 0);

        printf("Case #%i: ", i + 1);
        if (ret == 0) {
            printf("IMPOSSIBLE");
        } else {
            for (int i = 0; i < solutionLen; i += 1) {
                if (i < solutionLen-1) {
                    printf("%i ", solution[i] + 1);
                }
                else {
                    printf("%i", solution[i] + 1);
                }
            }
        }
        printf("\n");
    }

    /* free */
    for (int i = 0; i < caseCount; i += 1) {
        freeState(cases[i]);
    }
    free(cases);

    return 0;
}

