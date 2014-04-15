#include <stdio.h>
#include <map>
#include <string.h>
#include <vector>
using namespace std;
#define			debug		printf("!\n")
#define			bug(x)		printf("#  %d\n", x)
#define			MAXN		200005
struct Edge {
	int pos, next;
} edge[MAXN * 2];
map<int,int> M;
vector<int> zero;
int head[MAXN], refer[MAXN];
int edge_num, n;
long long ans ;
void add_edge(int x, int pos)
{
	edge[edge_num].pos = pos;
	edge[edge_num].next = head[x];
	head[x] = edge_num++;
}
void init()
{
	ans = 0;
	edge_num = 0;
	memset(head, -1, sizeof(head));
	M.clear();
	zero.clear();
}

int find1(int l, int r, int x)
{
	for(int k = head[x]; k != -1; k = edge[k].next) {
		int pos = edge[k].pos;
		if(pos < r) return pos;
	}
	return r;
}
int find2(int l, int r, int x)
{
	for(int k = head[x]; k != -1; k = edge[k].next) {
		int pos = edge[k].pos;
		if(pos > l) return pos;
	}
	return l;
}
void dfs(int mid, int l, int r)
{
	int l_del = mid-1, r_del = mid+1;
	for(int i = 1; !(l_del == l && r_del == r) ; i++) {
		int j = M[ i ]; 
		int p1 = find1(l, l_del, j), p2 = find2(r_del, r, j);
			//printf("# (%d %d %d--->%d)\n", l,l_del,i,p1);
			//printf("# (%d %d %d--->%d)\n", r_del,r,i,p2);
		int a = l_del - p1, b = p2 - r_del;
		printf("%d  %lld  (a=%d b=%d) (p1=%d p2=%d) (l_del=%d r_del=%d) (l=%d,r=%d) \n", i, ans, a, b, p1, p2,l_del,r_del, l,r);
		if(j == 0 || (p1 == l_del && p2 == r_del)) {
			ans += i * ( (1+a) * (1+b) + (mid-l_del+1)*(1+b) + (r_del-mid+1)*(1+a));
			return ;
		}

		ans += i * a * b;		//新增加的
		ans += ((a+1) * (r_del - mid +1) + (b+1) * (mid - l_del +1)) * (i) ;	//弥补之前缺的
		ans += (a+b) * i;		//一个点选0，另一个选a/b区间的一个
		
		l_del = p1, r_del = p2;
	}
}
void solve()
{
	if(M[0] == 0) return ;
	for(int Size = zero.size(), i = 0; i < Size; i++) {
		int pos = zero[i];
		int mid = pos;
		if(i != Size-1) dfs(mid, 1,  zero[i+1]-1); else dfs(mid, 1, n);
	}
}
int main()
{
	int x;
	while(scanf("%d", &n) , n) {
		init();
		int Index = 1;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if(M[ x ] == 0) M[ x ] = Index, refer[Index] = x, Index++;
			if(x != 0) add_edge(M[ x ], i);
			else zero.push_back(i);
		}
		solve();
		printf("%lld\n", ans);
	}
}
