/*
	连通性  反向建图   好题  启发题

	题意：题意：给出一个有向图，表示点与点之间的支持关系，支持关系可以传递，A支持B，B支持C，那么A支持C，C获得两个支持。找出哪些人获得最多支持，输出获得支持票数，然后升序点的标号

	思路：缩点，统计点u能被多少个点到达。
		
		  难点就在于统计这一块儿。得到缩点后的DAG后，问题就变成，一个点能被多少个点到达，要知道一个点能被多少个点到达，一般就是方向建图。
		  ***反向建图统计前驱点数*** : 建立反向图后，对于点u，从u除法遍历整个图，统计能够到达的点。易知点u为当前入度为0的点。



	反思：一开始我是边拓扑排序边统计，但是对于除法点x，x能通过i到达y，也能够通过j到达y，这样的话我的拓扑就会统计两次y。而且在我的源代码里没法补救。
		  
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define		MAXN		5005
#define		MAXM		30005
struct Edge {
	int u, v, next;
} edge[MAXM], e[MAXM];
vector<int> b[MAXN];
int head[MAXN], dfn[MAXN], low[MAXN], S[MAXN], belong[MAXN], num[MAXN], in_deg[MAXN];
bool in_stack[MAXN], vis[MAXN], pass[MAXN];
int edge_num, n, S_top, Index, Order;

void add_edge(int u, int v)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num ++;
}
void init()
{
	edge_num = S_top = Order = 0;
	Index = 1;
	for(int i = 0; i < n; i++) b[i].clear();
	memset(num, 0, sizeof(num));
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_deg, 0, sizeof(in_deg));
	memset(in_stack, false, sizeof(in_stack));
	memset(vis, false, sizeof(vis));
}
void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
	S[S_top++] = u;
    in_stack[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(dfn[v] == 0) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int x;
        do {
			x = S[--S_top];
            in_stack[x] = false;
            belong[x] = Order;
			b[Order].push_back(x);
			num[Order]++;
        } while(x != u);
        Order++;
    }
}
void dfs(int u, int ancester)		//遍历能到达ancester的点
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!pass[v]) num[ancester] += num[v], pass[v] = true, dfs(v, ancester);
	}
}
int calc(int n)
{
	S_top = 0;
	for(int i = 0; i < n; i++) if(!in_deg[i]) {
		S[S_top++] = i;
	}
	while(S_top--) {				//对于每个入度为0的点做统计
		int u = S[S_top];
		memset(pass, false, sizeof(pass));
		dfs(u, u);
		vis[u] = true;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(--in_deg[v] == 0) S[S_top++] = v;
		}
		num[u]--;
	}
	int max_ = 0;
	for(int i = 0; i < n; i++) max_ = max(max_, num[i]);
	return max_;
}
int main()
{
	int cases, Cas = 0, u, v, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			e[i].u = u, e[i].v = v;
		}
		for(int i = 0; i < n; i++) if(!dfn[i]) Tarjan(i);
		//for(int i = 0; i < n; i++) printf("belong[%d] = %d\n", i, belong[i]);
		edge_num = 0;
		memset(head, -1, sizeof(head));
		for(int i = 0; i < m; i++) {		//逆向构图
			u = belong[e[i].u], v = belong[e[i].v];
			if(u != v) {
				add_edge(v, u), in_deg[u]++;
			}
		}
		int max_ = calc(Order);
		/*
		for(int i = 0; i < m; i++) {
			u = e[i].u, v = e[i].v;
			if(belong[u] != belong[v] && !path[belong[u]][belong[v]]) {
				add_edge(belong[u], belong[v]);
				in_deg[belong[v]]++;
				path[belong[u]][belong[v]] = true;
			}
		}

		int max_ = topsort(Order);
		*/
		for(int i = 0; i < Order; i++) if(!vis[i]) num[i]--, max_ = max(max_, num[i]);			//孤立点
		vector<int> ans;
		for(int i = 0; i < Order; i++) if(num[i] == max_) {
			for(int Size = b[i].size(), j = 0; j < Size; j++) ans.push_back(b[i][j]);
		}
		
		sort(ans.begin(), ans.end());
		printf("Case %d: %d\n", ++Cas, max_);
		for(int Size = ans.size(), i = 0; i < Size; i++) printf("%d%c", ans[i], i == Size - 1 ? '\n' : ' ');
	}
	return 0;
}
