/*
    线段树 水题
*/
//lightoj 1080
#include <stdio.h>
#include <string.h>
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
struct Node {
    int l, r, label, add;
} f[MAXN << 2];
char s[MAXN];

inline char rdc() { scanf(" "); return getchar(); }
void put_down(int u)
{
    if(!f[u].add) return ;
    f[L(u)].add ^= 1;
    f[R(u)].add ^= 1;
    f[u].add = 0;
}
void Update(int u, int l, int r)
{
    if(f[u].l == l && r == f[u].r) {
        f[u].add ^= 1;
        return ;
    }
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r);
    else if(mid < l) Update(R(u), l, r);
    else Update(L(u), l, mid), Update(R(u), mid+1, r);
}
int Query(int u, int pos)
{
    if(f[u].l == pos && pos == f[u].r) {
        if(f[u].add) f[u].label ^= 1, f[u].add = 0;
        return f[u].label;
    }
    if(f[u].add) put_down(u);
    int mid = MID(f[u].l, f[u].r);
    return pos <= mid ? Query(L(u), pos) : Query(R(u), pos);
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].add = 0;
    if(l == r) {
        f[u].label = s[l] - '0' ;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}
int main()
{
    int cases, Cas = 0, query, x, y;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%s", s);
        int n = strlen(s);
        build(1, 0, n-1);
        scanf("%d", &query);
        printf("Case %d:\n", ++Cas);
        while(query--) {
            char op = rdc();
            if(op == 'Q') scanf("%d", &x), printf("%d\n", Query(1, x-1));
            else scanf("%d%d", &x, &y), Update(1, x-1, y-1);
        }
    }
    return 0;
}
