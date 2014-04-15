/*  
    线段树求逆序数   求小逆序数   神奇

    题意：给定一个序列，对该序列的n种排列（排列如下）的每种排列(0 ~ n-1)的逆序数求最小值：
       a1, a2, ..., an-1, an  
       a2, a3, ..., an, a1  
       a3, a4, ..., an, a1, a2  
       ...  
       an, a1, a2, ..., an-1


    思路：先求出初始序列的逆序数，可以归并，这里用的是线段数求。
          设当前逆序数为sum，则每次把第一个数x移到最后，则新序列的逆序数 = sum - x + (n - 1 - x)

          sum = sum - a[i] + (n - 1 - a[i]);      //太神奇了，这个转移方程.

          
          前面部分用线段树求初始逆序简单说一下，就是先建一棵树，每个节点[l,r]保存一个sum值，表示到目前为止[l,r]出现的个数。如当前序列为1,3, 则节点[0,3].sum = 2, [0, 4].sum = 2。然后每次扫到一个新的数x都先询问旧序列中[x+1, n-1]中出现的个数...

          *** 逐个插入值（即输入的一个值）；  在每插入一个值后就更新包含该区间的所有的数的个数（加一）***
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        5005
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
#define     MID(x, y)   (((x)+(y))>>1)
int a[MAXN], pos[MAXN], high[MAXN];
struct Node {
    int l, r, sum;
} f[MAXN * 3];
int n;
void Update(int root)
{
    if(root == 0) return ;
    f[root].sum++;
    Update(root >> 1);
}
int Query(int root, int l, int r)
{
    if(l <= f[root].l && f[root].r <= r) {
        return f[root].sum;
    }
    int mid = MID(f[root].l, f[root].r);
    if(r <= mid) return Query(L(root), l, r);
    else if(mid < l) return Query(R(root), l, r);
    else return Query(L(root), l, mid) + Query(R(root), mid+1, r);
}
void build(int root, int l, int r)
{
    f[root].l = l, f[root].r = r, f[root].sum = 0;
    if(l == r) {
        pos[l] = root;
        return ;
    }
    int mid = MID(l, r);
    build(L(root), l, mid);
    build(R(root), mid+1, r);
}

int main()
{
    int x;
    while(scanf("%d", &n) != EOF) {
        build(1, 0, n-1);
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            a[i] = x;
            high[x] = Query(1, x, n-1);
            Update(pos[x]);
        }
        int sum = 0;
        for(int i = 0; i < n; i++) sum += high[i];
        int ans = sum;
        for(int i = 0; i < n; i++) {
            sum = sum - a[i] + (n - 1 - a[i]);      //太神奇了，这个转移方程.
            ans = min(ans, sum);
        }
        printf("%d\n", ans);
    }
}
