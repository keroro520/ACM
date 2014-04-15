/*
    线段树  约瑟夫环问题  好题  反素数

    题意：N个孩子顺时针坐成一个圆圈且从1到N编号，每个孩子手中有一张标有非零整数的卡片。第K个孩子先出圈，如果他手中卡片上的数字A大于零，下一个出圈的是他左手边第A个孩子。否则，下一个出圈的是他右手边第(-A)个孩子。第p个出圈的孩子会得到F(p)个糖果，F(p)为p的因子数。求得到糖果数最多的是哪个孩子及得到多少糖果。
    

    思路：至今仍不知道下面这个公式是怎么推出来的... 
            if(a[index] > 0) pos = (pos - 1 + a[index] - 1) % n + 1;
            else pos = ((pos - 1 + a[index]) % n + n) % n + 1;

          线段树方面跟上题一样。
    http://blog.csdn.net/ahfywff/article/details/7222193
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        500005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

int su[37]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,  
           55440,83160,110880,166320,221760,277200,332640,498960,500001};  
int yinzi[37]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200,1314521};  
struct Node {
    int l, r, sum;
} f[MAXN * 3];
int a[MAXN];
char name[MAXN][11];
int ans , n;
int fansushu(int n)
{
    for(int i = 0; ; i++) if(su[i] > n) {
        ans = yinzi[i-1];
        return su[i-1];
    }
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].sum = r - l + 1;
    if(l == r) return ;
    build(L(u), l, MID(l,r));
    build(R(u), MID(l,r)+1, r);
}
int Query(int root, int num)
{
    f[root].sum--;
    if(f[root].l == f[root].r) {
        return f[root].l;
    }
    if(f[L(root)].sum >= num) Query(L(root), num);
    else Query(R(root), num - f[L(root)].sum);
}
int main()
{
    int K;
    while(scanf("%d%d", &n, &K) != EOF) {
        for(int i = 1; i <= n; i++) scanf("%s%d", name[i], a+i);
        int p = fansushu(n);
        build(1, 1, n);
        int pos = K;    /* 当前环中第pos个孩子 */
        int index ;     /* idx为当前出去的孩子的原始位置 */   
        while(p--) {
            index = Query(1, pos);
            n--;        //不先抹消k的位置吗？  ---在Query里面做了
            if(n == 0) break;
            if(a[index] > 0) pos = (pos - 1 + a[index] - 1) % n + 1;
            else pos = ((pos - 1 + a[index]) % n + n) % n + 1;
        }
        printf("%s %d\n", name[index], ans);
    }
    return 0;
}

