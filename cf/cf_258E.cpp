/*
	树转线性  好题
	题意：题目：给出一棵树，每次操作给出两个结点a,b，表示将以a,b为根的两棵子树的所有结点，都加入一个相同的数i，i表示操作序号。
	然后查询所有的点，和自己至少有1个相同数字的结点有多少个

	思路：一开始在树上各种乱搞，结果还是失败了。
		  
		  其实一看到这种树上RMQ的问题应该第一反应就是树转线性、树链剖分什么的，我是傻逼吗>M<..
		  得到树的先序dfs序列后，对子树操作就是对一个区间操作。再看看题意，只要求“有一个相同”就可以，也就是说如果我们把一个操作看作对一个区间加一个数值，那么询问就是问[1,n]内有多少个add[]不为0的数。
		  还是按树的先序dfs更新维护线段树，每次查询有多少个点被覆盖就行了

		  个人觉得维护线段树那部分代码还是挺精彩挺妙的！我是自己写不出来，然后看题解上的，特别是push_up()
*/
//codeforce 258E  http://codeforces.com/problemset/problem/258/E
#include <stdio.h>
#include <string.h>
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
struct Edge {
	int v, next;
} oper[MAXN*4], edge[MAXN*2];
struct Seg_Tree {
	int l, r, sum, lazy;
} f[MAXN << 2];
int head[MAXN], node[MAXN], cnt[MAXN], in[MAXN], out[MAXN];
int n, edge_num, Index;
void push_up(int u)
{
	if(f[u].lazy) {
		f[u].sum = f[u].r - f[u].l + 1; 
	} else {
		if(f[u].l == f[u].r) f[u].sum = 0;
		else f[u].sum = f[L(u)].sum + f[R(u)].sum;		//妙呀...
	}
}
void Update(int u, int l, int r, int val)
{
	if(l == f[u].l && f[u].r == r) {		//妙	//这是树dfs后的序列喔~
		f[u].lazy += val;
		push_up(u);
		return ;
	}
	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) Update(L(u), l, r, val);
	else if(mid < l) Update(R(u), l, r, val);
	else Update(L(u), l, mid, val), Update(R(u), mid+1, r, val);
	push_up(u);
}
void calc(int u, int father)
{
	for(int k = node[u]; k != -1; k = oper[k].next) {
		int v = oper[k].v;
		Update(1, in[v], out[v], 1);
	}
	cnt[u] = f[1].sum;
	if(cnt[u] > 0) cnt[u]--;

	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v != father) calc(v, u);
	}
	for(int k = node[u]; k != -1; k = oper[k].next) {
		int v = oper[k].v;
		Update(1, in[v], out[v], -1);
	}
}
void predfs(int u, int father)
{
	in[u] = ++Index;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v != father) predfs(v, u);
	}
	out[u] = Index;
}
int main()
{
	int query, u, v;
	scanf("%d%d", &n, &query);
	
	init();
	for(int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	predfs(1, 1);
	build(1, 1, Index);
	edge_num = 0;
	for(int i = 0; i < query; i++) {
		scanf("%d%d", &u, &v);
		add_oper(u, v), add_oper(v, u), add_oper(u, u), add_oper(v, v);		//
	}
	calc(1, 1);
	for(int i = 1; i <= n; i++) printf("%d%c", cnt[i], i == n ? '\n' : ' ');
}
void init()
{
	edge_num = Index = 0;
	memset(head, -1, sizeof(head));
	memset(node, -1, sizeof(node));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u]; 
	head[u] = edge_num++;
}
void add_oper(int u, int v)
{
	oper[edge_num].v = v, oper[edge_num].next = node[u]; 
	node[u] = edge_num++;
}

void build(int u, int l, int r)
{
	f[u].l = l, f[u].r = r, f[u].lazy = 0, f[u].sum = 0;
	if(l == r) return ;
	int mid = MID(l, r);
	build(L(u), l, mid), build(R(u), mid+1, r);
}
