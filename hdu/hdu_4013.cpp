/*
	树的同构  树的最小表示法  枚举子树

	题意：给一棵无根树，问有多少个异构的子树。

	思路：判断同构异构我觉得不难，难的是怎么搞出所有子树。
	 	  网上的都是暴力枚举所有子树...=_= 就是枚举所有点集，然后判断这个点集是不是一棵子树（即是不是个连通块，因为森林不算子树）。
		  对于一棵子树，枚举每个节点作为根，出来的子树最小表示是不一样的，但一棵子树又只能算1。
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
#define		MAXN		16
map<string,bool> M;
struct Edge {
	int v, next;
} edge[MAXN*2];
int head[MAXN];
bool vis[MAXN];
int n, edge_num, Node_Rest;

void init()
{
	edge_num = 0;
	M.clear();
	memset(head, -1, sizeof(head));
}
void add_edge(int u, int v)
{	
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool is_subtree(int u, int pre)			//判断是否连通
{
	if(--Node_Rest == 0) return true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == pre || !vis[v]) continue;
		if(is_subtree(v, u)) return true;
	}
	return false;
}
string min_Presentation(int u, int pre)			//树的最小表示
{
	vector<string> sub;
	string res = "(";
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == pre || !vis[v]) continue;
		sub.push_back( min_Presentation(v, u) );
	}
	sort(sub.begin(), sub.end());
	for(int Size = sub.size(), i = 0; i < Size; i++) 
		res += sub[i];
	res += ")";
	return res;
}
int main()
{
	int cases, Cas = 0, u, v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++) {	
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		int ans = 0;
		for(int N = (1 << n), status = 1; status < N; status++) {
			int idx ;
			Node_Rest = 0;
			for(int i = 1; i <= n; i++) 
				if((1<<(i-1)) & status) vis[i] = true, Node_Rest++, idx = i;
				else vis[i] = false;
			if(!is_subtree(idx, -1)) continue;

			bool flag = false;
			for(int i = 1; i <= n; i++) if(vis[i]) {
				string res = min_Presentation(i, -1) ;
				if(!M[res]) {
					M[res] = true;			//虽然不同点做根得到的最小表示序列不一样
					flag = true;			//但是只能算一棵子树。还要记得把每个节点做根节点的时候该点集的最小表示哈希存下来
				}
			}
			ans += flag;
		}
		printf("Case #%d: %d\n", ++Cas, ans);
	}
	return 0;
}
