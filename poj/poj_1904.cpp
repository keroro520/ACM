/*
	连通分量  好题  启发题  二分匹配运用
	题意：N个男人N个女人，给出男人喜欢的女人编号，只要男人喜欢女人，他们就可以结婚。每个人都有唯一的结婚对象。
		  下面给出一个可行的匹配方案，即一个女人对应的男人一定是喜欢她的。现问所有合法方案。合法方案就是，每个人有唯一的结婚对象，且该女人是男人喜欢的。

	思路：这题一个突破口是那个合法的方案！
		  先写出算法，再说思路：对于给出的可行方案(boy,girl)，将这两人合成一个大点。然后对于大点u(boy,girl)和大点v(boy',girl')，如果boy喜欢girl'，则连条边(u --> v)。最后求强连通分量，同一个连通分量里的所有男人都可以娶到连通分量里的所有的女人。
		  如果题目没有给出第一个可行方案怎么办？先二分匹配搞出来一个。

		  http://www.gonglin91.com/poj-1904-kings-quest/
*/
/*
	摘：
	题意：有n个男人和n个女人，下面n行依次给出每个男人喜欢那些女人（男人和女人都分别从1到n编号），这些男人最后只能跟他喜欢的女人结婚。另外一行内给出n个数字，表示一种匹配方案，第i个数字m[i]，表示m[i]这个女人要嫁给i这个男人。注意，这个方案是一个合法的方案，即一个女人一定对应一个男人，而且这个女人一定是上面给出的，这个男人喜欢的女人之一。问题是，除了这个合法的方案，还没有没其他合法的方案，合法的方案就是，每个男人都可以娶到女人，每个女人只会嫁一个男人
	
	这题一个突破口是那个合法的方案。如果男人u喜欢女人v，就添加一个有向边u->v，在合法方案中，将女人a嫁给了男人b，那么添加一条有向边a->b
	我们来考虑一下这个图，这个图至少存在n个小环，因为可行方案产生了n对合法的夫妻，一对夫妻之间形成一个小环。
	暂且把这n个小环看做N个点。看看点和点之间有没有边，如果有边，一定是一条男人指向女人的边，因为我们在添加有向边的时候，女人指向男人的边只有n条，就是那个合法方案产生的n条，这n条边都在小环里面了，所以其他边一定是男人指向女人的边。在这N个点中，可不可能形成环内，是可能的。如果这N个点不形成环会怎样？从A这个点出发，最终回不到A这个点！从A出发，指向B，意思就是A里面的那个男人，指向了B里面的女人（大点之间的边一定是男人指向女人的边），那么A里面的女人就没人匹配了，接着如果B指向C，说明B里面的男人指向C里面的女人，那么B里面的女人又没人匹配了………………
	说明就很明显了，对于一个大点X，如果X可以指向别的点Y，并且选择了这条边的话，那么说明X里面的男人选择了Y里面的女人，那么X里面的女人必定没人匹配了，并且Y里面的男人也是没人匹配的，那么Y男人一定要到别的点找女人，也必定导致那个点的男人无法匹配，以此类推…..一个点的男人夺走了其他点的女人那么那个点的男人一定要去别处找女人，唯一完满的结局就是某个男人找到了第1个女人，别忘了那个女人还没人匹配。这样才能结束这个死循环。
	
	所以如果大点能形成环，那么环内的大点里面的男人就有了不止一种选择，并且做出不同的选择都会合法。再说得直白一点就是，对于一个连通分量里面的男人，它可能选择这个连通分量里面的任意一个女人（但是这个女人必须是他喜欢的，有的女人他不喜欢但也可以到达），并且保证合法
	其实这题给出了一组可行解，就是一个最大的突破口，试想就算没给出这组可行解一样可以问同样的问题，但是恐怕就没那么好想了。如果真的没有给出可行解，可以运行一次最大匹配，那么就找到了一组可行解，就变为了原题
	注意最后答案是要排序再输出的
*/
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		MAXN		2005
struct Edge {
	int v, next;
} edge[200005];
int head[MAXN], dfn[MAXN], low[MAXN], S[MAXN], cnt[MAXN], girl[MAXN][MAXN], belong[MAXN], refer[MAXN];
bool in_stack[MAXN];
vector<int> ans[MAXN];
int n,edge_num, Index, Order, S_top;

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num ++;
}
void init()
{
	edge_num = Order = S_top = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
	for(int i = 1; i <= n; i++) ans[i].clear();
}
void Tarjan(int u)
{
	dfn[u] = low[u] = Index++;
	S[S_top++] = u;
	in_stack[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		int x;
		do {
			x = S[--S_top];
			in_stack[x] = false;
			belong[x] = Order;
		} while(x != u);
		Order ++;
	}
}
int main()
{
	int u, v;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i <= n; i++) {
			scanf("%d", &cnt[i]);
			for(int j = 0; j < cnt[i]; j++) scanf("%d", &girl[i][j]);
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &v);
			refer[v] = i;
			ans[i].push_back(v);
		}
		for(u = 1; u <= n; u++) 
			for(int j = 0; j < cnt[u]; j++) {
				v = girl[u][j];
				if(v == ans[u][0]) continue;
				add_edge(u, refer[v]);
			}
		for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
		for(u = 1; u <= n; u++)
			for(int i = 0; i < cnt[u]; i++) {
				int v = girl[u][i];
				if(v != ans[u][0] && belong[u] == belong[refer[v]])
					ans[u].push_back(v);
			}
		for(u = 1; u <= n; u++) {
			sort(ans[u].begin(), ans[u].end());
			printf("%d", ans[u].size());
			for(int i = 0 ; i < ans[u].size(); i++) printf(" %d", ans[u][i]);
			puts("");
		}
	}
	return 0;
}
