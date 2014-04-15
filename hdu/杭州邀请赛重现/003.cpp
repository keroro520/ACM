#include <stdio.h>
#include <string.h>
#define     debug       printf("!\n")
#define     MOD2        (10007)
#define     MOD         (10007LL)
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

struct Node {
    int l, r, add, mul, chg;
    long long p[3];
} f[MAXN << 2];

void Update(int u, int l, int r, int value, int op);
void put_self(int u, int value, int op)
{
    if(op == 1) {
        f[u].p[2] = (f[u].p[2]%MOD + 3*value*f[u].p[1] % MOD + 3*value*value*f[u].p[0] % MOD + value*value*value%MOD*(f[u].r - f[u].l + 1)%MOD) % MOD;
        f[u].p[1] = (f[u].p[1] + value*value*(f[u].r - f[u].l + 1) + 2*value*f[u].p[0]) % MOD;
        f[u].p[0] = (f[u].p[0] + value * (f[u].r - f[u].l + 1)) % MOD;
    } else if(op == 2) {
        f[u].p[0] = (f[u].p[0] * value) % MOD;
        f[u].p[1] = (f[u].p[1] * value*value) % MOD;
        f[u].p[2] = (f[u].p[2]%MOD * (value*value*value%MOD)) % MOD;
    } else if(op == 3) {
        f[u].p[0] = value * (f[u].r - f[u].l + 1) % MOD;
        f[u].p[1] = value*f[u].p[0] % MOD;
        f[u].p[2] = value*f[u].p[1] % MOD;
    }
}
void put_lazy(int u, int value, int op)
{
    if(op == 1) f[u].add = (value+f[u].add) % MOD2;
    else if(op == 2) f[u].add = f[u].add * value % MOD2, f[u].mul = value * f[u].mul % MOD2;
    else if(op == 3) f[u].add = 0, f[u].mul = 1, f[u].chg = value % MOD2;
}
void put_down(int u)
{
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    Node & a  = f[u];
    if(a.chg != -1) Update(L(u), ll.l, ll.r, a.chg, 3), Update(R(u), rr.l, rr.r, a.chg, 3);
    if(a.mul !=  1) Update(L(u), ll.l, ll.r, a.mul, 2), Update(R(u), rr.l, rr.r, a.mul, 2);
    if(a.add !=  0) Update(L(u), ll.l, ll.r, a.add, 1), Update(R(u), rr.l, rr.r, a.add, 1);
    a.chg = -1, a.mul = 1, a.add = 0;
}
void put_up(int u)
{
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    Node & a  = f[u];
    for(int i = 0; i < 3; i++) a.p[i] = (ll.p[i] + rr.p[i]) % MOD;
}
void Update(int u, int l, int r, int value, int op) 
{
    if(f[u].l == l && r == f[u].r) {
        put_lazy(u, value, op);
        put_self(u, value, op);
        return ;
    }
    put_down(u);
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, value, op);
    else if(mid < l) Update(R(u), l, r, value, op);
    else Update(L(u), l, mid, value, op), Update(R(u), mid+1, r, value, op);
    put_up(u);
}
long long Query(int u, int l, int r, int value)
{
    if(l == f[u].l && f[u].r == r) return f[u].p[value];
    put_down(u);
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) return Query(L(u), l, r, value);
    else if(mid < l) return Query(R(u), l, r, value);
    else return (Query(L(u), l, mid, value) + Query(R(u), mid+1, r, value)) % MOD;
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].add = 0, f[u].mul = 1, f[u].chg = -1;
    if(l == r) {
        memset(f[u].p, 0, sizeof(long long)*3);
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}

int main()
{
    int query, op, l, r, value, n;
    while(scanf("%d%d", &n, &query) , n + query) {
        build(1, 1, n);
        while(query--) {
            scanf("%d%d%d%d", &op, &l, &r, &value);
            if(op != 4) {
                Update(1, l, r, value, op);           //1+  2* 3change
            } else {
                printf("%I64d\n", Query(1, l, r, value-1) % MOD);;
            }
        }
    }
    return 0;
}
