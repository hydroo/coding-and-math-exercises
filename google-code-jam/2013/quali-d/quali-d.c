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
        memcpy(d->keys, c->keys, c->keyCount * sizeof(int));
    }
    d->keyCount = c->keyCount;
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

//static State *duplicateState(const State* s) {
//}
//
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

    fclose(f);

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

/* *** work **************************************************************** */
static State* openChest(State *s, int chestIndex, int keyIndex) {

    Chest *c = s->chests[chestIndex];

    State *t = (State*) malloc(sizeof(State));
    t->keyCount = s->keyCount + c->keyCount - 1;

    if (t->keyCount == 0) {
        t->keys = NULL;
    } else {
        t->keys = (int*) malloc(sizeof(int) * t->keyCount);

        if (keyIndex > 0 && keyIndex < s->keyCount-1) {
            // copy left side
            memcpy(t->keys, s->keys, keyIndex * sizeof(int));
        }
        if (keyIndex < s->keyCount-1) {
            //copy right side
            memcpy(&(t->keys[keyIndex]), &(s->keys[keyIndex+1]), (s->keyCount - (keyIndex+1)) * sizeof(int));
        }

        if (c->keyCount > 0) {
            // copy chest keys
            memcpy(&(t->keys[s->keyCount-1]), c->keys, c->keyCount * sizeof(int));
        }

        if (t->keyCount != c->keyCount) {
            qsort(t->keys, t->keyCount, sizeof(int), lessThanInt);
        }
    }

    t->chests = (Chest**) malloc(sizeof(Chest*) * s->chestCount);
    t->chestCount = s->chestCount;
    for (int i = 0; i < t->chestCount; i += 1) {
        if (s->chests[i] == NULL || i == chestIndex) {
            t->chests[i] = NULL;
        } else {
            t->chests[i] = duplicateChest(s->chests[i]);
        }
    }

    return t;
}

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

        State *t = openChest(s, i, keyIndex);
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
    char *inputFile = args[1];

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

        free(solution);
    }

    /* free */
    for (int i = 0; i < caseCount; i += 1) {
        freeState(cases[i]);
    }
    free(cases);

    return 0;
}

