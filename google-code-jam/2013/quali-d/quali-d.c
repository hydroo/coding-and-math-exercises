#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef DEBUG
#   define ASSERT(x) assert(x)
#else
#   define ASSERT(x)
#endif

//#define MAX_KEY_COUNT 21  // small input
#define MAX_KEY_COUNT 201 //large input


/* *** chest *************************************************************** */
typedef struct {
    int opened;
    int lock;
    int keys[MAX_KEY_COUNT];
} Chest;

static Chest* newChest() {
    Chest *c = (Chest*) malloc(sizeof(Chest));
    c->opened = 0;
    c->lock = -1;
    memset(c->keys, 0, sizeof(int) * MAX_KEY_COUNT);
    return c;
}

static void freeChest(Chest *c) {
    if (c == NULL) return;
    free(c);
}

static void printChest(const Chest* c) {
    if (c == NULL || c->opened == 1) {
        printf("x");
    } else {
        printf("%3i:", c->lock);
        for (int i = 0; i < MAX_KEY_COUNT; i += 1) {
            if (c->keys[i] > 0) {
                printf("%3i:%3i, ", i, c->keys[i]);
            }
        }
    }
    printf("\n");
}

/* *** state *************************************************************** */
typedef struct {
    int keys[MAX_KEY_COUNT];
    Chest **chests;
    int chestCount;
    int neededKeys[MAX_KEY_COUNT]; //keeps track of all locks that are still to be opened
} State;

static State* newState() {
    State* s = (State*) malloc(sizeof(State));
    memset(s->keys, 0, sizeof(int) * MAX_KEY_COUNT);
    s->chests = NULL;
    s->chestCount = 0;
    memset(s->neededKeys, 0, sizeof(int) * MAX_KEY_COUNT);
    return s;
}

static void freeState(State *s) {
    for (int i = 0; i < s->chestCount; i += 1) {
        freeChest(s->chests[i]);
    }
    free(s->chests);
    free(s);
}

