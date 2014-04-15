/*
	KM  二分图最优匹配
	题意：略
	思路：模型还是挺容易看出来的，先n次SPFA搞出station到port的最短距离，作为二分图的边（有向！）
		  哈哈，虽然KM值直接copy的，但是能A还是挺高兴的.
*/	
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		305

struct Edge {
	int v, w, next;
} edge[2 * MAXN * MAXN];
int  head[MAXN], linker[MAXN], slack[MAXN], ans[MAXN], LX[MAXN], LY[MAXN], visx[MAXN], visy[MAXN], Q[MAXN * MAXN], port[MAXN];
int  dis[MAXN][MAXN];
bool vis[MAXN];
int edge_num, n, m, when, INF;

bool find(int u)
{
    visx[u] = when;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visy[v] == when) continue;
        int rest = LX[u] + LY[v] - edge[k].w;
        if(rest == 0) {
            visy[v] = when;
            if(linker[v] == -1 || find(linker[v])) {
                linker[v] = u;
                ans[v]  = k;        //记录边
                return true;
            }
        } else slack[v] = min(slack[v], rest);  //u在交错树，v不在交错树，更新d  也就是说边(u,v)不在相等子图中
    }
    return false;
}
bool KM()
{
    memset(LX, 128, sizeof(LX));        //最大匹配
    memset(LY,   0, sizeof(LY));
    memset(linker, -1,sizeof(linker));
    for(int i = 1; i <= n; i++)
        for(int k = head[i]; k != -1; k = edge[k].next) {
            LX[i] = max(LX[i], edge[k].w);
        }
	
    for(int i = 1; i <= n; i++) {
        for(int j = 1+n; j <= n+n; j++) slack[j] = INF;
        while(true) {
			when++;
            if(find(i)) break;
            else {
                int tmp = INF;
                for(int j = 1+n; j <= n+n; j++) if(visy[j] != when) tmp = min(tmp, slack[j]);
                if(tmp == INF) return false;         //无法松弛，找不到完备匹配     TODO TODO 这里判断是否有完备匹配
                for(int j = 1; j <= n; j++)     if(visx[j] == when) LX[j] -= tmp;
                for(int j = 1+n; j <= n+n; j++) 
                    if(visy[j] == when) LY[j] += tmp;
                    else slack[j] -= tmp;       //修改顶标后，要把所有的不在交错树中的Y顶点的slack值都减去d。
            }
        }
    }
    return true;
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void SPFA(int s, int *dis)
{
	memset(vis, false, sizeof(vis));
	dis[s] = 0;
	
	int car = 0, cdr = 0;
	Q[car++] = s;
	while(cdr < car) {
		if(car >= MAXN * MAXN) while(true) ;		//for debug

		int u = Q[cdr++] ;   
		vis[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v, w = edge[k].w;
			if(dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				if(!vis[v]) vis[v] = true, Q[car++] = v; 
			}
		}
	}
}
int solve()
{
	for(int i = 0; i < n; i++) {
		memset(dis[port[i]], 127, sizeof(dis[port[i]]));
		SPFA(port[i], dis[port[i]]);				//for every ship-station, do SPFA
	}
	init();
	for(int i = 0; i < n; i++) 		//ship-station	I change it to Index
		for(int j = 1; j <= n; j++)	if(dis[port[i]][j] != INF) //port
			add_edge(j, i+1+n, INF - dis[port[i]][j]);

	KM();
	int sum = 0;
	for(int i = 1+n; i <= n+n; i++) sum += INF - edge[ ans[i] ].w;
	return sum;
}
int main()
{
	int u, v, w, es2s, es2p;
	memset(&INF, 127, sizeof(int));
	while(scanf("%d %d %d %d", &n, &m, &es2s, &es2p) != EOF) {		//n-port, m-station, es2s-station-to-station, es2p
																	//1-n : port, n+1 - n+m : station
		init();
		for(int i = 0; i < n; i++) scanf("%d", &port[i]), port[i] += n;
		while(es2s--) {
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u+n, v+n, w);   add_edge(v+n, u+n, w);
		}
		while(es2p--) {
			scanf("%d %d %d", &u, &v, &w);
			//add_edge(u, v+n, w);
			add_edge(v+n, u, w);
		}

		printf("%d\n", solve());
	}
	return 0;
}
