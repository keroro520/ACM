/*
    线段树      好题  好巧妙

    题意：人们按顺序来排队或插队，按顺序给出每个人要插入的位置p，即当前者要在队列里第p个人后面；还有每个人的编号。输出最后的队列的编号序列。

    思路：记得以前做过一遍了，可是现在再自己做一遍还是不会。太弱了...
          就不分析了。建一棵空树，每个节点保存该区间的空位。从后往前插入，p[i]的意义就变成“第i个人站的位置前面要有p[i]个空位”

*/
#include <stdio.h>
#define     MAXN    200005
#define     debug       printf("!\n")
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
int n, pos[MAXN], a[MAXN], b[MAXN],y;
struct Node {
    int l,r,num,rest;
} f[MAXN * 4];
void Update(int u, int x)
{
    f[u].rest--;
    if(f[u].l == f[u].r) {
        f[u].num = y;
        return ;
    }
    if(f[L(u)].rest > x) Update(L(u), x);
    else Update(R(u), x - f[L(u)].rest);
}

void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r;
    f[u].rest = r - l + 1;
    if(l == r) {
        pos[l] = u;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}
int main()
{
    int x;
    while(scanf("%d", &n) != EOF) {
        build(1, 1, n);
        for(int i = 0; i < n; i++) scanf("%d%d", &a[i], &b[i]);
        for(int i = n-1; i >= 0; i--) {
            x = a[i], y = b[i];
            Update(1, x);
        }
        for(int i = 1; i <= n; i++) printf("%d%c", f[pos[i]].num, i == n ? '\n' : ' ');
    }
    return 0;
}

