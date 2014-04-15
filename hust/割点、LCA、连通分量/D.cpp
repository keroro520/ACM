/*
	LCA   并查集  Tarjan离线  好题  难题   神题！！！
	题意：

	收获：并查集在压缩路径的时候可以更新一些数据，这点是我之前没见过的。   （详见Find()）
		  Tarjan离线搞最小公共祖先以递归回到祖先lca的时候才能有信息回答query(u,v)，之前都是遍历到v点的时候就能回答query(u,v)（假设u点已经遍历过了），这道题是要递归回到祖先z的时候才能回答。

	思路：对于每个节点x，当前祖先为z 
			max(x)/min(x)	x到z路径上的最大/小值
			up(x)			x->z路径上的dp值
			down(x)			z->x路径上的dp值
			则ans( query(u,v) ) = max{ up(x), down(y), max(y)-min(x) }
			方程不是重点，重点是如何实现.

	代码解释：
		//================================================================================
		int Find(int x)
		//把更新过程放在Find里面，边向上并查集找祖先，边更新x-lca的信息，把并查集用得太好了！！
		//先把当前x的父亲y记录下来，然后father[x] = Find(Father[x]) 向上找y的祖先并更新节点y的属性。
		//之后利用y点的信息更新x点信息。想象一下，超美妙。假设当前的祖先为z，则Find(father[x])过程中更新了区间(y, z)的信息，存在节点y里面，那接下来就用区间(y, z)的信息（存在节点y），和(x, y)的信息（存在节点x）来更新区间(x, z)的信息，并存到x节点。
		{
			if(x == father[x]) return x;
			int y = father[x];
			father[x] = Find(father[x]);
		
			a[x].up 	= 	max(a[y].max - a[x].min, max(a[x].up, a[y].up));
			a[x].down	= 	max(a[x].max - a[y].min, max(a[x].down, a[y].down));
			a[x].max	= 	max(a[x].max, a[y].max);
			a[x].min 	= 	min(a[x].min, a[y].min);
			return father[x];
		}


		//==================================================================================
		for(int Size = Quetion[u].size(), i = 0; i < Size; i++) 
		//以前的LCA都是对于query(u,v)，若vis[v] == true，则根据Find(v)就可以对query进行回答，但这道题不行。因为我们接下来要递归下去，要保持当前子树的祖先都是x，所以我们必须得在递归回来之后才能Union(x, fa)。那不Union，根据Find(v)找到当前v的祖先（当前树的根节点）又没有办法回答query(u,v)，那就不能像一般LCA那样在这里就回答咯~~
		//怎么办呢？首先我们应该考虑，什么时候我们才能回答query(u,v)？设当前lca(u,v) = z，分析一下知道，要回答query(u,v)，就要知道(u->z)和(z->v)的信息。那自然我们就知道---当递归回到z的时候我们能回答query(u,v).
		//所以这里我们把每个query(u,v)存到Q[z]里面，在LCA递归回到z的时候再输出。
		{
			int v = Quetion[u][i].first, id = Quetion[u][i].second;
			if(!vis[v]) continue;
			int fv = Find(v);
			if(id >= 0) Q[fv].push_back(u), Q[fv].push_back(v), Q[fv].push_back(id);
			else 		Q[fv].push_back(v), Q[fv].push_back(u), Q[fv].push_back(-id);
		}

		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(!vis[v]) {
				LCA(v);
				Union(u, v);							//Union的位置很重要！递归回来才能Union
			}
		}

		for(int Size = Q[u].size(), i = 0; i < Size; i += 3) {
		//这里就是对于每个z的回答.  这里u表示lca(x,y) = u
			int x = Q[u][i], y = Q[u][i+1], id = Q[u][i+2];
			Find(x), Find(y);
			ans[ id ] = max( a[x].up, max(a[y].down, a[y].max - a[x].min) );
		}
*/
//poj 3728
#include <algorithm>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;
#define			MAXN		50005

struct Tree_Node {
	int min, max, up, down;
} a[MAXN];
struct Edge {
	int next, v;
} edge[MAXN * 2];
typedef		pair<int,int> 	PII;
vector< PII > Quetion[MAXN]; 
vector<int> Q[MAXN];
int head[MAXN], father[MAXN], ans[MAXN];
bool vis[MAXN];
int n, edge_num;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= n; i++) Quetion[i].clear(), Q[i].clear();
	for(int i = 1; i <= n; i++) father[i] = i;
}
void add_edge(int u, int v)
{	
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int Find(int x)
{
	if(x == father[x]) return x;
	int y = father[x];
	father[x] = Find(father[x]);

	a[x].up 	= 	max(a[y].max - a[x].min, max(a[x].up, a[y].up));
	a[x].down	= 	max(a[x].max - a[y].min, max(a[x].down, a[y].down));
	a[x].max	= 	max(a[x].max, a[y].max);
	a[x].min 	= 	min(a[x].min, a[y].min);
	return father[x];
}
void Union(int u, int v)
{
	father[v] = u;
}
void LCA(int u)
{
	vis[u] = true;
	for(int Size = Quetion[u].size(), i = 0; i < Size; i++) {			
		int v = Quetion[u][i].first, id = Quetion[u][i].second;
		if(!vis[v]) continue;
		int fv = Find(v);
		if(id >= 0) Q[fv].push_back(u), Q[fv].push_back(v), Q[fv].push_back(id);
		else 		Q[fv].push_back(v), Q[fv].push_back(u), Q[fv].push_back(-id);
	}

	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!vis[v]) {
			LCA(v);
			Union(u, v);			//Union的位置很重要！
		}
	}
	for(int Size = Q[u].size(), i = 0; i < Size; i += 3) {
		int x = Q[u][i], y = Q[u][i+1], id = Q[u][i+2];
		Find(x), Find(y);
		ans[ id ] = max( a[x].up, max(a[y].down, a[y].max - a[x].min) );
	}
}

int main()
{
	int u, v, query;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i].min);
			a[i].max = a[i].min;
			a[i].up = a[i].down = 0;
		}
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		scanf("%d", &query);
		for(int i = 1; i <= query; i++) {
			scanf("%d%d", &u, &v);
			Quetion[u].push_back( PII(v, i) ), Quetion[v].push_back( PII(u, -i) );
		}
		LCA(1);
		for(int i = 1; i <= query; i++) printf("%d\n", ans[i]);
	}
	return 0;
}
