/*
    题意：给序列{Ai}，对于每个询问(l,r)，问区间[l,r]是否满足:al<=al+1<=...<=ak>=ak+1>=...>=ar

    思路：标记+线段树    线段树是用来查找区间[l,r]的最大数
          
          很多人直接线性地做标记，没有用线段树，不知道怎么做的...题解也是这样做的。
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN        100005
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)+1)
#define     MID(x, y)   (((x)+(y))>>1)
#define     debug       printf("!\n")
struct Node {int left, right, pos, num; } f[MAXN*3];
int a[MAXN], min_L[MAXN], min_R[MAXN];
int n;

void build(int root, int left, int right)
{
    f[root].left =  left; f[root].right = right;
    if(left == right) {
        f[root].num = a[left];
        f[root].pos = left;
        return ;
    }
    int mid = MID(left, right);
    build(L(root), left, mid);
    build(R(root), mid+1, right);
    if(f[L(root)].num > f[R(root)].num) {
        f[root].num = f[L(root)].num;
        f[root].pos = f[L(root)].pos;
    } else {
        f[root].num = f[R(root)].num;
        f[root].pos = f[R(root)].pos;
    }
}
int Query(int root, int left, int right)
{
    if(left == f[root].left && f[root].right == right) return f[root].pos;
    int mid = MID(f[root].left, f[root].right);
    if(right <= mid) return Query(L(root), left, right);
    else if(mid < left) return Query(R(root), left, right);
    else {
        int tmp1 = Query(L(root), left, mid);
        int tmp2 = Query(R(root), mid+1, right);
        return a[tmp1] > a[tmp2] ? tmp1 : tmp2;
    }
}
int main()
{
    int query;
    scanf("%d%d", &n, &query);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    min_L[0] = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= a[i-1]) min_L[i] = min_L[i-1];
        else min_L[i] = i;
    }
    min_R[n+1] = n+1;
    for(int i = n; i >= 1; i--) {
        if(a[i] >= a[i+1]) min_R[i] = min_R[i+1];
        else min_R[i] = i;
    }
    while(query--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int mid = Query(1, l, r);
        if(l >= min_L[mid] && min_R[mid] >= r) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
