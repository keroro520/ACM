/*
    并查集  好题

    题意 : 给出一棵树，找出一个点root，使得所有点到这个点的权值和最大，所谓的权值是指为点到root的路径上所有边权里的最小值。

    思路 : 好吧..竟然是并查集...知道是并查集后应该不难, 难的是如何想到并查

           边按权值大到小排序, 做并查集.
           因为给出的是树, 所以其实每条边e都是是用来连接两个连通块的, 在这里`连通块`即并查集的集合. 我们需要考虑的是要把root放在e的哪一边? 可以肯定, 放在使得新的边权和最大的那一边最优, 详细看代码. 每次连接两个集合, 就要更新权值总和, 这需要知道两个集合各自的权值和, 集合内的点数目. 我觉得这一点是我之前做的并查集没有过的, **亮点**
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
#define N   200001
struct Edge { 
        int w, x, y;
} e[N];
bool cmp(Edge a, Edge b) { return a.w > b.w; }
int father[N], cnt[N];
LL sum[N];
int find(int x) 
{ 
    return (x == father[x]) ? x : (father[x] = find(father[x]));
}
int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n-1; i++)
            scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);

        sort(e, e+n-1, cmp);

        for(int i = 1; i <= n; i++) {
            father[i]   =   i;
            sum[i]      =   0;
            cnt[i]    =   1;
        }

        for(int i = 0; i < n-1; i++) {
            int fa = find(father[e[i].x]);
            int fb = find(father[e[i].y]);
            LL va = (LL)e[i].w * cnt[fb] + sum[fa];
            LL vb = (LL)e[i].w * cnt[fa] + sum[fb];
            if(va > vb) {
                father[fb] = fa;
                sum[fa] = va;
                cnt[fa] += cnt[fb];
            } else {
                father[fa] = fb;
                sum[fb] = vb;
                cnt[fb] += cnt[fa];
            }
        }
        cout << sum[find(e[n-2].x)] << endl;
    }
}
