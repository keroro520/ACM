/*
    线段树  离散化  

    题意:在墙上贴海报,海报可以互相覆盖,问最后可以看见几张海报

    

    // * 贴思路 * //
    思路 :  这题数据范围很大,直接搞超时+超内存,需要离散化:
            离散化简单的来说就是只取我们需要的值来用,比如说区间[1000,2000],[1990,2012] 我们用不到[-∞,999][1001,1989][1991,1999][2001,2011][2013,+∞]这些值,所以我只需要1000,1990,2000,2012就够了,将其分别映射到0,1,2,3,在于复杂度就大大的降下来了
            所以离散化要保存所有需要用到的值,排序后,分别映射到1~n,这样复杂度就会小很多很多

        而这题的难点在于每个数字其实表示的是一个单位长度(并非一个点),这样普通的离散化会造成许多错误(包括我以前的代码,poj这题数据奇弱)
        给出下面两个简单的例子应该能体现普通离散化的缺陷:
        例子一:1-10 1-4 5-10
        例子二:1-10 1-4 6-10
        普通离散化后都变成了[1,4][1,2][3,4]
        线段2覆盖了[1,2],线段3覆盖了[3,4],那么线段1是否被完全覆盖掉了呢?
        例子一是完全被覆盖掉了,而例子二没有被覆盖
        为了解决这种缺陷,我们可以在排序后的数组上加些处理,比如说[1,2,6,10]
        如果相邻数字间距大于1的话,在其中加上任意一个数字,比如加成[1,2,3,6,7,10],然后再做线段树就好了.    关于这一点我因为没有考虑好而RE了一次
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        20005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

struct Node {
    int l, r, label;
} f[MAXN * 6];
int pos[MAXN*2];
int post[MAXN][2];
int map[10000005];
int p[MAXN * 2*2];
bool boo[MAXN * 2*2];

void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].label = -1;
    if(l == r) {
        pos[l] = u;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}

void put_down(int u)
{
    f[L(u)].label = f[R(u)].label = f[u].label;
    f[u].label = -1;
}
void Update(int u, int l, int r, int color)
{
    if(l == f[u].l && f[u].r == r) {
        f[u].label = color;
        return ;
    }
    if(f[u].label != -1) put_down(u);
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, color);
    else if(mid < l) Update(R(u), l, r, color);
    else {
        Update(L(u), l, mid, color);
        Update(R(u), mid+1, r, color);
    }
}
void put_all_down(int u)
{
    if(f[u].l == f[u].r) {
        return ;
    }
    if(f[u].label != -1) put_down(u);
    put_all_down(L(u));
    put_all_down(R(u));
}
int main()
{
    int cases, n;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        int top = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &post[i][0], &post[i][1]);
            p[top++] = post[i][0];
            p[top++] = post[i][1];
        }
        sort(p, p+top);
        map[p[0]] = 0;
        int Index = 1;
        for(int i = 1; i < top; i++) 
            if(p[i] == p[i-1]) continue;
            else if(p[i] == p[i-1]+1) map[p[i]] = Index++;
            else map[p[i]-1] = Index++, map[p[i]] = Index++;
        build(1, 0, Index-1);
        for(int i = 0; i < n; i++) Update(1, map[post[i][0]], map[post[i][1]], i);
        put_all_down(1);
        memset(boo, false, sizeof(bool) * (n+1));
        int ans = 0;
        for(int i = 0; i < Index; i++) 
            if(f[pos[i]].label != -1 && !boo[f[pos[i]].label]) {
                boo[f[pos[i]].label] = true;
                ans++;
            }
        printf("%d\n", ans);
    }
    return 0;
}
