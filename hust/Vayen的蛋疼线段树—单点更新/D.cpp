/*
    简单线段树      

    描述：板子h*w上贴1*w0的广告，从左上角贴起，询问广告所在的row。每个广告height都为1

    思路：将h分段，结构中增加w域，保存区间[a,b]所以行剩余可贴的最大量。
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN        200000
#define     MID(x,y)    (((x)+(y))>>1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
#define     debug       printf("!\n")
struct Node {
    int l, r, rest;
} f[MAXN * 3];
int H, W;

int Query_and_Update(int root, int w)
{
    if(f[root].l == f[root].r) {
        f[root].rest -= w;
        return f[root].l;
    }
    int result ;
    if(f[L(root)].rest >= w) result = Query_and_Update(L(root), w);
    else result = Query_and_Update(R(root), w);
    f[root].rest = max(f[L(root)].rest, f[R(root)].rest);
    return result;
}
void build(int u, int l, int r)
{
    f[u].l = l , f[u].r = r , f[u].rest = W;
    if(l == r) return ;
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}
int main()
{
    int n,w;
    while(scanf("%d%d%d", &H, &W, &n) != EOF) {
        build(1, 1, min(n, H));
        while(n--) {
            scanf("%d", &w);
            if(f[1].rest < w) printf("-1\n");
            else printf("%d\n", Query_and_Update(1, w));
        }
    }
    return 0;
}
