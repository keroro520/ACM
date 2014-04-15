/*
	差分约束  好题
	题意：问一个图<G,E>是否满足下列两个条件(ai表示i点的权值，<i,j>表示边i-j)：
			<1> 所有 |ai| < T 
			<2> (i,j) ∈ E     <====>    |ai - aj| >= T

	思路：我一开始是想直接判是否有奇环就可以了，后面看题解才知道题意没搞对。题意就不能写清楚明白点吗！  对于题目的第二个条件，注意符号"<====>" 是表示"充要"，我一开始就只理解为"推出===>"。什么意思呢？如果(i,j) ∈ E，那要符合条件|ai - aj| >= T；反之如果(i,j) ∉ E，则要|ai - aj| < T.
		  
		  染色法判断一下奇环，有奇环则No. 
		  染色过程中我们默认color[x] == 0的x点点权为正，coloe[x] == 1的ax点点权为负。
		  然后差分约束判断是否满足条件。
		  对于e(i,j)属于E，并且假设顶点ai为正，则ai - aj >= T   ----> aj <= ai - T
		  对于e(i,j)不属于E，并且假设顶点ai为正，则ai - aj < T  ----> ai < aj + T ----> ai <= aj + T - 1
		  以a0为参照点，若ai为正，则加边<i, a0, -T>,<a0, i, 0)；若ai为负，则加边<a0, ai, T-1>,<ai, a0, 0>
		  SPFA看看是否有负圈，有则No。




	代码：if(color[i] == color[j]) continue;		//去掉这句也对	因为ai,aj同号的话直接可以肯定(ai,aj)满足条件了
		  color[i] == color[j]即ai和aj同号，假设ai和aj为正，则ai - aj < T肯定满足，加上我们在染色之后，若i,j颜色相同，则说明i,j不相连，所以|ai - aj| >= T肯定不满足。说明color[i]==color[j]这种情况可以忽略，因为它一定合法。

*/
//一个看不懂的神奇的做法：http://blog.csdn.net/yihuikang/article/details/10284595
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
#define		MAXN		305
#define		T 			(400)
typedef pair<int, int> PII;
class Edge {
	public : int u, v, next, w;
	Edge () { }
	Edge (int u, int v, int next, int w) : u(u), v(v), next(next), w(w) { }
} edge[MAXN * MAXN];
int n, edge_num;
int head[MAXN], map[MAXN][MAXN];
int color[MAXN], dis[MAXN], times[MAXN];
bool inque[MAXN];

void add_edge(int u, int v, int w)
{
	Edge tmp = Edge(u, v, head[u], w);
	edge[edge_num] = tmp;
	head[u] = edge_num++;
}
void Find(int u, int c)
{
	if(color[u] != -1) return ;
	color[u] = c;
	for(int k = head[u]; k != -1; k = edge[k].next) Find(edge[k].v, !c);
}
bool dye()
{
	memset(color, -1, sizeof(color));
	for(int i = 1; i <= n; i++) if(color[i] == -1) Find(i, 0);
	for(int i = 0; i < edge_num; i++) if(color[edge[i].u] == color[edge[i].v]) return false;
	return true;
}
void init()
{
	memset(head, -1, sizeof(head));
	edge_num = 0;
}
bool SPFA(int s)			//堆优化的SPFA
{
	memset(times, 0, sizeof(times));
	memset(dis, 127, sizeof(dis));
	memset(inque, false, sizeof(inque));
	dis[s] = 0;
	priority_queue< PII > Q;
	Q.push(PII(0, s));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		inque[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(dis[v] > dis[u] + edge[k].w) {
				dis[v] = dis[u] + edge[k].w;
				if(!inque[v]) {
					inque[v] = true;
					Q.push(PII(dis[v], v));
					if(++times[v] > n) return false;
				}
			}
		}
	}
	return true;
}
bool judge()				//建图
{
	init();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			if(color[i] == color[j]) continue;		//去掉这句也对	因为ai,aj同号的话直接可以肯定(ai,aj)满足条件了
			int x = i, y = j;
			if(color[i] == 1) swap(x, y);			//保证ax >= 0
			if(map[x][y]) add_edge(x, y, -T);
			else add_edge(y, x, T-1);
		}
	for(int i = 1; i <= n; i++) 
		if(color[i] == 0) {
			add_edge(0, i, T-1);
			add_edge(i, 0, 0);	// ???
		} else {
			add_edge(i, 0, T-1);
			add_edge(0, i, 0);	// ???
		}
	return SPFA(0);
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) scanf("%1d", &map[i][j]);
		for(int i = 1; i <= n; i++)
			for(int j = i+1; j <= n; j++) if(map[i][j]) 
				add_edge(i, j, 0), add_edge(j,i,0);
		if(!dye()) {
			puts("No");
			continue;
		}
		puts(judge() ? "Yes" : "No");
	}
	return 0;
}
