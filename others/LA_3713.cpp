/*
	2-SAT  图论  好题   lrj版本的2-sat

	题意：
	思路：构图好神奇...
		  写了个lrj版的2-sat


	直接贴别人的了
		"		
		给定n个宇航员的年龄，平均年龄为 ave，根据下列要求分配任务：
		
		B任务只能分配给年龄<ave的宇航员；
		
		A任务只能分配给年龄>=ave的宇航员；
		
		C任务可以任意分配。
		
		给定m组互相憎恨的宇航员，要求他们不能分配到同一个任务。能否存在这样的一组任务分配。
		
		每个宇航员都只能分配两种任务中的一种：A或C（年龄大于等于ave），B或C（年龄小于ave)，那么为每个宇航员设立一个变量xi，xi为0表示分配C任务，为1则分配A或B（根据年龄）。
		
		对于互相仇恨的宇航员，如果属于同一类型，那么应满足xi∨xj，非xi∨非xj，表示xi和xj一真一假；如果类型不同只需要满足不同时分配C任务就可：xi∨xj。
		"
*/
#include <stdio.h>
#include <string.h>
#define			MAXN		400005

struct Edge {
	int v, next;
} edge[MAXN];
int    head[MAXN], color[MAXN], S[MAXN];
double age[MAXN];
int    n, edge_num, top;

inline		int		hash(int x) 	{ return  x <= n ? x + n : x - n; }

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(color, 0, sizeof(color));
}
bool dfs(int u)
{
	if(color[hash(u)]) return false;
	if(color[u]) return true;
	color[u] = 1;
	S[top++] = u;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfs(v)) return false;
	}
	return true;
}
bool two-sat()
{
	for(int i = 1; i <= n; i++)
		if(!color[i] && !color[hash(i)]) {
			top = 0;
			if(!dfs(i)) {
				while(top) color[ S[--top] ] = 0;
				if(!dfs(hash(i))) return false;
			}
		}
	return true;
}
int main()
{
	int u, v, m;
	while(scanf("%d %d", &n, &m) != EOF && (n || m) ) {
		init();
		double ava = 0;
		for(int i = 1; i <= n; i++) scanf("%lf", &age[i]), ava += age[i];
		ava /= n;
		while(m--) {
			scanf("%d %d", &u, &v);
			if((age[u] >= ava && age[v] >= ava) || (age[u] < ava && age[v] < ava)) {
				add_edge(u, hash(v)), add_edge(v, hash(u));
			}
			add_edge(hash(u), v); 			//这里我一直以为是 else ，wa到掉渣
			add_edge(hash(v), u);
		}

		if(!two-sat()) { puts("No solution."); continue; }
		for(int i = 1; i <= n; i++)
			if(color[i]) puts(age[i] >= ava ? "A" : "B");
			else 		 puts("C");
	}
	return 0;
}
