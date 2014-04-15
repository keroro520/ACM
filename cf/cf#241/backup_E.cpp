/*
	TLE
*/
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
#define		DEBUG		0
#define		MAXN		505
#define		MAXM		(505*505)
#define		INF			99999999

struct Edge {
	int u, v, w, next;
} edge[MAXM];
typedef pair<int,int> Pii;
priority_queue< Pii, vector<Pii> , greater<Pii> > Q;
vector<int> path[MAXN];
int head[MAXN], d[MAXN], get_ans[MAXN];
bool out[MAXN], color[MAXM];
int edge_num , n, m;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof head);
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].w = w;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int calc_single_path(int s, int u)
{
	if(get_ans[u] || u == s) return get_ans[u];
	return get_ans[u] = 1 + calc_single_path(s, edge[*path[u].begin()].u );
}
int calc_multi_path(int u)
{
	int ans = 0;
	for(vector<int> :: iterator it = path[u].begin(); it != path[u].end(); it++) {
		if(color[(*it) / 2]) continue;
		else color[(*it) / 2] = true, ans += 1 + calc_multi_path(edge[*it].u);
	}
	return ans;
}
void solve(int s)
{
	while(!Q.empty()) Q.pop();
	for(int i = 1; i <= n; i++) d[i] = INF;
	d[s] = 0;
	for(int i = 1; i <= n; i++) Q.push( Pii(d[i], i) ), path[i].clear();
	memset(out, false, sizeof out);
	int inQueue = n;
	while(inQueue--) {
		int u;
		while(u = Q.top().second, Q.pop(), out[u]) ;
		out[u] = true;

		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v, w = edge[k].w;
			if(d[v] > d[u] + w) {
				path[v].clear(), path[v].push_back(k);
				Q.push( Pii(d[v] = d[u] + w, v) );
			} else if(d[v] == d[u] + w) {
				path[v].push_back(k);
			}
		}
	}
	#if DEBUG
	for(int i = s+1; i <= n; i++) {
		printf("!  %d %d : ", s, i);
		for(vector<int> :: iterator it = path[i].begin(); it != path[i].end(); it++)
			printf("(%d %d)", edge[*it].u, edge[*it].v);
		puts("");
	}
	#endif
	memset(get_ans, 0, sizeof get_ans);
	for(int i = 1; i <= n; i++) 
		if(path[i].size() > 1) {
			memset(color, false, sizeof color);
			get_ans[i] = calc_multi_path(i);
		}
	for(int i = s+1; i <= n; i++) 
		if(path[i].size() == 1) {
			get_ans[i] = calc_single_path(s, i);
		}
}
int main()
{
	int u, v, w;
	scanf("%d %d", &n, &m);
	init();
	for(int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, w), add_edge(v, u, w);
	}

	for(int i = 1; i <= n; i++) {
		solve(i);
		for(int j = i + 1; j <= n; j++) printf("%d ", get_ans[j]);
	} puts("");
	return 0;
}
