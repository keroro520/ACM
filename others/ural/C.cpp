#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h> 
using namespace std;
#define     eps     1e-6
#define     MAXN    500
int n, m;
struct Point { double x, y; } statue[MAXN];
struct Line  { Point p1, p2;} e[MAXN];
int  father[MAXN];
vector<int> pass_by;

bool zero(double x) {
    return fabs(x) < eps;
}
double xmult(Point &p1, Point &p2, Point &p0) {
    return (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y);
}
bool on_road(Point &p, Point &l1, Point l2) {
    return zero(xmult(p, l1, l2)) && (l1.x-p.x)*(l2.x-p.x) < eps && (l1.y-p.y)*(l2.y-p.y) < eps;
}
double multi(Point &p0, Point &p1, Point &p2) {
    return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}
bool same(Point &a, Point &b) {
    return zero(a.x - b.x) && zero(a.y - b.y);
}
int dot_online_in
bool inter(Point &s1, Point &e1, Point &s2, Point &e2)
{
    if(!dots_inline(s1,e1,s2) || !dots_inline(s1,e1,e2))
        return same_side(s1,e1,s2,e2) && same_side(s2,e2,s1,e1);
    return dot_online_in(s1,e1,s2) ||
           dot_online_in(e1,s2,e2) ||
           dot_online_in(s2,s1,e1) ||
           dot_online_in(e2,s1,e2) ;
}
int find(int x) { return x == father[x] ? x : father[x] = find(father[x]); }
void Union(int x, int y) 
{
    int fx = find(x), fy = find(y);
    father[fx] = fy;
}
int main()
{
    int s,t;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%lf%lf", &statue[i].x, &statue[i].y);
    }
    
    if(n == 1) { printf("YES"); return 0;}
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &s, &t);
        e[i].p1 = statue[s-1];
        e[i].p2 = statue[t-1];
    }
    bool flag;
    for(int i = 0; i < n; i++) {
        flag = false;
        for(int j = 0; j < m && !flag; j++) flag = on_road(statue[i], e[j].p1, e[j].p2);
        if(!flag) break;
    }
    if(!flag) { printf("NO"); return 0;}

    for(int i = 0; i < m; i++) father[i] = i;
    for(int i = 0; i < m; i++) 
        for(int j = i+1; j < m; j++) 
            if(inter(e[i].p1, e[i].p2, e[j].p1, e[j].p2)) {
                printf("!! %d  %d\n", i, j);
                Union(i, j);
            }
    int root = find(0);
    flag = true;
    for(int i = 1; i < m && flag; i++) if(root != find(i)) flag = false;
    printf(flag ? "YES" : "NO");
    return 0;
}
