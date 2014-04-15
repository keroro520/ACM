
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define		MAXN		405
typedef		pair<int,int>	Pii;
vector<Pii> v[MAXN];
int a[MAXN], f[MAXN][MAXN], pre[MAXN][MAXN], n, V, inf;
void output(int i, int j)
{
	if(i == 0) return ;
	int next = pre[i][j], sum = V;
	output(i-1, next);
	int feed = f[i][j] - f[i-1][next];
	printf("%d", feed);
	for(vector<Pii> :: iterator it = v[i].begin(); it != v[i].end(); it++) {
		sum += it->first;
		if(sum > next + a[i]) break;
		printf(" %d", it->second);
	}
	puts("");
}
int main()
{
	memset(&inf, 128, sizeof inf);
	int m, r, l, x;
	scanf("%d %d", &n, &V);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d %d %d", &l, &r, &x);
		while(l <= r) v[l].push_back( Pii(x,i) ), l++;
	}
	for(int i = 1; i <= n; i++) sort(v[i].begin(), v[i].end());
	memset(f,    128, sizeof    f);
	f[0][0] = 0;
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= 400; j++) if(f[i][j] != inf) {
			f[i+1][ min(a[i+1], j+a[i+1]-V) ] = max( f[i+1][ min(a[i+1], j+a[i+1]-V) ], f[i][j]);
			pre[i+1][ min(a[i+1], j+a[i+1]-V) ] = j;

			int sum = V, step = 0;
			for(vector<Pii> :: iterator it = v[i+1].begin(); it != v[i+1].end(); it++) {
				sum += it->first, step++;
				if(j+a[i+1] < sum) break;
				if( f[i+1][ min(j+a[i+1] - sum, a[i+1]) ] < f[i][j] + step ) {
					f[i+1][ min(j+a[i+1] - sum, a[i+1]) ] = f[i][j] + step;
					pre[i+1][min(j+a[i+1] - sum, a[i+1])] = j;
				}
			}
		}
	}
	int ans = 0, ansj;
	for(int j = 0; j <= 400; j++) if(ans < f[n][j]) ans = f[n][j], ansj = j;
	printf("%d\n", ans);
	output(n, ansj);
	return 0;
}
