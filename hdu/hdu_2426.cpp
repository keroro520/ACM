/*
    二分图带权匹配  KM   好题

    题意：二分图最大权匹配的模板题 + 有可能不存在完备匹配。不存在完备匹配时输出-1，否则输出最大权匹配

    思路：这个模板把判断是否有完备匹配嵌入到了KM算法里面，所以不用特意地在前面用匈牙利判断。
          把原来习惯用slack变量改为slack数组。速度有加快。
          slack数组 + 判断是否有完备匹配 + KM
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define     MAXN        505
#define     INF         999999999

int n, m, edge_num;
int slack[MAXN], head[MAXN], LX[MAXN], LY[MAXN], link[MAXN], ans[MAXN];
bool appear[MAXN], visx[MAXN], visy[MAXN];
struct Edge {
    int v, next, w;
} edge[50005];

void add_edge(int u, int v, int w)
{
    edge[edge_num].v = v;
    edge[edge_num].w = w;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
bool find(int u)
{
    visx[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visy[v]) continue;
        int rest = LX[u] + LY[v] - edge[k].w;
        if(rest == 0) {
            visy[v] = true;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                ans[v]  = k;        //记录边
                return true;
            }
        } else slack[v] = min(slack[v], rest);  //u在交错树，v不在交错树，更新d  也就是说边(u,v)不在相等子图中
    }
    return false;
}
bool KM()
{
    memset(LX, 128, sizeof(LX));
    memset(LY,   0, sizeof(LY));
    memset(link, -1,sizeof(link));
    for(int i = 1; i <= n; i++)
        for(int k = head[i]; k != -1; k = edge[k].next) {
            LX[i] = max(LX[i], edge[k].w);
        }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) slack[j] = INF;
        while(true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(find(i)) break;
            else {
                int tmp = INF;
                for(int j = 1; j <= m; j++) if(!visy[j]) tmp = min(tmp, slack[j]);
                if(tmp == INF) return false;         //无法松弛，找不到完备匹配
                for(int j = 1; j <= n; j++) if(visx[j]) LX[j] -= tmp;
                for(int j = 1; j <= m; j++) 
                    if(visy[j]) LY[j] += tmp;
                    else slack[j] -= tmp;       //修改顶标后，要把所有的不在交错树中的Y顶点的slack值都减去d。
            }
        }
    }
    return true;
}
void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
    memset(appear, false, sizeof(appear));
}
int main()
{
    int e, x, y , z, Cas = 0;
    while(scanf("%d%d%d", &n, &m, &e) != EOF) {
        printf("Case %d: ", ++Cas);
        init();
        int appear_num = 0;
        while(e--) {
            scanf("%d%d%d", &x, &y, &z);
            x++, y++;
            if(z < 0) continue;
            if(!appear[y]) appear[y] = true, appear_num++;
            add_edge(x, y, z);
        }
        if(appear_num < n) {
            printf("-1\n");
            continue;
        }
        bool perfect_match = KM();
        if(!perfect_match) printf("-1\n");
        else {
            int sum = 0;
            for(int i = 1; i <= m; i++) if(link[i] != -1) sum += edge[ans[i]].w;
            printf("%d\n", sum);
        }
    }
    return 0;
}
