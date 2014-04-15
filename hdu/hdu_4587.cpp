/*
	连通性  割点   好题  AC后花很多时间来思考细节
	题意：对于一个无向图删除两个点，使得剩余图连通分量最多。

	思路：无向图里的连通分量：只要两点(u,v)有路径到达即为同一的连通分量。
		  删除一个节点使得剩余连通分量最多：尽量找割点。对于割点u，如果u只存在于一个连通分量中，则删u和删该连通分量的其它点没什么区别。但是若割点u存在于多个连通分量中，就不一样了，原因很简单，略。如果没有割点的话会是怎样呢？答案是删哪个都一样。什么时候没有割点呢？当所有点要么为孤立点，要么属于一个双连通分量中。
		  再回到上面问题，可能在找割点的过程中，找不到一个割点，那么只能随便删除一个点，那么图的连通分量就是 ANS = max(ANS,CNT)吗？
		  不一定的！因为一个无向图中，如果没有割点，删除一个点，图的连通分量数不一定保持不变，而是可能减少
		  例如
		  1 2
		  3 2
		  4 2
		  5 2
		  这种数据，删除点2，后得到1 3 4 5这些连通分量，CNT = 4，这些点中没有一个点是割点，那么任意删除一个点即可
		  但删除了一个点，连通分量数不变吗？不是的，而是-1
		  所以为了保证正确性，更新答案应该是
		  ANS = max(ANS,CNT-1);

		  总结一下，当图中没有割点时：<1>当原图有存在双连通分量，则删除双连通分量里的点，使得删点后的连通分量数保持不变 <2>当原图所有点都是孤立点，则删点后的连通分量数减1


		  OK!  所以第一步枚举删的第一个点后，问题就转为上述的“删除一个节点使得剩余连通分量最多”的问题了。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN		5005
struct Edge {
	int v, next;
} edge[MAXN * 2];
int head[MAXN], cnt[MAXN], dfn[MAXN], low[MAXN];
bool vis[MAXN * 2], in_stack[MAXN];
int root, del, edge_num, Index, n;
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void init2()
{
	Index = 1;
	memset(dfn, 0, sizeof(dfn));
	memset(cnt, 0, sizeof(cnt));
	memset(vis, false, sizeof(vis));
	memset(in_stack, false, sizeof(in_stack));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void Tarjan(int u)
{
	dfn[u] = low[u] = Index++;
	in_stack[u] = true;
	int tot = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) if(!vis[k]) {
		vis[k] = vis[k^1] = true;
		int v = edge[k].v;
		if(v == del) continue;
		if(!dfn[v]) {
			Tarjan(v);
			tot ++ ;
			low[u] = min(low[u], low[v]);
			if(u != root && low[v] >= dfn[u]) {
				cnt[u] ++ ;
				//if(del == 6) printf("# %d  %d\n", u, v);
			}
		} else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(u == root) cnt[u] = tot - 1;			//为了处理没有割点的第二种情况。
	in_stack[u] = false;		//TODO  疑问   
}
int main()
{
	int m, u, v;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		while(m--) {
			scanf("%d%d", &u, &v);
			u++, v++;
			add_edge(u, v), add_edge(v, u);
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			del = i;
			init2();
			int sum = 0;
			for(int j = 1; j <= n; j++) if(!dfn[j] && del != j) {
				sum ++ ;
				root = j;
				Tarjan(j);
			}
			for(int j = 1; j <= n; j++) if(j != i) ans = max(ans,  sum + cnt[j]);		//这里一定要判断!! 因为如果是第二种没有割点的情况的话要减1，即cnt[x] = -1，但cnt[del] = 0，这时候就会错
			//我觉得定个sum出来把事情弄方便了一些。如果删掉的不是root，而是一个割点，则root所在的连通分量已经被加到sum里了；如果删的是root，则sum-1，即cnt[root] = 分支数 - 1
		}
		printf("%d\n", ans);
	}
	return 0;
}
