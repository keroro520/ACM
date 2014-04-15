/*
	有重边，没处理，WA。也不知道想法对不对。
	先对于每条新加边(u,v)按max(depth[u], depth[v])从大到小排序，然后按大小顺序一条一条插入，如果u和v已经同属于一个环，ans++，然后记录u-v之间的点属于同一双连通分量。
	最后答案 = 所有的新旧边对 - 属于u,v属于同一分量的旧边*ans
			 = m*(n-1) - sum*ans
*/
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define			MAXN		100005
struct Edge {
	int u, v, next;
} edge[MAXN * 2], Query[MAXN];
int head[MAXN], father[MAXN], depth[MAXN], up[MAXN];
int edge_num, n;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= n; i++) father[i] = i;
}
void add_edge(int u, int v)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool cmp(const Edge &a, const Edge &b) {
	if(max(depth[a.u], depth[a.v]) != max(depth[b.u], depth[b.v])) {
		return max(depth[a.u], depth[a.v]) > max(depth[b.u], depth[b.v]);
	} else return min(depth[a.u], depth[a.v]) > min(depth[b.u], depth[b.v]);
}
void build(int u, int fa, int deep)
{
	depth[u] = deep;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		build(v, u, deep+1);
		up[v] = u;
	}
}
int Find(int x) { return x == father[x] ? x : father[x] = Find(father[x]); }
void Union(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);
	while(depth[u] != depth[v]) {
		father[u] = up[u];
		u = up[u];
	}
	while(u != v) {
		father[u] = up[u], father[v] = up[v];
		u = up[u], v = up[v];
	}
}
int main()
{
	int query, u, v;
	while(scanf("%d%d", &n, &query) != EOF) {
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		up[1] = 0;
		build(1, 0, 0);
		long long ans = 0;
		for(int i = 0; i < query; i++) scanf("%d%d", &Query[i].u, &Query[i].v);
		sort(Query, Query+query, cmp);
		for(int i = 0; i < query; i++) {
			u = Query[i].u, Query[i].v;
			int fu = Find(u), fv = Find(v);
			if(fu == fv) {
				ans ++;
			} else {
				Union(fu, fv);
			}
		}
		long long sum = query - ans ;
		for(int i = 0; i < edge_num; i++) if(Find(edge[i].u) == Find(edge[i].v)) sum ++;
		ans = (long long)query * (n-1) - sum * ans;
		printf("%I64d\n", ans);
	}
	return 0;
}
