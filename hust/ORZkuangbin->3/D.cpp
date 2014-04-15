#include <stdio.h>
#define		MAXN	10005

int next[MAXN], fa[MAXN], orig[MAXN], ball[MAXN], trans[MAXN];
int n;

void init()
{
	for(int i = 1; i <= n; i++) 
		next[i] = fa[i] = orig[i] = i, ball[i] = 1, trans[i] = 0;//fa[i]所在城市，trans[i]转移次数，orig[i]未更新转移前在的城市
}
int  Find(int x) { return x == fa[x] ? x : fa[x] = Find( fa[x] ); }
void Union(int u, int v)
{
	int fx = Find(u), fy = Find(v);
	if(fx == fy) return ;
	ball[fy] += ball[fx];
	ball[fx]  = 0;
	fa[fx]    = fa[fy];
	next[fx]  = fy;
}
int calc(int u)
{
	int tmp = u, v = Find(u), sum = 0;
	u = orig[u];	
	while(u != v) {
		sum++;
		u = next[u];
	}
	orig[tmp] = v;
	trans[tmp] += sum;
	return trans[tmp];
}
int main()
{
	int cases, Cas = 0, query, u, v, x; char op[5];
	scanf("%d", &cases);
	while(cases--) {
		printf("Case %d:\n", ++Cas);
		scanf("%d %d", &n, &query);
		init();
		while(query--) {
			scanf("%s", &op);
			if(op[0] == 'T') {
				scanf("%d %d", &u, &v);
				Union(u, v);
			} else {
				scanf("%d", &x);
				printf("%d %d %d\n", Find(x), ball[Find(x)], calc(x));
			}
		}
	}
	return 0;
}
