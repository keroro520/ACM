#include <stdio.h>
#include <string.h>
#define		MAXN	8005*2
#define		MAXM	20005*2
struct Edge {
	int v, next;
} edge[MAXM];
int head[MAXN], color[MAXN], S[MAXN];
int S_top, edge_num, n;
inline	int	hash(int x)	{	return (x ^ 1); }
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(color, 0, sizeof(color));
}
bool dfs(int u)
{
	if(color[hash(u)]) return false;
	if(color[u])   return true;
	color[u] = 1;
	S[S_top++] = u;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfs(v)) return false;
	}
	return true;
}
bool solve()
{
	for(int i = 0; i < 2*n; i += 2)			// i += 2 ???
		if(!color[i] && !color[hash(i)]) {
			S_top = 0;
			if(!dfs(i)) {
				while(S_top > 0) color[S[--S_top]] = 0;
				if(!dfs(hash(i))) return false;
			}
		}
	return true;
}
int main()
{
	int m, u, v;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			u--, v--;
			add_edge(v, hash(u)), add_edge(u, hash(v));	
		}
		if(!solve()) puts("NIE");
		else {
			for(int i = 0; i < 2*n; i++) if(color[i] == 1) printf("%d\n", i+1);
		}
	}
	return 0;
}
