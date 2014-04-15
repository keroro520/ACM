/*
	题意：一张无向图，保证每个点的度不小于K，没有重边或者自环。现要求输出一个环，该环的大小不小与K+1

	思路：Tarjan在找到割点的时候判断一下是不是环，是环的话点数够不够
		  跟“圆桌会议”很像的算法

		  看题解知道有更简单的方法，这里有个性质：假设现有简单路径v1,v2...vr，这时如果vr后面无法再接下一个点了，只能说明与vr相邻的点都已经存在在这个简单路径里面了。而因为任意一个点的度>=K，加上点v，那不就是K+1啦~~
		  不过这思路的实现我没多想
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    100005
struct Edge { int v, next; } edge[MAXN * 2];
int low[MAXN], dfn[MAXN], head[MAXN], S[MAXN], ans[MAXN];
int fuck[MAXN], color[MAXN];
bool vis[MAXN * 2], in_stack[MAXN], yes[MAXN];
int n, m, edge_num, Index, K, S_top, st;

bool dye(int u, int pre, int sum, int c)		//染色法判断是不是环，染色其实只是为了判点重...	sum是点数
{
	if(color[u] != 0) {
		if(sum > K + 1 && u == st) {			//是否数目>=K+1 && 是不是以u点开头的环
			fuck[sum] = u;
			fuck[0] = sum;
			return true;
		}
		return false;
	}
	color[u] = c;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == pre || yes[v] == false) continue;
		if(dye(v, u, sum+1, 3-c)) {
			fuck[sum] = u;
			return true;
		}
	}
	return false;
}
bool judge(int u, int v)
{
	int sum = 0, x;
	do {
		x = S[--S_top];
		in_stack[x] = false;
		ans[sum++] = x;
	} while(x != v);		//最后的割地u不出来
	if(sum < K) return false;
	ans[sum++] = u;
	for(int i = 0; i < sum; i++) yes[ ans[i] ] = true, color[ ans[i] ] = 0;
	st = u;
	if(dye(u, u, 1, 1)) return true;
	for(int i = 0; i < sum; i++) yes[ ans[i] ] = false;
	return false;
}
bool Tarjan(int u)
{
	dfn[u] = low[u] = Index++;
	S[S_top++] = u;
	in_stack[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) if(!vis[k]) {
		vis[k] = vis[k^1] = true;
		int v = edge[k].v;
		if(!dfn[v]) {
			if(Tarjan(v)) return true;
			low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u]) {
				if(judge(u, v)) return true;
			}
		} else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
	}
	return false;
}
void init()
{
	edge_num = S_top = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
	memset(vis, false, sizeof(vis));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int main()
{
	int u, v;
	scanf("%d%d%d", &n, &m, &K);
	init();
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	for(int i = 1; i <= n; i++) if(!dfn[i]) if(Tarjan(i)) break;
	printf("%d\n", fuck[0]-1);
	for(int i = 1; i < fuck[0]; i++) printf("%d ", fuck[i]);
	puts("");
	return 0;
}
