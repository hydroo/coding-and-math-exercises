#include "../lib.hpp"

s64 numberOfResilientFractions2(s64 d, double ratio, const QVector<s64>& primes) {

    s64 maxResilientN = (s64) ceil(ratio*(d-1));

    QVector<s64> nonFactorsOfD;
    int i = 0;
    while (primes[i] < d) {
        if (d % primes[i] != 0) {
            nonFactorsOfD << primes[i];
        }
        i += 1;
    }

    QSet<s64> resilientN;

    function<void(s64)> recurse = [&d, &nonFactorsOfD, &resilientN, &recurse](s64 n) {
        for (int i = 0; i < nonFactorsOfD.size() && n*nonFactorsOfD[i] < d; i += 1) {
            resilientN << n*nonFactorsOfD[i];
            recurse(n*nonFactorsOfD[i]);
        }
    };

    for (int i = nonFactorsOfD.size()-1; i >= 0; i -= 1) {
        resilientN << nonFactorsOfD[i];
        recurse(nonFactorsOfD[i]);
        if (resilientN.size() >= maxResilientN) { return d-1; } // quick exit if no new candidate
    }

    //qDebug() << "d:" << d << ", non-factors:"<< nonFactorsOfD << ", resilient numerators:" << resilientN;

    return 1 + resilientN.size();
}

s64 numberOfResilientFractions(s64 d) {
    assert(d >= 2);
    s64 ret = 1;
    for (s64 n = 2; n < d; n += 1) {
        if (gcd(n, d) == 1) {
            ret += 1;
        }
    }
    return ret;
}

void tooSlow();
void gottaGoFaster();
void testNumberOfResilientFractions();
void testNumberOfResilientFractions2();

int main() {
    testNumberOfResilientFractions();
    testNumberOfResilientFractions2();
    //tooSlow();
    gottaGoFaster();
    return 0;
}

void gottaGoFaster() {

    double wantedResilienceRatio = 15499.0 / 94744.0;
    s64 start = 90090;
    s64 max = 1000000;

    qDebug() << "Wanted R(d) <" << wantedResilienceRatio;

    QVector<s64> primes;
    primesToAtLeast(max, &primes);

    double lowestRatio = 1.0;
    for (s64 d = start; d <= max; d += 1) {

        auto resilient = numberOfResilientFractions2(d, lowestRatio, primes);

        double ratio = ((double) resilient) / ((double) (d-1));
        if (ratio < lowestRatio) {
            lowestRatio = ratio;
            qDebug() << ratio << "=" << resilient << "/" << d-1 << ", d:" << d;
        }
        if (ratio < wantedResilienceRatio) {
            qDebug() << "Solution" << d;
            break;
        }
    }
}

void tooSlow() {
    double wantedResilienceRatio = 15499.0 / 94744.0;
    s64 max = 10 * 1000 * 1000;

    qDebug() << "Wanted R(d) <" << wantedResilienceRatio;

    double lowestRatio = 1.0;
    for (s64 d = 2; d <= max; d += 1) {

        double ratio = ((double) numberOfResilientFractions(d)) / ((double) (d-1));
        if (ratio < lowestRatio) {
            lowestRatio = ratio;
            qDebug() << ratio << ", d:" << d;
        }
        if (ratio < wantedResilienceRatio) {
            qDebug() << "Solution" << d;
        }
    }
}

void testNumberOfResilientFractions() {
    assert(numberOfResilientFractions( 2) ==  1); // 1
    assert(numberOfResilientFractions( 3) ==  2); // 1
    assert(numberOfResilientFractions( 4) ==  2); // 2
    assert(numberOfResilientFractions( 5) ==  4); // 1
    assert(numberOfResilientFractions( 6) ==  2); // 4
    assert(numberOfResilientFractions( 7) ==  6); // 1
    assert(numberOfResilientFractions( 8) ==  4); // 4
    assert(numberOfResilientFractions( 9) ==  6); // 3
    assert(numberOfResilientFractions(10) ==  4); // 6
    assert(numberOfResilientFractions(11) == 10); // 1
    assert(numberOfResilientFractions(12) ==  4); // 8
}
void testNumberOfResilientFractions2() {
    QVector<s64> primes;
    primesToAtLeast(12, &primes);
    assert(numberOfResilientFractions2( 2, 1.0, primes) ==  1); // 1
    assert(numberOfResilientFractions2( 3, 1.0, primes) ==  2); // 1
    assert(numberOfResilientFractions2( 4, 1.0, primes) ==  2); // 2
    assert(numberOfResilientFractions2( 5, 1.0, primes) ==  4); // 1
    assert(numberOfResilientFractions2( 6, 1.0, primes) ==  2); // 4
    assert(numberOfResilientFractions2( 7, 1.0, primes) ==  6); // 1
    assert(numberOfResilientFractions2( 8, 1.0, primes) ==  4); // 4
    assert(numberOfResilientFractions2( 9, 1.0, primes) ==  6); // 3
    assert(numberOfResilientFractions2(10, 1.0, primes) ==  4); // 6
    assert(numberOfResilientFractions2(11, 1.0, primes) == 10); // 1
    assert(numberOfResilientFractions2(12, 1.0, primes) ==  4); // 8
}

//0.666667 = 2 / 3 , d: 4
//0.4 = 2 / 5 , d: 6
//0.363636 = 4 / 11 , d: 12
//0.352941 = 6 / 17 , d: 18
//0.347826 = 8 / 23 , d: 24
//0.275862 = 8 / 29 , d: 30
//0.271186 = 16 / 59 , d: 60
//0.269663 = 24 / 89 , d: 90
//0.268908 = 32 / 119 , d: 120
//0.268456 = 40 / 149 , d: 150
//0.268156 = 48 / 179 , d: 180
//0.229665 = 48 / 209 , d: 210
//0.229117 = 96 / 419 , d: 420
//0.228935 = 144 / 629 , d: 630
//0.228844 = 192 / 839 , d: 840
//0.228789 = 240 / 1049 , d: 1050
//0.228753 = 288 / 1259 , d: 1260
//0.228727 = 336 / 1469 , d: 1470
//0.228708 = 384 / 1679 , d: 1680
//0.228692 = 432 / 1889 , d: 1890
//0.22868 = 480 / 2099 , d: 2100
//0.207882 = 480 / 2309 , d: 2310
//0.207837 = 960 / 4619 , d: 4620
//0.207822 = 1440 / 6929 , d: 6930
//0.207815 = 1920 / 9239 , d: 9240
//0.20781 = 2400 / 11549 , d: 11550
//0.207807 = 2880 / 13859 , d: 13860
//0.207805 = 3360 / 16169 , d: 16170
//0.207803 = 3840 / 18479 , d: 18480
//0.207802 = 4320 / 20789 , d: 20790
//0.207801 = 4800 / 23099 , d: 23100
//0.2078 = 5280 / 25409 , d: 25410
//0.2078 = 5760 / 27719 , d: 27720
//0.191815 = 5760 / 30029 , d: 30030
//0.191811 = 11520 / 60059 , d: 60060
//0.19181 = 17280 / 90089 , d: 90090
//0.19181 = 23040 / 120119 , d: 120120
//0.191809 = 28800 / 150149 , d: 150150
//0.191809 = 34560 / 180179 , d: 180180
//0.191809 = 40320 / 210209 , d: 210210
//0.191809 = 46080 / 240239 , d: 240240
//0.191809 = 51840 / 270269 , d: 270270
//0.191809 = 57600 / 300299 , d: 300300
//0.191809 = 63360 / 330329 , d: 330330
