/*
	拓扑 简单题
*/
//lightoj 1003
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define			MAXM		10005
#define			MAXN		20005
map< string, int > M;
struct Edge {
	int v, next;
} edge[MAXM];
int head[MAXN], in_deg[MAXN],Q[MAXN];
bool vis[MAXN]; 
int edge_num;
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	M.clear();
	memset(head, -1, sizeof(head));
	memset(in_deg,0, sizeof(in_deg));
	memset(vis, false, sizeof(vis));
}
bool bfs(int s)
{
	int top = 0, tail = 0;
	Q[top++] = s;
	while(tail < top) {
		int u = Q[tail++];
		vis[u] = true;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			in_deg[v] --;
			if(!in_deg[v]) Q[top++] = v;
		}
	}
}
int main()
{
	string s1, s2;
	int cases, Cas = 0, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &m);
		init();
		int Index = 1;
		while(m--) {
			cin >> s1 >> s2;
			if(M[s1] == 0) M[s1] = Index++;
			if(M[s2] == 0) M[s2] = Index++;
			int x = M[s1], y = M[s2];
			in_deg[y] ++;
			add_edge(x, y);
		}
		for(int i = 1; i < Index; i++) if(!vis[i] && !in_deg[i]) bfs(i);
		bool flag = true;
		for(int i = 1; i < Index; i++) if(!vis[i]) flag = false;
		printf("Case %d: %s", ++Cas, flag ? "Yes\n" : "No\n");
	}
	return 0;
}
