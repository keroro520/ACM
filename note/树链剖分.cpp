/*
	树链剖分模板

	tid[x]		:	x节点在欧拉序列中的位置
	son[x]		:	x节点的重儿子
	size[x]		:	以x为根的子树的节点数
	depth[x]	:	x节点的深度
	fa[x]		:	x节点的父节点
	top[x]		:	x所在重链的链头
	F[]			:	欧拉序列(只记录第一次访问的时间戳，所以size()==N)

*/
/*
  	[1] 修改操作：例如将u到v的路径上每条边的权值都加上某值x。
    一般人需要先求LCA，然后慢慢修改u、v到公共祖先的边。而高手就不需要了。
    记f1 = top[u]，f2 = top[v]。
    当f1 <> f2时：不妨设dep[f1] >= dep[f2]，那么就更新u到f1的父边的权值(logn)，并使u = fa[f1]。
    当f1 = f2时：u与v在同一条重链上，若u与v不是同一点，就更新u到v路径上的边的权值(logn)，否则修改完成；
    重复上述过程，直到修改完成。
	[2]  求和、求极值操作：类似修改操作，但是不更新边权，而是对其求和、求极值。
*/
//spoj 375
struct Segmemt_Tree {
	int l, r, max;
} f[MAXN * 4];
int head[MAXN], tid[MAXN], weight[MAXN], son[MAXN], size[MAXN], depth[MAXN], fa[MAXN], top[MAXN], F[MAXN];
int n, edge_num, Index;

void init()
{
	edge_num = 0;
	Index    = 0;
	memset(head, -1, sizeof(head));
	memset(son,  -1, sizeof(son));
	memset(size,  0, sizeof(size));
}
void find_heavy_edge(int u, int father, int dep)
{
	depth[u] = dep;
	fa[u]    = father;
	size[u]  = 1;
	int Max = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		find_heavy_edge(v, u, dep + 1);
		weight[v] = edge[k].w;				// 我想把边权化为点权		//TODO
		size[u] += size[v];
		if(size[v] > Max) {
			Max = size[v], son[u] = v;
		}
	}
}
void connect_heavy_chain(int u, int ancester)
{
	tid[u] = ++Index;
	F[Index] = u;				//把剖分后的序列当作欧拉序列的话，那F[]就是对应的欧拉序列	//TODO
	top[u] = ancester;			//top[u]表示u所在重链的头
	if(son[u] != -1) connect_heavy_chain(son[u], ancester);
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa[u]  || v == son[u]) continue;
		connect_heavy_chain(v, v);
	}
}
int Query(int u, int v)
{
	int f1 = top[u], f2 = top[v], ans = 0;
	while(f1 != f2) {
		if(depth[f1] < depth[f2]) swap(f1, f2), swap(u, v);
		ans = max(ans, _Query(1, tid[f1], tid[u]));				//TODO
		u = fa[f1], f1 = top[u];
	}
	if(u == v) return ans;		//这样是返回区间[u, son[v]]的值，如果要返回[u,v]的值，则改为return max(ans, _Query(1,tid[u],tid[u]))
								//其实这个道理跟下面这个 TODO 是一样的，注意区间下标
								//或者可以直接省略掉这一句也可以，因为下面会处理。推荐后者

	if(depth[u] > depth[v]) swap(u, v);
	return max(ans, _Query(1, tid[son[u]], tid[v]));			//TODO  注意下标
}

