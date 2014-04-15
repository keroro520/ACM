/*
    区间线段树  简单题

    题意：区间求和线段树，操作是增加区间元素值和询问区间和。

    思路：用了lazy
          除了lazy标记外，因为操作里面有询问区间和，而区间和在每次Update的时候是可以直接算出来的，所以不用每次Query的时候都递归递到底。
*/
#include <stdio.h>
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1LL)
#define     L(x)        ((x)<<1LL)
#define     R(x)        (((x)<<1LL)|1LL)

struct Node {
    int l, r;
    long long add, sum;
} f[MAXN * 4];
int Index = 1;
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].add = 0;
    if(l == r) {
        scanf("%I64d", &f[u].sum);
        return ;
    }
    int mid = MID(l,r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
    f[u].sum = f[L(u)].sum + f[R(u)].sum;
}
void Update(int u, int l, int r, int add)
{
    f[u].sum += add * (r - l + 1);                  //label标记，区间sum可以直接计算出来，这样Query的时候就不用每次都递到底了
    if(l == f[u].l && f[u].r == r) {
        f[u].add += add;
        return ;
    }   //跟上一题不一样，这里不用put_down
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, add);
    else if(mid < l) Update(R(u), l, r, add);
    else {
        Update(L(u), l, mid, add);
        Update(R(u), mid+1, r, add);
    }
}
void put_down(int u)
{
    int ll = L(u), rr = R(u);
    f[ll].sum += f[u].add * (f[ll].r - f[ll].l + 1);
    f[ll].add += f[u].add;
    f[rr].sum += f[u].add * (f[rr].r - f[rr].l + 1);
    f[rr].add += f[u].add;
    f[u].add  =  0;
}
long long Query(int u, int l, int r)
{
    if(l == f[u].l && f[u].r == r) return f[u].sum;
    if(f[u].add) {
        put_down(u);
    }
    int mid = MID(f[u].l , f[u].r);
    if(r <= mid) return Query(L(u), l, r);
    else if(mid < l) return Query(R(u), l, r);
    else return Query(L(u), l, mid) + Query(R(u), mid+1, r);
}
int main()
{
    int n, query, l, r, x;
    char op[2];
    scanf("%d%d", &n, &query);
    build(1, 1, n);
    while(query--) {
        scanf("%s %d%d", op, &l, &r);
        if(op[0] == 'Q') {
            printf("%I64d\n", Query(1, l, r));
        } else {
            scanf("%d", &x);
            Update(1, l, r, x);
        }
    }
    return 0;
}
