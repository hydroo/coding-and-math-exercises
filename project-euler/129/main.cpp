#include <cassert>

#include <QString>
#include <QtDebug>
#include <QtGlobal>

static int A(int n) {
    int m = 1;
    int sum = 0;
    int i = 1;
    for(; i <= n; i += 1) {
        m = (m*10) % n;
        sum = (sum + m) % n;

        if (sum == 0) {
            break;
        }
    }
    return i;
}

int main(int argc, char **args) {
    Q_UNUSED(argc);
    Q_UNUSED(args);

    int a;
    for(int i = 999999;; i += 2) {
        if (i % 2 == 0 || i % 5 == 0) continue;

        a = A(i);

        if (a > 1000000) {
            qDebug() << "!!!" << i << a;
            break;
        }
    }

    return 0;
}
