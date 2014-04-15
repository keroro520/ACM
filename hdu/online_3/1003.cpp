#include <map>
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define		debug		printf("!\n")
#define		bug(x)		printf("# %d\n", x)
#define         low(x)      ((x) & (-(x)))
#define		MAXN		10005
#define		MAXM		500005
#define		MAXP		100005
#define		INF			2139062143
class  Edge {
	public :
	int v, u, w;
	friend bool operator < (const Edge & x, const Edge & y) {
		return x.w < y.w;
	}
} edge[MAXM];
int p[MAXP];
long long c[MAXP + MAXM+10];
int people[MAXN], fa[MAXN], e[MAXM+MAXP+10];
int n, idx_hash;
long long tot;
map<int,int> M;
void init()
{
	memset(c, 0, sizeof(c));
}
void Update(int pos, long long val)
{
	while(pos < idx_hash) {
		c[pos] += val;
		pos += low(pos);
	}
}
long long Query(int pos)
{
	long long sum = 0;
	while(pos) {
		sum += c[pos];
		pos -= low(pos);
	}
	return sum;
}
int Find(int x)
{
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}
void Union(int u, int v, int w)
{
	int fx = Find(u), fy = Find(v);
	if(fx == fy) return ;
	Update(w, 2*people[fx]*people[fy]);
	tot += 2 * people[fx] * people[fy];
	people[fx] += people[fy];
	fa[fy] = fx;
}
int main()
{
	int m, query, u, v, w;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		int idx = 0;
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &w);
			u++, v++;
			edge[i].u = u; edge[i].v = v; edge[i].w = w;
			e[idx++] = w;
		}
		
		scanf("%d", &query);
		for(int i = 0; i < query; i++) {
			scanf("%d", &p[i]);
			e[idx++] = p[i];
		}
		sort(e, e+idx);
		M.clear();
		idx_hash = 1;
		M[e[0]] = idx_hash++;
		for(int i = 1; i < idx; i++) if(e[i] != e[i-1]) M[ e[i] ] = idx_hash++;

		sort(edge, edge+m);
		for(int i = 0; i < m; i++) edge[i].w = M[ edge[i].w ];
		for(int i = 1; i <= n; i++) fa[i] = i, people[i] = 1;
		tot = 0;
		for(int i = 0; i < m; i++) {
			u = edge[i].u, v = edge[i].v, w = edge[i].w;
			Union(u, v, w);
		}
		for(int i = 0; i < query; i++) printf("%I64d\n", tot - Query(M[p[i]]-1));
	}
	return 0;
}
