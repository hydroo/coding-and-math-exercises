#include "../lib.hpp"

struct Line {
    mpf_class m; // slope
    mpf_class n; // y-offset
};

QDebug operator<<(QDebug d, const Line& l) {
    d.nospace();
    d.noquote();
    stringstream s;
    s << l.m << "x + " << l.n;
    d << QString::fromStdString(s.str());
    return d.resetFormat();
}

struct Point {
    mpf_class x, y;
    bool  operator==(const Point& rhs   ) const { return x == rhs.x && y == rhs.y; }
    Point operator* (const mpf_class& f ) const { return Point{f*x, f*y};          }
    Point operator+ (const Point& rhs   ) const { return Point{x+rhs.x, y+rhs.y};  }
    Point operator- (                   ) const { return Point{-x, -y};            }
    Point operator- (const Point& rhs   ) const { return *this + -rhs;             }
    bool  operator<=(const mpf_class& f ) const { return x <= f && y <= f;         }
    bool  operator> (const mpf_class& f ) const { return ! (*this <= f);           }
};

QDebug operator<<(QDebug d, const Point& f) {
    d.nospace();
    d.noquote();
    stringstream s;
    s << "(" << f.x << ", " << f.y << ")";
    d << QString::fromStdString(s.str());
    return d.resetFormat();
}

void solveQuadraticEquation(const mpf_class& p, const mpf_class& q, mpf_class* x1, mpf_class* x2, bool* realResult) {

    *x1 = p * -1 / 2;
    *x2 = *x1;

    mpf_class p22mq = p*p / 4 - q;


    if (p22mq > 0) {
        *realResult = true;
    } else {
        *realResult = false;
        return;
    }

    mpf_class s;
    mpf_sqrt(s.get_mpf_t(), p22mq.get_mpf_t());

    *x1 += s;
    *x2 -= s;
}


void intersectLineWithEllipse(const Line& line, Point* p1, Point* p2) {
    mpf_class p, q;

    const auto& m = line.m;
    const auto& n = line.n;

    p = 2*m*n / (4 + m*m);
    q = (n*n - 100) / (4 + m*m);

    mpf_class x1, x2;
    bool real;
    solveQuadraticEquation(p, q, &x1, &x2, &real);

    if (real == false) {
        qDebug() << "bad: solution to quadratic equation is not real";
        return;
    }

    //qDebug() << line << ", p:"<< p << ", q:"<< q << ", x1: " << x1 << ", x2: " << x2;

    p1->x = x1;
    p1->y = m*x1 + n;
    p2->x = x2;
    p2->y = m*x2 + n;
}

Point intersectLines(const Line& l1, const Line l2) {
    Point ret;
    ret.x = (l2.n - l1.n) / (l1.m - l2.m);
    ret.y = l1.m * ret.x + l1.n;
    return ret;
}

mpf_class /*slope*/ mirror(const mpf_class& m1 /*tangent slope*/, const mpf_class& m2 /*line slope*/) {

    Point p1{1, m2};
    //qDebug() << "p1:" << p1;

    /* get line orthogonal to m1, starting in p1 */
    mpf_class om1 = -1/m1;
    mpf_class on1 = p1.y + (0-p1.x)*om1;
    Line ol1{om1, on1};
    //qDebug() << "ol1:" << ol1;

    /* intersect ol1 with m1 to get p2, and goto p3 on the target line */
    auto p2 = intersectLines(Line{m1, 0}, ol1);
    //qDebug() << "p2:" << p2;
    auto p3 = p2 - (p1 - p2);
    //qDebug() << "p3:" << p3;

    /* return p3's slope from 0,0 */

    //qDebug() << "mirrored slope:" << p3.y / p3.x;

    return p3.y / p3.x;
}

/* note: 'from' is used to rule out the wrong of the two solutions from the intersection with the ellipse */
void reflect(const Line& lIn, const Point& from, Line* l, Point* p_) {

    Point p, p1, p2;
    intersectLineWithEllipse(lIn, &p1, &p2);

    if (p1 - from <= 0.0001) {
        p = p2;
    } else {
        if (p2 - from > 0.0001) {
            qDebug() << "bad, from doesn't match neither p1 nor p2. from:" << from << ", p1:" << p1 << ", p2:" << p2;
        }
        p = p1;
    }

    mpf_class m = mirror(-4*p.x/p.y /*ellipse tangent slope*/, lIn.m);
    mpf_class n = p.y + (0 - p.x)* m;

    *l = Line{m ,n};
    *p_ = p;
}

