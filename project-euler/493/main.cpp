#include <cassert>
#include <cmath>
#include <boost/multiprecision/gmp.hpp>

#include <array>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

#include <functional>

#include <QtDebug>
#include <QTime>

#include "lrucache.hpp"

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

template<class T, std::size_t N>
QDebug operator<<(QDebug d, const array<T, N>& a) {
    d.nospace();
    d.noquote();

    d << "std::array(";
    for(auto i = begin(a); i != end(a); ++i) {
        d << *i;
        if (distance(i, end(a)) > 1) {
            d << ", ";
        }
    }
    d << ")";
    return d.resetFormat();
}

template<class T>
QDebug operator<<(QDebug d, const vector<T>& v) {
    d.nospace();
    d.noquote();
    d << "std::vector(";
    for(auto i = begin(v); i != end(v); ++i) {
        d << *i;
        if (distance(i, end(v)) > 1) {
            d << ", ";
        }
    }
    d << ")";
    return d.resetFormat();
}

template<class S, class T>
QDebug operator<<(QDebug d, const pair<S, T>& p) {
    d.nospace();
    d.noquote();
    d << "std::pair(" << p.first << ", " << p.second << ")";
    return d.resetFormat();
}

// warning: this is only supposed to work for our narrow task of 10 balls for 7 colors. this could go wrong in other cases.
namespace std {
template<size_t L>
struct hash<array<int8_t, L>>
{
    size_t operator()(const array<int8_t, L>& a) const {
        int shift = 0;
        size_t ret = 0;

        foreach (int8_t i, a) {
            ret += i << shift;
            shift += 4;
        }

        return ret;
    }
};
}

template<int NumberOfColors, int NumberOfBallsPerColor>
class Urn {
public:
    Urn() {
        _urn[NumberOfBallsPerColor] = NumberOfColors;
        for (auto i = 0; i < NumberOfBallsPerColor; i += 1) {
            _urn[i] = 0;
        }
    }

    //bool operator==(const Urn<NumberOfColors, NumberOfBallsPerColor>& u) const {
    //    return _urn == u._urn;
    //}

    //bool operator<(const Urn<NumberOfColors, NumberOfBallsPerColor>& u) const {
    //    for (auto i = begin(_urn), j = begin(u._urn); i != end(_urn); ++i, ++j) {
    //        if (*i < *j) return true;
    //    }
    //    return false;
    //}

    bool sumOfElementsIsCorrect() const {
        int8_t sum = 0;
        for (auto i = begin(_urn); i != end(_urn); ++i) {
            sum += *i;
        }
        return sum == NumberOfColors;
    }

    int distinctDrawnColors() const {
        return NumberOfColors - _urn[NumberOfBallsPerColor];
    }

    vector<pair<int /*index*/, mpq_rational /*prob*/>> pickOptions(int remainingBalls) const {
        vector<pair<int, mpq_rational>> options;

        int balls = remainingBalls;

        for (int i = 1; i <= NumberOfBallsPerColor; i += 1) {
            if (_urn[i] > 0) {
                options.emplace_back(make_pair(i, mpq_rational((int)_urn[i]*i, balls)));
            }
        }
        return options;
    }

    void pick(int i) {
        assert(i > 0 && i < (int) _urn.size()); // remove for more speed
        assert(_urn[i] > 0);                    // remove for more speed
        _urn[i] -= 1;
        _urn[i-1] += 1;
    }

    mpq_rational expectedNumberOfDistinctColors(int picks_) const {

        assert(picks_ <= NumberOfColors*NumberOfBallsPerColor);

        function<mpq_rational(Urn<NumberOfColors, NumberOfBallsPerColor>, mpq_rational, int, lru_cache<array<int8_t, NumberOfBallsPerColor + 1>, mpq_rational>*)> recurse = [&recurse, &picks_](Urn<NumberOfColors, NumberOfBallsPerColor> u, mpq_rational p, int picks, lru_cache<array<int8_t, NumberOfBallsPerColor + 1>, mpq_rational>* cache) -> mpq_rational {

            if (picks == 0) {
                return u.distinctDrawnColors();
            }

            if (cache->exists(u._urn)) {
                return cache->get(u._urn);
            }

            mpq_rational e = 0;

            for (const auto& pick : u.pickOptions(NumberOfBallsPerColor*NumberOfColors - (picks_ - picks))) {
                auto uCopy = u;
                uCopy.pick(pick.first);

                e += recurse(uCopy, p*pick.second, picks-1, cache)*pick.second;
            }

            cache->put(u._urn, e);

            return e;
        };

        lru_cache<array<int8_t, NumberOfBallsPerColor + 1>, mpq_rational> cache(100000);


        auto ret = recurse(*this, 1, picks_, &cache);

        return ret;
    }

//private:
public: // for testing
    array<int8_t, NumberOfBallsPerColor + 1> _urn; // _urn[numberofballs] = numberofcolors that have as many balls
};


void test() {
    Urn<7, 10> u710; assert(u710._urn.size() == 11);
    assert(u710._urn[10] == 7);
    for(auto i = 0; i < 10; i += 1) assert(u710._urn[i] == 0);
    assert(u710.sumOfElementsIsCorrect());

    Urn<1, 1> u11;
    assert(u11.expectedNumberOfDistinctColors(1) == 1);

    Urn<1, 2> u12;
    assert(u12.expectedNumberOfDistinctColors(1) == 1);
    assert(u12.expectedNumberOfDistinctColors(2) == 1);

    Urn<2, 3> u22;
    assert(u22.expectedNumberOfDistinctColors(2) == 1*mpq_rational(4, 10) + 2*mpq_rational( 6, 10));
    assert(u22.expectedNumberOfDistinctColors(3) == 1*mpq_rational(4, 40) + 2*mpq_rational(36, 40));
    assert(u22.expectedNumberOfDistinctColors(4) == 2);
    assert(u22.expectedNumberOfDistinctColors(5) == 2);
    assert(u22.expectedNumberOfDistinctColors(6) == 2);

    Urn<3, 2> u32_;
    assert(u32_.expectedNumberOfDistinctColors(2) == 1*mpq_rational( 3, 15) + 2*mpq_rational(12, 15));
    assert(u32_.expectedNumberOfDistinctColors(3) == 2*mpq_rational(18, 30) + 3*mpq_rational(12, 30));
    //assert(u32_.expectedNumberOfDistinctColors(4) == );
    //assert(u32_.expectedNumberOfDistinctColors(5) == );
    assert(u32_.expectedNumberOfDistinctColors(6) == 3);
}

void doit() {
    Urn<7, 10> u;
    qDebug() << u.expectedNumberOfDistinctColors(20);
}

int main() {

    test();

    doit();

    return 0;
}
