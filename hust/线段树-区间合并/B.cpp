/*
    区间线段树  单点更新

    题意：求区间最长连续上升子串。有单点更新值。

    思路：做了UESTC 1425 another LCIS后这道题就算水题了...
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1LL)
#define     L(x)        ((x)<<1LL)
#define     R(x)        (((x)<<1LL)|1LL)
int pos[MAXN];
struct Node {
    int l, r, l_value, r_value, l_cis, r_cis, maxl, len;
}f[MAXN << 2];

void put_up(int u)
{
    Node & a = f[u];
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    a.l_value = ll.l_value, a.r_value = rr.r_value;
    a.l_cis   = ll.l_cis  , a.r_cis   = rr.r_cis;
    a.maxl = max(ll.maxl, rr.maxl);
    
    if(ll.r_value < rr.l_value) {
        a.maxl = max(a.maxl, ll.r_cis + rr.l_cis);
        if(ll.l_cis == ll.len) a.l_cis = ll.l_cis + rr.l_cis;
        if(rr.r_cis == rr.len) a.r_cis = rr.r_cis + ll.r_cis;
    }
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].len = r - l + 1;
    if(l == r) {
        scanf("%d",  &f[u].r_value);
        f[u].l_value = f[u].r_value;
        f[u].l_cis = f[u].r_cis = f[u].maxl = 1;
        pos[l] = u;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
    put_up(u);
}
void Update(int u, int x)
{
    f[u].l_value = f[u].r_value = x;
    u >>= 1;
    while(u) {
       put_up(u); 
       u >>= 1;
    }
}
int Query(int u, int l, int r)
{
    if(l == f[u].l && f[u].r == r) return f[u].maxl;
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) return Query(L(u), l, r);
    else if(mid < l) return Query(R(u), l, r);
    else {
        int ans = max(Query(L(u), l, mid), Query(R(u), mid+1, r));
        Node & ll = f[L(u)];
        Node & rr = f[R(u)];
        if(ll.r_value < rr.l_value) 
            ans = max(ans, ll.r + 1 - max(l, ll.r - ll.r_cis+1)  +  min(r, rr.l + rr.l_cis - 1) + 1 - rr.l);
        return ans;
    }
}
int main()
{
    int cases, query, n, l, r;
    char op[10];
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);
        build(1, 0, n-1);
        while(query--) {
            scanf("%s%d%d", op, &l, &r);
            if(op[0] == 'Q') printf("%d\n", Query(1, l, r));
            else Update(pos[l], r);
        }
    }
    return 0;
}
