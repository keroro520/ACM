/*
	树转线性结构  LCA   树形结构转线性结构经典题

	题意：给你一棵树，现在有两种操作，一个是修改u到v路径上点的权值(全部增加一个值)，另外一个是查询一个点的点权。

	思路：考虑将树形结构转化为线性结构，记录l[x]和r[x]表示先序遍历时开始访问x的时间戳l[x]和结束访问x的时间戳r[x]（以1 为根）
		  对于修改(u,v)路径上的点权操作，我们将[ 1, l[u] ]和[ 1, l[v] ]区间上的值全都加上w，在[1, l[ LCA(u,v) ]]和[1, l[LCA(u,v)]-1]区间减去w，
		  然后查询点u则回答weight[u] + Query(l[u], l[u]) - Q(r[u], r[u])



	摘抄：http://blog.csdn.net/lyhypacm/article/details/6734748
		  我们现在要做的是更新区间查找点，利用树状数组维护括号序列的增量(注意这里是增量，初始化全部为0)，我们这么考虑，对于每一个更新操作，假设更新的是u到v路径上的点权全部加w，那么对于u，我们做的是将1到l(u)位置上的元素全部加w，对于v我们做类似的处理。
	你会发现，更新1到l(u)上的元素值的时候，对于一个结点x,如果x是u的祖先，那么x一定是左括号被增加了w，如果x不是其祖先，比如说u为4的时候，3不是4的祖先，那么x一定是左右括号都被增加了w。通过这个例子，大家应该都知道怎么做了吧，对于每次更新，我们将1到l(u)以及1到l(v)元素全部加w，然后将u和v的lca的左括号的位置找出来，假设为l，那么1到l-1的全部元素减去2w，因为我们要更新的是路径上的值，这时候我们会发现lca会被更新了两次，所以lca对应的左括号位置元素减w，这样我们就完成了一次更新操作。
	对于查询操作，看了上面一段话，应该会知道怎么做了，一个点的点权增加量就是等于其左括号的增加量减去右括号的增加量，这样我们就可以利用一个树状数组配合在线LCA在O(NlogN)的时间内得到所有的查询的答案。

*/
//hdu 3966
#pragma comment(linker, "/STACK:200000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			bug(x)		printf("# %d\n", x)
#define			debug		printf("!\n")
#define			MID(l,r)	(((l) + (r)) >> 1)
#define			L(x)		((x) << 1)
#define			R(x)		(((x) << 1) + 1)
#define			MAXN		50005 * 2		//不乘2的话互RE，不明白
#define			ANC_SIZE	28
int head[MAXN], l[MAXN], r[MAXN], weight[MAXN], anc[MAXN][ANC_SIZE], depth[MAXN];
struct Edge {
	int v, next;
} edge[MAXN * 2];
struct Node {
	int l, r, lazy, num;
} f[MAXN * 2 * 4];
int edge_num, n, Time;
void init()
{
	memset(head, -1, sizeof(head));
	memset(anc,  -1, sizeof(anc));
	edge_num = Time = 0;
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void predfs(int u, int father)
{
	l[u] = ++Time;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		predfs(v, u);
	}
	r[u] = ++Time;
}
void preLCA(int u, int father, int dep)
{
	depth[u] = dep+1;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		anc[v][0] = u;
		for(int i = 1; i < ANC_SIZE; i++) 
			anc[v][i] = anc[ anc[v][i-1] ][i-1];

		preLCA(v, u, dep+1);
	}
}
int LCA(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);
	int k = depth[u] - depth[v];
	for(int i = 0; i < ANC_SIZE; i++) if(k & (1 << i)) {
		u = anc[u][i];
	}
	if(u == v) return u;
	for(int i = ANC_SIZE - 1; i >= 0; i--) 
		if(anc[u][i] != anc[v][i]) 
			u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}
void build(int u, int l, int r);
int  Query(int u, int l, int r);
void Update(int u, int l, int r, int val);
int main()
{
	int query, u, v, w;
	char op[10];
	while(scanf("%d%*d%d", &n, &query) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &weight[i]);
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		predfs(1, 0);
		preLCA(1, 0, 0);
		build(1, 1, Time);
		while(query--) {
			scanf("%s", op);
			if(op[0] == 'I' || op[0] == 'D') {
				scanf("%d%d%d", &u, &v, &w);
				if(op[0] == 'D') w = -w;
				Update(1, 1, l[u], w), Update(1, 1, l[v], w);
				int lca = LCA(u, v);
				if(l[lca] > 1) Update(1, 1, l[lca]-1, -w);
				Update(1, 1, l[lca], -w);
			} else {
				scanf("%d", &u);
				printf("%d\n", weight[u] + Query(1, l[u], l[u]) - Query(1, r[u], r[u]));
			}
		}
	}
	return 0;
}
void build(int u, int l, int r)
{
	f[u].l = l, f[u].r = r, f[u].lazy = f[u].num = 0;
	if(l == r) return ;
	int mid = MID(l, r);
	build(L(u), l, mid), build(R(u), mid+1, r);
}
void put_up(int u)
{
	f[u].num = f[L(u)].num + f[R(u)].num;
}
void push_down(int u)
{
	int mid = MID(f[u].l, f[u].r);
	Update(L(u), f[u].l, mid, f[u].lazy), Update(R(u), mid+1, f[u].r, f[u].lazy);
	f[u].lazy = 0;
}
void Update(int u, int l, int r, int val)
{
	if(l == f[u].l && f[u].r == r) {
		f[u].lazy += val;
		f[u].num  += (r - l + 1 ) * val;
		return ;
	}
	if(f[u].lazy) push_down(u);
	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) Update(L(u), l, r, val);
	else if(mid < l) Update(R(u), l, r, val);
	else Update(L(u), l, mid, val), Update(R(u), mid+1, r, val);
	put_up(u);
}
int  Query(int u, int l, int r)
{
	if(l == f[u].l && r == f[u].r) {
		return f[u].num;
	}
	if(f[u].lazy) push_down(u);
	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) return Query(L(u), l, r);
	else if(mid < l) return Query(R(u), l,r);
	else return Query(L(u), l, mid) + Query(R(u), mid+1, r);
}