static void printState(const State* s) {
    printf("keys: ");
    for (int i = 0; i < MAX_KEY_COUNT; i += 1) {
        if (s->keys[i] > 0) {
            printf("%3i:%3i, ", i, s->keys[i]);
        }
    }
    printf("\n");

    printf("needed keys: ");
    for (int i = 0; i < MAX_KEY_COUNT; i += 1) {
        if (s->neededKeys[i] > 0) {
            printf("%3i:%3i, ", i, s->neededKeys[i]);
        }
    }
    printf("\n");

    for (int i = 0; i < s->chestCount; i += 1) {
        printf("%3i: ", i+1);
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

    ASSERT(currentLine == lineCount);

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
    ASSERT(lineCount > 0);
    char **lines = readLines(fileName);

    // input line: caseCount
    sscanf(lines[0], "%i", caseCount);
    State **cases = (State **) malloc(sizeof(State*) * (*caseCount));

    int currentLine = 1;

    for (int caseIndex = 0; caseIndex < *caseCount; caseIndex += 1) {
        State *s = cases[caseIndex] = newState();

        int keyCount;

        // input line: keyCount chestCount
        sscanf(lines[currentLine], "%i %i", &keyCount, &(s->chestCount));
        s->chests = (Chest**) malloc(sizeof(Chest*) * s->chestCount);
        currentLine += 1;

        // input line: keys
        char *line = lines[currentLine];
        char *space = line;
        int i = 0;
        int key;
        while ((space = strchr(line, ' ')) != NULL) {
            sscanf(line, "%i", &key);
            ASSERT(key > 0 && key < MAX_KEY_COUNT);
            s->keys[key] += 1;
            line = space+1;
            i += 1;
        }
        sscanf(line, "%i", &key);
        ASSERT(key > 0 && key < MAX_KEY_COUNT);
        s->keys[key] += 1;

        ASSERT(i == (keyCount-1));
        currentLine += 1;

        // input lines chests
        for (int i = 0; i < s->chestCount; i += 1) {
            line = lines[currentLine];
            Chest *c = s->chests[i] = newChest();

            int chestKeyCount;
            sscanf(line, "%i %i", &(c->lock), &chestKeyCount);
            s->neededKeys[c->lock] += 1;

            if (chestKeyCount > 0) {
                line = strchr(strchr(line, ' ') + 1, ' ') + 1;
                char *space = line;
                int j = 0;
                int chestKey;
                while ((space = strchr(line, ' ')) != NULL) {
                    sscanf(line, "%i", &chestKey);
                    ASSERT(chestKey > 0 && chestKey < MAX_KEY_COUNT);
                    c->keys[chestKey] += 1;
                    line = space+1;
                    j += 1;
                }
                sscanf(line, "%i", &chestKey);
                ASSERT(chestKey > 0 && chestKey < MAX_KEY_COUNT);
                c->keys[chestKey] += 1;
                ASSERT(j == chestKeyCount-1);
            }

            currentLine += 1;
        }
    }

    freeLines(lines, lineCount);

    return cases;
}

/* *** helper ************************************************************** */
static void addKeys(int to[MAX_KEY_COUNT], int from[MAX_KEY_COUNT]) {
    for (int i = 0; i < MAX_KEY_COUNT; i += 1) {
        to[i] += from[i];
    }
}

static void removeKeys(int to[MAX_KEY_COUNT], int from[MAX_KEY_COUNT]) {
    for (int i = 0; i < MAX_KEY_COUNT; i += 1) {
        to[i] -= from[i];
    }
}

/* *** work **************************************************************** */
static void openChest(State *s, Chest *c) {
    ASSERT(s->keys[c->lock] > 0);
    ASSERT(s->neededKeys[c->lock] > 0);

    c->opened = 1;
    s->keys[c->lock] -= 1;
    s->neededKeys[c->lock] -= 1;
    addKeys(s->keys, c->keys);
}

static void closeChest(State *s, Chest *c) {
    c->opened = 0;
    s->keys[c->lock] += 1;
    s->neededKeys[c->lock] += 1;
    removeKeys(s->keys, c->keys);

    for (int i = 0; i < MAX_KEY_COUNT; i += 1) {
        ASSERT(s->keys[i] >= 0);
    }
}

static int solveRecursively(State *s, int *solution, int step) {

    //printState(s);

    int allChestsOpened = 1;
    int ret;

    for (int i = 0; i < s->chestCount; i += 1) {
        Chest *c = s->chests[i];

        allChestsOpened &= (c->opened == 1);

        if (c->opened == 1 || s->keys[c->lock] == 0) {
            continue;
        }

        // if we have only 1 key of this type left, and do not get another one with this chest,
        // and we need another one for another chest, then we cannot open this chest
        // (wrong)
        if (s->keys[c->lock] == 1 && c->keys[c->lock] == 0 && s->neededKeys[c->lock] > 1) {
            int noKeyAvail = 1;
            for (int j = 0; j < s->chestCount; j += 1) {
                if (s->chests[j]->opened == 0 && s->chests[j]->lock != c->lock) {
                    noKeyAvail &= s->chests[j]->keys[c->lock] == 0;
                }
            }
            if (noKeyAvail == 1) {
                continue;
            }
        }

        openChest(s, s->chests[i]);
        ret = solveRecursively(s, solution, step + 1);
        closeChest(s, s->chests[i]);

        if (ret == 1) {
            solution[step] = i;
            return 1;
        } else {
            continue;
        }
    }

    if (allChestsOpened == 1) {
        return 1; // correct solution
    } else {
        return 0; // impossible
    }
}

static int solve(State *s, int *solution, int step) {
    for (int key = 1; key < MAX_KEY_COUNT; key += 1) {
        int neededKeys = 0;
        int availableKeys = s->keys[key];

        for (int i = 0; i < s->chestCount; i += 1) {
            if (s->chests[i]->lock == key) {
                neededKeys += 1;
            }
            availableKeys += s->chests[i]->keys[key];
        }

        if (neededKeys > availableKeys) {
            //printf("key: %d: needed: %d, avail: %d\n", key, neededKeys, availableKeys);
            return 0;
        }
    }

    return solveRecursively(s, solution, step);
}

/* ************************************************************************* */
int main(int argc, char **args) {
    assert(argc > 1);
    char *inputFile = args[1];

    /* read input */
    int caseCount;
    State **cases = casesFromInput(inputFile, &caseCount);

    /* work */
    //for (int i = 2; i < 3; i += 1) {
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

