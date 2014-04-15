#include <stdio.h>
#include <string.h>
#define		MAXN		100005
#define		MAXM		100005*2 

struct Edge {
	int v, w, next;
} edge[MAXM], group[MAXN];
int head[MAXN], dis[MAXN], belong[MAXN], S[MAXN], node[MAXN], deg[MAXN];
bool vis[MAXN];
int edge_num, n, C, S_top, group_num;

void init()
{
	edge_num = group_num = 0;
	S_top = 0;
	memset(head, -1, sizeof(head));
	memset(node, -1, sizeof(node));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}
void add_group(int u, int i)
{
	group[group_num].v = i, group[group_num].next = node[u];
	node[u] = group_num++;
}
int SPFA(int s, int t)
{
	int cheat = 0;
	memset(dis, 127, sizeof(dis));
	memset(vis, false, sizeof(vis));
	int INF;
	memset(&INF, 127, sizeof(int));
	vis[s] = true;
	dis[s] = 0;
	S[S_top++] = s;
	while(S_top) {
		int u = S[--S_top];
		vis[u] = false;
		//if(++cheat > n*26) break;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(dis[v] > dis[u] + edge[k].w) {
				dis[v] = dis[u] + edge[k].w;
				if(!vis[v]) S[S_top++] = v, vis[v] = true;
			}
		}

		for(int k = node[u+1]; k != -1; k = group[k].next) {
			int v = group[k].v;
			if(dis[v] > dis[u] + group[k].w) {
				dis[v] = dis[u] + C;
				if(!vis[v]) S[S_top++] = v, vis[v] = true;
			}
		}

		for(int k = node[u-1]; k != -1; k = group[k].next) {
			int v = group[k].v;
			if(dis[v] > dis[u] + group[k].w) {
				dis[v] = dis[u] + C;
				if(!vis[v]) S[S_top++] = v, vis[v] = true;
			}
		}
	}
	if(dis[t] == INF) return dis[t] = -1;
	return dis[t];
}
void dfs(int u, int sum);
int main()
{
	int cases, m, u, v, w, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d%d", &n, &m, &C);
		init();
		for(int i = 1; i <= n; i++) {
			scanf("%d", &u);
			belong[i] = u;
			add_group(u, i);
		}
		memset(deg, 0, sizeof(deg));
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
			deg[u]++, deg[v]++;
		}
		for(int i = 1; i <= n; i++) if(node[i] != -1)
		{
			int tmp = -1;
			for(int k = node[i]; k != -1; k = group[k].next) {
				int v = group[k].v;
				if(deg[v] == 0) {
					if(tmp == -1) node[i] = group[k].next;
					else group[tmp].next = group[k].next;
				}
				else tmp = k;
			}
		}
		memset(dis, 127, sizeof(dis));
		//dfs(1, 0);
		//printf("Case #%d: %d\n", ++Cas, dis[n]);//SPFA(1, n));
		printf("Case #%d: %d\n", ++Cas, SPFA(1, n));
	}
	return 0;
}

void dfs(int u, int sum)
{
	if(dis[n] <= sum || dis[u] <= sum) return ;
	dis[u] = sum;
	if(u == n) return ;

	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		dfs(v, sum+edge[k].w);
	}

	for(int k = node[u+1]; k != -1; k = group[k].next) {
		int v = group[k].v;
		dfs(v, sum+C);
	}

	for(int k = node[u-1]; k != -1; k = group[k].next) {
		int v = group[k].v;
		dfs(v, sum+C);
	}
}
