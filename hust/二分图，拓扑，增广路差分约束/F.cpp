/*
	WA
	拓扑排序 + 优先队列  或者反向建图

	题意读不懂，反正是会做了，不纠结于题意坑了.
*/
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
#define			MAXN		205
#define			MAXM		40005 
struct Edge {
	int v, next;
} edge[MAXM];
int  head[MAXN], in[MAXN], c[MAXN], ans[MAXN];
int n , edge_num;
priority_queue<int, vector<int>, greater<int> > Q;

void init()
{	
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(in,    0, sizeof(in));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool topsort()
{
	int color = 1;
	while(!Q.empty()) Q.pop();
	for(int i = 1; i <= n; i++) if(!in[i]) Q.push( i );
	while(!Q.empty()) {
		int u = Q.top();  Q.pop();
		c[u] = color++;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(--in[v] == 0) Q.push( v );
		}
	}
	for(int i = 1; i <= n; i++) if(in[i]) return false;
	return true;
}
int main()
{
	int cases, u, v, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		init();
		while(m--) {
			scanf("%d %d", &u, &v);
			add_edge(u, v);		
			in[v]++;
		}
		if(!topsort()) { puts("-1"); continue ; }
		for(int i = 1; i <= n; i++) ans[c[i]] = i;//printf("%d%c", c[i], i == n ? '\n' : ' ');
		for(int i = 1; i <= n; i++) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	return 0;
}
