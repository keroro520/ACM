/*
	题意：给你一棵树，现在有两种操作，一个是修改u到v路径上点的权值(全部增加一个值)，另外一个是查询一个点的点权。

	思路：我们现在要做的是更新区间查找点，利用树状数组维护括号序列的增量(注意这里是增量，初始化全部为0)，我们这么考虑，对于每一个更新操作，假设更新的是u到v路径上的点权全部加w，那么对于u，我们做的是将1到l(u)位置上的元素全部加w，对于v我们做类似的处理。
	你会发现，更新1到l(u)上的元素值的时候，对于一个结点x,如果x是u的祖先，那么x一定是左括号被增加了w，如果x不是其祖先，比如说u为4的时候，3不是4的祖先，那么x一定是左右括号都被增加了w。通过这个例子，大家应该都知道怎么做了吧，对于每次更新，我们将1到l(u)以及1到l(v)元素全部加w，然后将u和v的lca的左括号的位置找出来，假设为l，那么1到l-1的全部元素减去2w，因为我们要更新的是路径上的值，这时候我们会发现lca会被更新了两次，所以lca对应的左括号位置元素减w，这样我们就完成了一次更新操作。
	对于查询操作，看了上面一段话，应该会知道怎么做了，一个点的点权增加量就是等于其左括号的增加量减去右括号的增加量，这样我们就可以利用一个树状数组配合在线LCA在O(NlogN)的时间内得到所有的查询的答案。


	摘自：http://blog.csdn.net/lyhypacm/article/details/6734748
*/
#pragma comment(linker, "/STACK:200000000")
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define			debug			printf("!\n")
#define			ANC_SIZE		20
#define			MAXN			50005 * 2
#define			L(x)			((x) << 1)
#define			R(x)			(((x) << 1) | 1)
#define			MID(l,r)		(((l) + (r)) >> 1)
struct Edge {
	int v, next;
} edge[MAXN * 2];
struct Node {
	int l, r, num, lazy;
} f[MAXN * 4];
int head[MAXN], depth[MAXN], anc[MAXN][ANC_SIZE], l[MAXN], r[MAXN], a[MAXN], b[MAXN * 2], pos[MAXN];
int edge_num, Index;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(anc, -1, sizeof(anc));					//这个初始化在多组数据的时候是不是很重要？
}
void add_edge(int u, int v)
{	
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int LCA(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);
	int k = depth[u] - depth[v];
	for(int i = 0; i < ANC_SIZE; i++) if(k & (1 << i)) {
		u = anc[u][i];
	}
	if(u == v) return u;
	for(int i = ANC_SIZE - 1; i >= 0; i--) {
		if(anc[u][i] != anc[v][i]) 
			u = anc[u][i], v = anc[v][i];
	}
	return anc[u][0];
}
void predfs(int u, int fa, int dep)
{
	anc[u][0] = fa;				
	for(int i = 1; i < ANC_SIZE; i++) 			//看来要记住树上的RMQ初始化是放在这里的。
		anc[u][i] = anc[ anc[u][i-1] ][i-1];

	depth[u] = dep;
	l[u] = Index;
	b[Index++] = 0;//a[u];
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		predfs(v, u, dep+1);
	}
	r[u] = Index;
	b[Index++] = 0;//-a[u];
}
void build_tree(int u, int l, int r)
{
	f[u].l = l, f[u].r = r, f[u].lazy = 0;
	if(l == r) {
		f[u].num = b[u];
		pos[r] = u;
		return ;
	}
	int mid = MID(l, r);
	build_tree(L(u), l, mid), build_tree(R(u), mid+1, r);
}
void push_down(int u)
{
	f[L(u)].lazy += f[u].lazy;
	f[R(u)].lazy += f[u].lazy;
	f[u].lazy = 0;
}
void Update(int u, int r, int val)
{
	if(f[u].l > r) return ;
	if(r == f[u].r) {
		f[u].lazy += val;
		return ;
	}
	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) Update(L(u), r, val);
	else Update(L(u), mid, val), Update(R(u), r, val);
}
int Query(int u, int pos)
{
	if(f[u].l == f[u].r && f[u].r == pos) {
		if(f[u].lazy) f[u].num += f[u].lazy, f[u].lazy = 0;
		return f[u].num;
	}
	//if(f[u].l == f[u].r) printf("oh no !  (%d   %d   pos=%d)\n", f[u].l, f[u].num, pos);
	if(f[u].lazy) push_down(u);
	int mid = MID(f[u].l, f[u].r);
	if(pos <= mid) return Query(L(u), pos);
	else if(pos <= r) return Query(R(u), pos);
	else return 0;
}
int main()
{
	int n, query, u, v, w; 
	char op[10];
	while(scanf("%d%*d%d", &n, &query) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <  n; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		Index = 1;
		predfs(1, -1, 0);
		Index--;
		build_tree(1, 1, Index);
		while(query--) {
			scanf("%s", op);
			if(op[0] == 'I' || op[0] == 'D') {
				scanf("%d%d%d", &u, &v, &w);
				if(op[0] == 'D') w = -w;
				Update(1, l[u], w), Update(1, l[v], w); 
				int lca = LCA(u, v);
				Update(1, l[lca], -w);
				if(lca != 1) Update(1, l[lca]-1, -w);
			} else {
				scanf("%d", &u);
				//printf("###   (%d %d %d   %d)\n", u, l[u], pos[l[u]], f[pos[l[u]]]);
				printf("%d\n", a[u] + Query(1, l[u]) - Query(1, r[u]));
			}
		}
	}
	return 0;
}
