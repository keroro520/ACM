/*
	树链剖分模板题
	题意：一棵树上有n个节点，编号分别为1到n，每个节点都有一个权值w。我们将以下面的形式来要求你对这棵树完成一些操作： I. CHANGE u t : 把结点u的权值改为t II. QMAX u v: 询问从点u到点v的路径上的节点的最大权值 III. QSUM u v: 询问从点u到点v的路径上的节点的权值和 注意：从点u到点v的路径上的节点包括u和v本身

	=_=||  bzoj_1036稍微改一下就1A了。
*/
//lightoj 1348
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN		30005
#define		L(x)		((x) << 1)
#define		R(x)		(((x) << 1) | 1)
#define		MID(l,r)	(((l) + (r)) >> 1)
struct Edge {
	int v, next;
} edge[MAXN * 2];
struct Segment_Tree {
	int l, r, max, sum, mid;
} f[MAXN << 2];
int head[MAXN], top[MAXN], hson[MAXN], fa[MAXN], depth[MAXN], size[MAXN], son[MAXN], weight[MAXN], w[MAXN], tid[MAXN];
int n, edge_num, Index;

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = Index = 0;
	memset(head, -1, sizeof(head));
	memset(hson, -1, sizeof(hson));
	memset(size,  0, sizeof(size));
}
void find_heavy_edge(int u, int father, int dep)
{
	depth[u] = dep;
	fa[u] 	 = father;
	size[u]  = 1;
	int Max_size = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		find_heavy_edge(v, u, dep+1);
		size[u] += size[v];
		if(size[v] > Max_size) Max_size = size[v], hson[u] = v;
	}
}
void connect_heavy_chain(int u, int ancester)
{
	tid[u] 		= 	++Index;
	top[u]		= 	ancester;
	w[Index]	=	weight[u];
	if(hson[u] != -1) connect_heavy_chain(hson[u], ancester);
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == hson[u] || v == fa[u]) continue;
		connect_heavy_chain(v, v);
	}
}
int _Query_Max(int u, int l, int r)
{
	if(l == f[u].l && f[u].r == r) return f[u].max;
	if(r <= f[u].mid) return _Query_Max(L(u), l, r);
	else if(f[u].mid < l) return _Query_Max(R(u), l, r);
	else return max(_Query_Max(L(u), l, f[u].mid), _Query_Max(R(u), f[u].mid+1, r));
}
int _Query_Sum(int u, int l, int r)
{
	if(l == f[u].l && f[u].r == r) return f[u].sum;
	if(r <= f[u].mid) return _Query_Sum(L(u), l, r);
	else if(f[u].mid < l) return _Query_Sum(R(u), l, r);
	else return _Query_Sum(L(u), l, f[u].mid) + _Query_Sum(R(u), f[u].mid+1, r);
}
void push_up(int u)
{
	f[u].sum =  f[L(u)].sum + f[R(u)].sum;
	f[u].max =  max(f[L(u)].max, f[R(u)].max);
}
void build(int u, int l, int r)
{
	f[u].l = l, f[u].r = r, f[u].mid = MID(l,r);
	if(l == r) {
		f[u].max = f[u].sum = w[l];
		return ;
	}
	build(L(u), l, f[u].mid), build(R(u), f[u].mid+1, r);
	push_up(u);
}
void Update(int u, int pos, int val)
{
	if(f[u].l == f[u].r) {
		f[u].max = f[u].sum = val;
		return ;
	}
	if(pos <= f[u].mid) Update(L(u), pos, val);
	else Update(R(u), pos, val);
	push_up(u);
}
int Query_Max(int u, int v)
{
	int f1 = top[u], f2 = top[v], ans = -9999999;
	while(f1 != f2) {
		if(depth[f1] < depth[f2]) swap(f1, f2), swap(u, v);
		ans = max(ans, _Query_Max(1, tid[f1], tid[u]));
		u = fa[f1], f1 = top[u];
	}
	if(u == v) return max(ans, _Query_Max(1, tid[u], tid[u]));		//TODO
	if(depth[u] > depth[v]) swap(u, v);
	return max(ans, _Query_Max(1, tid[u], tid[v]));
}
int Query_Sum(int u, int v)
{
	int f1 = top[u], f2 = top[v], ans = 0;
	while(f1 != f2) {
		if(depth[f1] < depth[f2]) swap(f1, f2), swap(u, v);
		ans +=  _Query_Sum(1, tid[f1], tid[u]);
		u = fa[f1], f1 = top[u];
	}
	if(u == v) return ans + _Query_Sum(1, tid[u], tid[u]);		//TODO
	if(depth[u] > depth[v]) swap(u, v);
	return ans + _Query_Sum(1, tid[u], tid[v]);
}

void solve();
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		printf("Case %d:\n", ++Cas);
		solve();
	}
	return 0;
}

void solve()
{
	int u, v, query, t, op;
	scanf("%d", &n);
	init();
	for(int i = 1; i <= n; i++) scanf("%d", &weight[i]);
	for(int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		u++,v++;
		add_edge(u, v), add_edge(v, u);
	}
	find_heavy_edge(1, 1, 0);
	connect_heavy_chain(1, 1);
	build(1, 1, Index);
	scanf("%d", &query);
	while(query--) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d%d", &u, &t);
			u++;
			Update(1, tid[u], t);
		} else {
			scanf("%d%d", &u, &v);
			u++, v++;
			printf("%d\n", Query_Sum(u, v));
		}
	}
}
