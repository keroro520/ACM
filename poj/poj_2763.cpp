/*
	LCA+RMQ  树转线性   好题 

	题意：一棵无根树，两种操作，一是修改某一条边的权值，二是查询(u,v)的路径长度

	思路：如果没有修改边权的操作，那就是简单的LCA问题了。我们用dis[u]表示根到u节点的距离， 则(u,v)的路径长度为dis[u] + dis[v] - 2*dis[LCA(u,v).
		  现在加入动态操作之后，如果修改边e(x,y)，设x是y的父节点，那么以y为根的子树的dis值都要发生改变。容易想到先转为欧拉序列，再用树状数组或者线段树来维护。其实想到“改e(x,y)，就是改以y为根的子树的所有点权”这一点就容易想到转成欧拉序列再以RMQ的形式维护了。


		  先把树转为欧拉序列，将LCA问题转化成RMQ问题，其中F[]表欧拉序列，level[]表深度序列，in[]/out[]表开始/结束访问时间戳，这样，修改边e(x,y)，处于(in[v], out[v])这个时间段的所有节点的dis值都改变，因为其实处于这个时间段的就是以y为根的子树的节点，Update(in[y], delta), Update(out[v]+1, -delta).

	
	题解blog: http://blog.csdn.net/scorpiocj/article/details/6576456
	树转线性结构：论文 《RMQ与LCA问题》郭华阳
				  blog: http://blog.csdn.net/lyhypacm/article/details/6734748
	被一个愚蠢的错误卡了一天...最后还是对拍找出来的...不过也帮助我学会了树的数据生成。
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			debug			printf("!\n")
#define			bug(x)			printf("# %d\n", x)
#define			low(x)			((x) & (-(x)))
#define			MAXN			100005 * 2
#define			ANC_SIZE		22
struct Edge {
	int u, v, next, w;
} edge[MAXN * 2];
int head[MAXN], anc[MAXN*2][ANC_SIZE], F[MAXN*2], in[MAXN], out[MAXN], level[MAXN*2], dis[MAXN], c[MAXN*2];
int edge_num, Time, n;

void init()
{
	Time = edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(anc,  -1, sizeof(anc));
	memset(c,     0, sizeof(c));
	memset(in,    0, sizeof(in));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].u = u, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void predfs(int u, int father, int dep)
{
	in[u] = ++Time ;
	F[Time] = u;		//欧拉序列
	level[Time] = dep;	//深度序列
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		dis[v] = dis[u] + edge[k].w;
		predfs(v, u, dep+1);
		F[++Time] = u, level[Time] = dep;
	}
	out[u] = Time;
}
void init_RMQ()
{
	for(int i = 1; i <= Time; i++) anc[i][0] = i;		//RMQ的ST初始化跟LCA的初始化不一样耶//这是对欧拉序列的RMQ初始化
	for(int j = 1; (1 << j) <= Time; j++)
		for(int i = 1; i + (1 << j) - 1 <= Time; i++)
			if(level[ anc[i][j-1] ] < level[ anc[i + (1 << (j-1))][j-1] ])
				anc[i][j] = anc[i][j-1];
			else anc[i][j] = anc[i + (1 << (j-1))][j-1];
}
void Update(int pos, int val)
{
	while(pos <= Time) {
		c[pos] += val;
		pos += low(pos);
	}
}
int  Sum(int pos)
{
	int sum = 0;
	while(pos) {
		sum += c[pos];
		pos -= low(pos);
	}
	return sum;
}
int Query(int u, int v)
{
	int mx_d = max(in[u], in[v]), mi_d = min(in[u], in[v]), k = (int)(log((mx_d - mi_d + 1)*1.0)/log(2.0));
	int lca;
	if(level[ anc[mx_d + 1 - (1 << k)][k] ] < level[ anc[mi_d][k] ]) 	//细节要注意
		lca = F[ anc[mx_d + 1 - (1 << k)][k] ];		//细节，是F[]  要区分代码里面RMQ的最小值和树上的LCA
	else lca = F[ anc[mi_d][k] ];
	return dis[u] + dis[v] - 2 * dis[lca] + Sum(in[u]) + Sum(in[v]) - 2 * Sum(in[lca]);
}
int main()
{
	int query, S, T, op ,road, len, delta, u, v, w;
	while(scanf("%d%d%d", &n, &query, &S) != EOF) {
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		dis[1] = 0;
		predfs(S, 0, 0);		//TODO    有关系吗?
		init_RMQ();

		while(query--) {
			scanf("%d", &op);
			if(op == 0) {
				scanf("%d", &T);
				printf("%d\n", Query(S, T));
				S = T;
			} else {
				scanf("%d%d", &road, &len);
				//delta = len - edge[road * 2 - 1].w, u = edge[road * 2 - 1].u, v = edge[road * 2 - 1].v;
				//edge[road * 2 - 1].w = edge[road * 2 - 2].w = len;
				delta = len - edge[(road - 1) * 2].w, u = edge[(road - 1) * 2].u, v = edge[(road - 1) * 2].v;
				edge[(road-1)*2+1].w = edge[(road-1)*2].w = len;
				if(in[u] < in[v]) swap(u, v);				//热泪盈眶...in写成level，WA死了...对拍一步一步才找到这个弱智错误的 ...
				Update(in[u], delta), Update(out[u] + 1, -delta);
			}
		}
	}
	return 0;
}
