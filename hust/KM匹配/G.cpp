/*
    二分图带权匹配   KM   经典题  好题
    题意：一个有向图，把该图分成一些环，使得构成这些环的总权值最小。一个环至少两个点，一个点在且仅在一个环中。

    思路：神奇的构图...orz...
          环的性质其实就是每个点有且仅有一个入度一个出度。拆点并把原边(u,v)变成(u,v')就把该环的性质转化成了二分图匹配...加上权值，就是二分图带权匹配了。

          建图虽然用一句话就概括完了，但很妙好不好！所以说，图论的构图真是靠运气成分很大呀。
*/
//hdu 1853
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define          MAXN        205
#define         hash(x)         ((x) + (n))
struct Edge {
    int v, next, w;
} edge[(MAXN*MAXN) << 2];
int link[MAXN], LX[MAXN], LY[MAXN], visx[MAXN], visy[MAXN], slack[MAXN];
int head[MAXN];
int edge_num, n, when = 1;
void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int w)
{
    edge[edge_num].v = v;
    edge[edge_num].w = w;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
bool find(int u)
{
    visx[u] = when;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visy[v] == when) continue;
        int rest = LX[u] + LY[v] - edge[k].w;
        if(rest == 0) {
            visy[v] = when;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
        } else slack[v] = min(slack[v], rest);
    }
    return false;
}
bool KM()
{
    memset(LX, 128, sizeof(LX));
    memset(LY,   0, sizeof(LY));
    memset(link,-1, sizeof(link));
    for(int i = 1; i <= n; i++) 
        for(int k = head[i]; k != -1; k = edge[k].next) {
            LX[i] = max(LX[i], edge[k].w);
        }
    for(int start = 1; start <= n; start ++) {
        for(int i = n+1; i <= hash(n); i++) slack[i] = (INT_MAX);
        while(true) {
            when++;
            if(find(start)) break;
            else {
                int d = (INT_MAX);
                for(int i = n+1; i <= hash(n); i++) if(visy[i] != when) d = min(d, slack[i]);
                if(d == INT_MAX) return false;
                for(int i = 1; i <= n; i++) if(visx[i] == when) LX[i] -= d;
                for(int i = n+1; i <= hash(n); i++)
                    if(visy[i] == when) LY[i] += d;
                    else slack[i] -= d;
            }
        }
    }
    return true;
}
int main()
{
    int m, x, y, z;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, hash(y), -z);
        }
        bool perfect_match = KM();
        if(!perfect_match) {
            printf("-1\n");
            continue;
        }
        int ans = 0;
        for(int i = n+1; i <= n+n; i++) ans += LX[link[i]] + LY[i];
        printf("%d\n", -ans);
    }
    return 0;
}
