/*
    区间线段树  单点修改
    题意：0/1序列，单点修改，Q x 问x代表的点所在的最长"1"序列的长度。 

    思路：图方便，用ok[x]表示x点是否为0
          Seg_tree_Node {
            int l, r,;
            int l_value, r_value;
            int ls, rs;     //以u.l点为起点的"1"序列的终点位置；以u.r为终点的"1"序列的起点位置.
          }

    题目描述坑，看了Discuss后改了一下就A了.
*/
#include <stdio.h>
#define     debug       printf("!\n")
#define     MAXN        50005 
#define     MID(x, y)   (((x)+(y)) >> 1LL)
#define     L(x)        ((x)<<1LL)
#define     R(x)        (((x)<<1LL)|1LL)

struct Node {
    int l, r, ls, rs, l_value, r_value;
} f[MAXN << 2];
int pos[MAXN];
bool ok[MAXN];
int S[MAXN];

void put_up(int u)
{
    Node & a = f[u];
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    a.l_value = ll.l_value, a.r_value = rr.r_value;
    if(ll.ls == ll.r && rr.l_value == 1) a.ls = rr.ls;
    else a.ls = ll.ls;
    if(rr.rs == rr.l && ll.r_value == 1) a.rs = ll.rs;
    else a.rs = rr.rs;
}
void Update(int u, int add)
{
    f[u].l_value = f[u].r_value = (add == 1);
    if(add == 1) f[u].ls = f[u].r, f[u].rs = f[u].l;
    else f[u].ls = f[u].l - 1, f[u].rs = f[u].r + 1;
    u >>= 1;
    while(u) {
        put_up(u);
        u >>= 1;
    }
}
int Query(int u, int pos)
{
    if(f[u].ls == f[u].r) return f[u].r - f[u].l + 1;
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    if(ll.r_value == 1 && rr.l_value == 1 && ll.rs <= pos && pos <= rr.ls) return rr.ls - ll.rs + 1;
    else if(pos <= MID(f[u].l, f[u].r)) return Query(L(u), pos);
    else return Query(R(u), pos);
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r;
    if(l == r) {
        pos[l] = u;
        f[u].l_value = f[u].r_value = 1;
        f[u].ls = f[u].rs = l;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
    put_up(u);
}
void solve(int n, int query)
{
    int x;
    char op[3];
    for(int i = 1; i <= n; i++) ok[i] = true;
    build(1, 1, n);
    int top = 0;
    while(query--) {
        scanf("%s", op);
        if(op[0] == 'D') {
            scanf("%d", &x);
            Update(pos[x], 0);
            ok[x] = false;
            S[top++] = x;
        } else if(op[0] == 'R') {
            while(top > 0) {
                x = S[--top];
                if(!ok[x]) break;
            }
            if(top == 0 && ok[x]) continue;
            Update(pos[x], 1);
            ok[x] = true;
        } else {
            scanf("%d", &x);
            if(!ok[x]) printf("0\n");
            else printf("%d\n", Query(1, x));
        }
    }
}
int main()
{
    int query, n;
    while( scanf("%d%d", &n, &query) != EOF) solve(n, query);
    return 0;
}
