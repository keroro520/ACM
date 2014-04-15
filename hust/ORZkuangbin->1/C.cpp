/*
	树转线性 简单题
*/
#include <stdio.h>
#include <string.h>
#define			MAXN			50005
#define			L(x)			((x) << 1)
#define			R(x)			(((x) << 1) + 1)
#define			MID(x,y)		(((x) + (y)) >> 1)
struct Edge {
	int v, next;
} edge[MAXN];
struct Node {
	int l, r, task;
} f[MAXN * 4];
int head[MAXN], in[MAXN], out[MAXN];
bool employee[MAXN];
int  n, edge_num, Index;

void Update(int u, int l, int r, int task);
void init()
{
	edge_num = Index = 0;
	memset(employee, false, sizeof(employee));
	memset(head,        -1, sizeof(head));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}

void predfs(int u)
{
	in[u] = ++Index;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		predfs( v );
	}
	out[u] = Index;
}
void push_down( int u )
{
	int mid = MID(f[u].l, f[u].r);
	Update(L(u), f[u].l, mid, f[u].task), Update(R(u), mid+1, f[u].r, f[u].task);
	f[u].task = -1;
}
void build(int u, int l, int r)
{	
	f[u].l = l, f[u].r = r, f[u].task = -1;
	if(l == r) return ;
	int mid = MID(l, r);
	build(L(u), l, mid), build(R(u), mid+1, r);
}
int Query(int u, int pos)
{
	if(f[u].l == f[u].r) return f[u].task;
	if(f[u].task != -1)  push_down( u );
	int mid = MID(f[u].l, f[u].r);
	if(pos <= mid) return Query(L(u), pos);
	else 		   return Query(R(u), pos);
}
void Update(int u, int l, int r, int task)
{
	if(l == f[u].l && f[u].r == r) {
		f[u].task = task;
		return ;
	}
	if(f[u].task != -1) push_down( u );
	int mid = MID(f[u].l, f[u].r);
				//if(task == 2) printf("! %d %d  %d\n", f[u].l, f[u].r , mid);
	if(r <= mid)     Update(L(u), l, r, task);
	else if(mid < l) Update(R(u), l, r, task);
	else Update(L(u), l, mid, task), Update(R(u), mid+1, r, task);
}
int main()
{
	int cases, Cas = 0, u, v, x, y, query;  char op[10];
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d %d", &u, &v);
			add_edge(v, u);
			employee[u] = true;
		}
		int boss = 1;
		for(int i = 1; i <= n; i++) if(!employee[i]) { boss = i; break; }
		predfs(boss);
		build(1, 1, n);

		printf("Case #%d:\n", ++Cas);
		scanf("%d", &query);
		while(query--) {
			scanf("%s", op);
			if(op[0] == 'C') {
				scanf("%d", &x);
				printf("%d\n", Query( 1, in[x] ));
			} else {
				scanf("%d %d", &x, &y);
				Update(1, in[x], out[x], y);
			}
		}
	}
	return 0;
}
