/*
	树链剖分模板题
	题意：一棵树，两种操作，一是修改边i的权值，二是问(u,v)之间最大的边权

	思路：树链剖分。我是把边权转为点权做的，对于边(u,v,w)，假设u是v的父节点，则weight[v] = w. 这样做需要注意的一点是，题目询问(u,v)的最大边权即询问(son[u], v)的最大点权，而不是(u,v)的最大点权。所以Query()的最后一句是 max(ans, _Query(1, tid[son[u]], tid[v]));
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN		10005
#define		L(x)		((x) << 1)
#define		R(x)		(((x) << 1) | 1)
#define		MID(l,r)	(((l) + (r)) >> 1)
struct Edge {
	int u, v, next, w;
} edge[MAXN * 2];
struct Segmemt_Tree {
	int l, r, max;
} f[MAXN * 4];
int head[MAXN], tid[MAXN], weight[MAXN], son[MAXN], size[MAXN], depth[MAXN], fa[MAXN], top[MAXN], F[MAXN];
int n, edge_num, Index;

int _Query(int u, int l, int r);
int Query(int u, int v);
void build(int u, int l, int r);
void Update(int e, int val);
void init()
{
	edge_num = 0;
	Index    = 0;
	memset(head, -1, sizeof(head));
	memset(son,  -1, sizeof(son));
	memset(size,  0, sizeof(size));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void find_heavy_edge(int u, int father, int dep)
{
	depth[u] = dep;
	fa[u]    = father;
	size[u]  = 1;
	int Max = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		find_heavy_edge(v, u, dep + 1);
		weight[v] = edge[k].w;				// 我想把边权化为点权
		size[u] += size[v];
		if(size[v] > Max) {
			Max = size[v], son[u] = v;
		}
	}
}
void connect_heavy_chain(int u, int ancester)
{
	tid[u] = ++Index;
	F[Index] = u;				//把剖分后的序列当作欧拉序列的话，那F[]就是对应的欧拉序列
	top[u] = ancester;			//top[u]表示u所在重链的头
	if(son[u] != -1) connect_heavy_chain(son[u], ancester);
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa[u]  || v == son[u]) continue;
		connect_heavy_chain(v, v);
	}
}
int Query(int u, int v)
{
	int f1 = top[u], f2 = top[v], ans = 0;
	while(f1 != f2) {
		if(depth[f1] < depth[f2]) swap(f1, f2), swap(u, v);
		ans = max(ans, _Query(1, tid[f1], tid[u]));
		u = fa[f1], f1 = top[u];
	}
	if(u == v) return ans;
	if(depth[u] > depth[v]) swap(u, v);
	return max(ans, _Query(1, tid[son[u]], tid[v]));
}

int main()
{
	int cases, u, v, w, e;
	char op[10];
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		weight[1] = 0, fa[1] = 0, depth[1] = 0;
		find_heavy_edge(1, 1, 0);
		connect_heavy_chain(1, 1);
		build(1, 1, Index);
		while(scanf("%s", op) , op[0] != 'D') {
			if(op[0] == 'C') {
				scanf("%d%d", &e, &w);
				Update(e, w);
			} else {
				scanf("%d%d", &u, &v);
				printf("%d\n", Query(u, v));
			}
		}
	}
	return 0;
}
void push_up(int u)
{
	f[u].max = max(f[L(u)].max, f[R(u)].max);
}
void _Update(int u, int pos, int val)
{
	if(f[u].l == f[u].r) {
		f[u].max = val;
		return ;
	}
	int mid = MID(f[u].l, f[u].r);
	if(pos <= mid) _Update(L(u), pos, val);
	else _Update(R(u), pos, val);
	push_up(u);
}
int _Query(int u, int l, int r)
{
	if(l == f[u].l && f[u].r == r) return f[u].max;
	int mid = MID(f[u].l, f[u].r);

	if(r <= mid) return _Query(L(u), l, r);
	else if(mid < l) return _Query(R(u), l, r);
	else return max(_Query(L(u), l, mid), _Query(R(u), mid+1, r));
}
void Update(int e, int val)
{
	int u = edge[(e-1)*2].u, v = edge[(e-1)*2].v;
	if(fa[u] == v) swap(u, v);
	_Update(1, tid[v], val);
}
void build(int u, int l, int r)
{
	f[u].l = l, f[u].r = r;
	if(l == r) {
		f[u].max = weight[ F[l] ];
		return ;
	}
	int mid = MID(l, r);
	build(L(u), l, mid), build(R(u), mid+1, r);
	push_up(u);
}
