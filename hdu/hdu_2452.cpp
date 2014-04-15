/*
	记忆化搜索  DP  博弈  好题  启发题
	题意：一个有向无环点权图，只有一个入度为0的点st，且点st能到达所有点。两个人移动同一个棋子从st点出发，轮流选择下一步的路线，第一次由A选，第二次由B选，第三次A选...需要注意的是，只有一个棋子，只是棋子每一步的路线选择轮流由A，B决定而已。
		  该棋子最终会停留在一个点，算作结束旅程。该旅程路线上的点权和作为旅程的价值。
		  现在，A想要旅程价值尽量大，B想要旅程价值尽量小，问有没有可能使得该旅程价值 >= 常量F ? "Victory" : "Glory" ?

	思路：dp[u][0] 表示当前路线权在A手上，到达点u的最优值
		  一开始我是按拓扑序dp一遍，不断更新各点的dp[][]值，狂WA无下限
		  后来发现按拓扑序dp确实不能保证“路线轮流选择”这个条件，即使我有分情况进行状态转移，但这个还是不能保证最后ans = max(ans, dp[t][0], dp[t][1])的正确性。   顺便说一下，我的错误解法是以st为起点，每到一个出度为0的点我都更新一下最优旅程价值ans
		  意识到这一点对我启发很大，想了很久也不能补救“路线轮流选择”这一问题----看起来好像拓扑序都完美解决了，其实只是假象=_=

		  学习了记忆化搜索的写法。
		  因为是搜索，所以我们可以加个参数cur 说明当前选择权在A手上还是在B手上。这样就简单巧妙地解决的我的问题。
		  重要的一点是，记忆化搜索实际上是“从后往前”递归回来的，也就是说，由后继节点的dp值推理出当前点的dp值，但这里的“从后往前”又是我们从前往后递归下去的...又因为我们一直有选择权参数cur保证，所以转移的时候可以直接按情况转移，遇到分叉口也没事。


		  为什么我的拓扑序解法不能补救呢？因为我是以入度为0的st为起始点，是“从前往后”更新各个后继节点，这种解法遇到分叉口就跪了有木有！！ 那我把边逆向再拓扑不就行了？不行！再看看正解记忆化搜索，它是“从前往后请求需要的状态，然后到了叶子节点就递归回来，就可以知道我希望知道的状态了，类似于client-server模型，且client有把控制参数(cur)一起发送到server”，但拓扑的话就是纯递推模型。


	启发：拓扑dp与记忆化搜索的区别
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
#define		INF			999999999
struct Edge {
	int v, next;
} edge[MAXN * MAXN / 2];
int  head[MAXN], val[MAXN], dp[MAXN][2];
bool in[MAXN]; 
int n, m, edge_num;

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1,    sizeof(head));
	memset(in,   false, sizeof(in));
	memset(dp,   -1,    sizeof(dp));
}
int dfs(int u, int cur)
{
	if(dp[u][cur] != -1) return dp[u][cur];
	if(head[u] == -1) return dp[u][cur] = val[u];

	int _max = -INF, _min = INF;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(cur) _min = min(_min, dfs(v, !cur) + val[u]);
		else    _max = max(_max, dfs(v, !cur) + val[u]);
	}
	if(cur) return dp[u][cur] = _min;
	else 	return dp[u][cur] = _max;
}
int main()
{
	int F, u, v;
	while(scanf("%d %d %d", &n, &m, &F) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
		while(m--) {
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			in[v] = true;
		}
		for(int i = 1; i <= n; i++) 
			if(!in[i]) puts(dfs(i, 0) >= F ? "Victory" : "Glory");
	}
	return 0;
}
