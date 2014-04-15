/*
    线段树    区间更新   简单

    题意：区间修改的线段树
       
    思路：用了lazy，记得在所有操作结束后来次put_all_down.
*/
#include <stdio.h>
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
int pos[MAXN];
struct Node {
    int l, r, label;
} f[MAXN * 4];

void put_down(int u)
{
    f[L(u)].label = f[R(u)].label = f[u].label;
    f[u].label = 0;
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].label = 1;
    if(l == r) {
        pos[l] = u;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}
void Update(int u, int l, int r, int change)
{
    if(f[u].label == change) return ;
    if(l == f[u].l && r == f[u].r) {
        f[u].label = change;
        return ;
    }
    if(f[u].label) {
        put_down(u);
    }
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, change);
    else if(mid < l) Update(R(u), l, r, change);
    else {
        Update(L(u), l, mid, change);
        Update(R(u), mid+1, r, change);
    }
}
void put_all_down(int u)
{
    if(f[u].l == f[u].r) return;
    if(f[u].label) {
        put_down(u);
    }
    put_all_down(L(u));
    put_all_down(R(u));
}
int main()
{
    int cases, Cas = 0, query, l, r, x, n;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);
        build(1, 1, n);
        while(query--) {
            scanf("%d%d%d", &l, &r, &x);
            Update(1, l, r, x);
        }
        put_all_down(1);
        int sum = 0;
        for(int i = 1; i <= n; i++) sum += f[pos[i]].label;
        printf("Case %d: The total value of the hook is %d.\n", ++Cas, sum);
    }
    return 0;
}
