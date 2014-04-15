#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
struct point {
    double x, y;
    point(double a, double b) : x(a), y(b) { }
    point() { }
    double magsqr() const { return x * x + y * y; }
    double mag() const { return sqrt(magsqr()); }
    point operator-(const point &p) const {
        return point(x - p.x, y - p.y);
    }
    point operator*(double k) const {
        return point(x * k, y * k);
    }
    point operator/(double k) const {
        return point(x / k, y / k);
    }
};
 
struct line {
    point a, b;
    line() { }
    line(const point &x, const point &y) : a(x), b(y) { }
    point vec() const { return b - a; }
};
 
const double eps = 1e-8;
 
inline int sgn(double a) {
    return a > eps ? 1 : a < -eps ? -1 : 0;
}
 
inline double cross(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}
 
inline point inpll(const line &a, const line &b) {
    double u = cross(a.vec(), point(b.b - a.b));
    double v = cross(a.vec(), point(b.a - a.b));
    return (b.b * v - b.a * u) / (v - u);
}
 
struct pinfo { point p; int i; };
 
line ho, pr, ob;
size_t n;
vector<pinfo> pfs;
 
inline void fixpoint(point &p) {
    if (p.x > pr.b.x) p.x = pr.b.x;
    if (p.x < pr.a.x) p.x = pr.a.x;
}
 
bool lessthanpfs(const pinfo &a, const pinfo &b) {
    return a.p.x < b.p.x;
}
 
inline bool test()
{
    cin >> ho.a.x >> ho.b.x >> ho.a.y; ho.b.y = ho.a.y;
    if (ho.a.x == 0.0 && ho.b.x == 0.0 && ho.a.y == 0.0)
        return false;
    cin >> pr.a.x >> pr.b.x >> pr.a.y; pr.b.y = pr.a.y;
    cin >> n; size_t i; pfs.clear(); pinfo pf;
    for (i = 0; i < n; ++i) {
        cin >> ob.a.x >> ob.b.x >> ob.a.y; ob.b.y = ob.a.y;
        if (sgn(ob.a.y - ho.a.y) >= 0) continue;
        if (sgn(ob.a.y - pr.a.y) <= 0) continue;
        point ptl = inpll(pr, line(ho.b, ob.a));
        point ptr = inpll(pr, line(ho.a, ob.b));
        fixpoint(ptl); fixpoint(ptr);
        pf.p = ptl; pf.i = 1; pfs.push_back(pf);
        pf.p = ptr; pf.i = -1; pfs.push_back(pf);
    }
    pf.p = pr.b; pf.i = 1; pfs.push_back(pf);
    sort(pfs.begin(), pfs.end(), lessthanpfs);
 
    int fl = 0; double mx = 0.0, cu = pr.a.x, t;
    for (size_t i = 0; i < pfs.size(); ++i) {
		printf("(%.2f %.2f %d)\n", pfs[i].p.x, pfs[i].p.y, pfs[i].i);
        if (fl > 0 && fl + pfs[i].i == 0) {
            cu = pfs[i].p.x;
        } else if (fl == 0) {
            t = pfs[i].p.x - cu;
            mx = max(mx, t);
        }
        fl += pfs[i].i;
    }
 
    if (!sgn(mx)) cout << "No View" << endl;
    else printf("%0.2fn", mx);
    return true;
}
 
int main(int, char *[]) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    while (test());
    return EXIT_SUCCESS;
}
