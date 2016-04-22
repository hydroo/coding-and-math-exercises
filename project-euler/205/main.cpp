#include <cassert>
#include <cmath>

#include <functional>
#include <numeric>
#include <sstream>

#include <boost/multiprecision/gmp.hpp>

#include <QtDebug>


using s64 = int64_t;

using namespace std;

using boost::multiprecision::mpq_rational;

QDebug operator<<(QDebug d, const mpq_rational& r) {
    d.nospace();
    d.noquote();
    stringstream s;
    s << r;
    d << QString::fromStdString(s.str());
    return d.resetFormat();
}

QMap<int /*roll*/, s64 /*count*/> rolls(int sides, int repetitions) {

    std::function<void(int , int, QMap<int, s64>*)> traverse = [&traverse, sides, repetitions](int sum, int rep, QMap<int, s64>* ret) {
        if (rep == repetitions) {
            if (ret->contains(sum) == false) {
                (*ret)[sum] = 0;
            }
            (*ret)[sum] += 1;
            return;
        }

        for (int i = 1; i <= sides; i += 1) {
            traverse(sum + i, rep + 1, ret);
        }
    };

    QMap<int, s64> ret;

    traverse(0, 0, &ret);

    return ret;
}

mpq_rational winProbability(int sides1, int reps1, int sides2, int reps2) {
    auto rolls1 = rolls(sides1, reps1);
    auto rolls2 = rolls(sides2, reps2);

    auto values1 = rolls1.values();
    auto values2 = rolls2.values();

    s64 sum1 = accumulate(begin(values1), end(values1), 0);
    s64 sum2 = accumulate(begin(values2), end(values2), 0);

    mpq_rational ret(0);

    QMap<int, s64>::const_iterator i = rolls2.constBegin();
    while (i != rolls2.constEnd()) {
        mpq_rational pickProbability(i.value(), sum1);

        s64 winNumerator = 0;

        QMap<int, s64>::const_iterator j = rolls1.constBegin();
        while (j != rolls1.constEnd()) {

            if (j.key() < i.key()) {
                winNumerator += j.value();
                //qDebug() << "  +" << j.key() << j.value() << winNumerator;
            } else {
                //qDebug() << "  -" << j.key();
            }

            ++j;
        }

        ret += pickProbability*mpq_rational(winNumerator, sum2);

        //qDebug() << "sum" << i.key() << ", pick" << pickProbability << ", win this" << mpq_rational(winNumerator, sum2) << ", total" << ret;

        ++i;
    }

    return ret;
}

void testRolls();
void test1();

int main(int argc, char **args) {
    Q_UNUSED(argc); Q_UNUSED(args);

    testRolls();
    test1();

    return 0;
}

void testRolls() {

    auto a31 = rolls(3, 1);
        assert(a31.size() == 3);
        assert(a31[1] == 1);
        assert(a31[2] == 1);
        assert(a31[3] == 1);

    auto a22 = rolls(2, 2);
        assert(a22.size() == 3);
        assert(a22[2] == 1);
        assert(a22[3] == 2);
        assert(a22[4] == 1);

    auto a49 = rolls(4, 9).values(); assert(accumulate(begin(a49), end(a49), 0) == 262144);
    auto a66 = rolls(6, 6).values(); assert(accumulate(begin(a66), end(a66), 0) ==  46656);
}

void test1() {
    qDebug() << winProbability(6, 6, 4, 9);
}
