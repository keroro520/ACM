/*
	树状DP  树的直径  好题  实现妙题

	题意：给一棵树，边长为1，有边权ei.w。删掉一条边e把树分成两棵新树，代价为两棵新树的直径的较大值*e.w，问最小代价。

	思路：先求树的直径。
		  如果边e不是直径上的边，那么去掉该边的毁灭值 = e的权值 * 直径长度
		  如果边e是直径上的边，那么去掉该边的毁灭值 = e的权值 * max(两颗新树的直径)，从直径两端各DP一次就可以了。

		  这里只讨论e是直径上的边的情况。
		  边e被删掉以后，我们要算两颗新树的直径。易知原树直径上的两个端点e1,e2被分在不同树上。那我们以e1,e2为根分别做一次树上DP，记录每个节点如下状态：
		      f[u].dis 以u为根的子树的最长直径。
			  f[u].fir/f[u].sec u节点的最长/次长子树长度
			  注意，以u为根的子树直径不一定经过u，所以，f[u].dis = max{ f[v].dis, f[u].fir+f[u].sec }, v is child node of u
		  仔细想想就可以知道，假设现在是以e1开始做DP的，那么f[u].dis其实就表示“删边后u点和e1不在同一棵树时，以u点为根的子树的直径”，说直白一点，就是“删掉连接u与u的父节点的这条边后，不包含e1的那棵树的直径”


		  这样，我们经过分别从e1,e2开始的DP且每次DP后计算出每条边的最大毁灭值。
*/
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		bug(x)		printf("! %d\n", x)
#define		MAXN		100005
struct Edge {
	int u, v, next, w;
} edge[MAXN*2];
struct Node {
	int dis, fir, sec;
} f[MAXN];
int head[MAXN], ans[MAXN];
bool used[MAXN];
int n, end, Max_len, edge_num, Dia;
void init()
{
	edge_num = 0;
	memset(used, false, sizeof(used));
	memset(head, -1, sizeof(head));
	memset(ans ,  0, sizeof(ans));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}
bool label(int u, int father)			//标记直径边
{
	if(u == end) return true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		if(label(v, u)) {
			used[k/2+1] = true;
			return true;
		}
	}
	return false;
}
void dfs(int u, int len,int father)		//求直径
{
	if(len > Max_len) end = u, Max_len = len;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		dfs(v, len+1, u);
	}
}

void DP(int u, int father)
{
	f[u].dis = f[u].fir = f[u].sec = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		DP(v, u);
		if(f[v].fir+1 > f[u].sec) {
			f[u].sec = f[v].fir + 1;
			if(f[u].sec > f[u].fir) swap(f[u].fir, f[u].sec);
		}
		f[u].dis = max(f[u].dis, f[v].dis);
	}
	f[u].dis = max(f[u].dis, f[u].fir + f[u].sec);
}
void calc(int u, int father)
//我觉得calc过程真是太妙了！！calc的顺序跟DP的顺序是一样的这样就保证了DP()和calc()遍历出来的序列是一模一样的，就保证了e(u,v)一定是u在前v在后。而以不同直径端点e1,e2开始DP()和calc()来遍历，得到的序列肯定是相反的！
//我觉得这是细节吧。要我写可能就直接for循环遍历了，根本没想到有这种细节。
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v, id = k/2 + 1;
		if(v == father) continue;
		calc(v, u);
		if(used[id])
			 ans[id] = max(ans[id], f[v].dis * edge[k].w);//为什么是v而不是u呢？因为我们的f[]意义为“删掉边id后不包含起始点e'的新树的
			 											  //直径”，即u与e'同一棵树，v才是与e'不同树
		else ans[id] = max(ans[id], Dia * edge[k].w);
	}
}

int main()
{
	int cases, Cas = 0, u, v, w;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		Max_len = -1;
		dfs(1, 0, 1);
		int e1 = end;
		Max_len = -1;
		dfs(end, 0, end);
		int e2 = end; 
		Dia = Max_len;

		label(e1, e1);

		DP(e1, e1);
		calc(e1, e1);
		DP(e2, e2);
		calc(e2, e2);
		int ans_ = 999999999, ansi_;
		for(int i = 1; i < n; i++) 
			if(ans_ > ans[i]) ans_ = ans[i], ansi_ = i;
		printf("Case #%d: %d\n", ++Cas,ansi_);
	}
	return 0;
}
