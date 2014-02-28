#include <cassert>

#include <QtDebug>
#include <QtGlobal>


int main(int argc, char **args) {

    Q_UNUSED(argc);
    Q_UNUSED(args);

    QMap <int, int> m;

    for (int d = 1; d < 50000000; d += 1) {

        if (d % 1000 == 0) qDebug() << d;

        qint64 d2 = (qint64)d * (qint64)d;

        int root;
        if (4*d2 <= 50000000) root = 0;
        else root = floor(sqrt(4*d2 - 50000000)) + 1;

        QSet <int> offsets;

        for (; (qint64)root*(qint64)root < 4*d2; root += 1) {

            qint64 root2 = (qint64)root * (qint64)root;

            qint64 n = 4*d2 - root2;

            Q_ASSERT(n > 0);
            if(n >= 50000000) continue;

            int o1, o2;

            o1 = 3*d + root;

            if (3*d >= root) {
                o2 = 3*d - root;
            } else {
                o2 = -1;
            }

            //int x1 = o1;
            //int y1 = o1 - d;
            int z1 = o1 - 2*d;
            //int x2 = o2;
            //int y2 = o2 - d;
            int z2 = o2 - 2*d;

            if (z1 > 0 && offsets.contains(o1) == false) {
                m[n] += 1;
                offsets.insert(o1);
            }
            if (z2 > 0 && o2 != -1 && offsets.contains(o2) == false) {
                m[n] += 1;
                offsets.insert(o2);
            }
        }
    }

    qint64 count = 0;
    QMapIterator<int, int> i(m);
    while (i.hasNext() == true) {
        i.next();
        if (i.value() == 1) count += 1;
    }
    qDebug() << count;

    return 0;
}