void testSolveQuadraticEquation();
void testIntersectLineWithEllipse();
void testIntersectLines();
void testMirror();
void testReflect();
void test1();
void doIt();

int main() {
    testSolveQuadraticEquation();
    testIntersectLineWithEllipse();
    testIntersectLines();
    testMirror();
    testReflect();
    test1();

    doIt();

    return 0;
}

void doIt() {
    Line l[2];
    Point p[2];
    int i = 0;

    l[0] = {-(10.1 + 9.6) / 1.4, 10.1};
    p[0] = Point{0.00710732, 9.99999};

    while(true) {

        const auto& li = l[i%2];
        const auto& pi = p[i%2];

        auto& lo = l[(i+1)%2];
        auto& po = p[(i+1)%2];

        reflect(li, pi, &lo, &po);

        qDebug() << i << po;

        if (po.x >= -0.01 && po.x <= 0.01 && po.y >= 0) {
            break;
        }

        i += 1;
    }

    qDebug() << i << p[(i+1)%2] << "!!!!!!!!";
}

void test1() {
    Line l1 = {-(10.1 + 9.6) / 1.4, 10.1};

    Line l2;
    Point p2;
    reflect(l1, Point{0.00710732, 9.99999}, &l2, &p2);
    //qDebug() << p2 << "," << l2;

    Line l3;
    Point p3;
    reflect(l2, p2, &l3, &p3);
    //qDebug() << p3 << "," << l3;

    Line l4;
    Point p4;
    reflect(l3, p3, &l4, &p4);
    //qDebug() << p4 << "," << l4;

    //qDebug() << "paste into Wolfram alpha: 4x^2 + y^2 = 100, " << l1 << " = y, " << l2 << " = y, " << l3 << " = y, " << l4 << " = y";
}

void testSolveQuadraticEquation() {
    mpf_class x1, x2;
    bool real;

    solveQuadraticEquation(2, 2, &x1, &x2, &real);
    assert(real == false);

    solveQuadraticEquation(2, 0, &x1, &x2, &real);
    assert(x1 ==  0);
    assert(x2 == -2);
    assert(real == true);
}

void testIntersectLineWithEllipse() {
    Point p1, p2;

    Line l1 = {-(10.1 + 9.6) / 1.4, 10.1};
    intersectLineWithEllipse(l1, &p1, &p2);
    assert(abs(p1.x - 1.4) <= 0.001 && abs(p1.y - -9.6) <= 0.001);
}

void testIntersectLines() {
    Line l1 = {0, 0};
    Line l2 = {1, 0};
    Line l3 = {-1, 1};

    Point p1 = intersectLines(l1, l2);
    assert((p1 == Point{0,0}));
    Point p2 = intersectLines(l1, l3);
    assert((p2 == Point{1,0}));
    Point p3 = intersectLines(l2, l3);
    assert((p3 == Point{0.5, 0.5}));
}

void testMirror() {
    mpf_class m, m1, m2;

    m1 = 0.00001;
    m2 = -1;
    m  = mirror(m1, m2);
    //qDebug() << m;
    assert(abs(m - 1) <= 0.0001);

    m1 = 0.00001;
    m2 = 1;
    m  = mirror(m1, m2);
    //qDebug() << m;
    assert(abs(m + 1) <= 0.0001);

    m1 = 1000000;
    m2 = 1;
    m  = mirror(m1, m2);
    //qDebug() << m;
    assert(abs(m + 1) <= 0.0001);

    m1 = 1000000;
    m2 = -1;
    m  = mirror(m1, m2);
    //qDebug() << m;
    assert(abs(m - 1) <= 0.0001);

    m1 = 1;
    m2 = 0.5;
    m  = mirror(m1, m2);
    //qDebug() << m;
    assert(abs(m - 2) <= 0.0001);
}

void testReflect() {

    Line l1{0.0000001, 0};
    Point p1{-5, 0};

    Line l2;
    Point p2;

    reflect(l1, p1, &l2, &p2);
    assert(abs(l2.m) <= 0.00001 && abs(l2.n) <= 0.00001);
    assert(l2.m <= 0 && l2.n > 0); // look for wrong +-
    assert(abs(p2.x - 5) <= 0.00001 && abs(p2.y - 0) <= 0.00001);
    assert(p2.y > 0); // look for correct +-

    Line l3, l4;
    Point p3, p4;

    reflect(l2, p2, &l3, &p3);
    reflect(l3, p3, &l4, &p4);

    assert(abs(l4.m) <= 0.00001 && abs(l4.n) <= 0.00001);
    assert(abs(p4.x - 5) <= 0.00001 && abs(p4.y - 0) <= 0.00001);
}
