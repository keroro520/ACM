#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		4005
int a[MAXN], num[1000005];
vector<int> pos[1000005];
bool boo[MAXN], M[1000005];
int find(int x, int s)
{
	for(int i = 0; i < pos[x].size(); i++)
		if(pos[x][i] > s) return pos[x][i];
	return -1;
}
int calc(int p, int q)
{
	int ans = 2;
	while(true) {
		p = find(a[p], q);
		if(p == -1) return ans;
		ans++;
		q = find(a[q], p);
		if(q == -1) return ans;
		ans++;
	}
	return ans;
}
int main()
{
	int n;
	scanf("%d", &n);
	if(n <= 2) {
		printf("%d\n", n);
		return 0;
	}
	int ans = 1;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]), pos[ a[i] ].push_back(i);
		if(M[ a[i] ] == 0) M[ a[i] ] = 1, boo[i] = true;
		if(++num[a[i]] > ans) ans = num[ a[i] ];
	}
	for(int i = 1; i <= n; i++) if(boo[i])
		for(int j = i+1; j <= n; j++) if(boo[j]) ans = max(ans, calc(i, j));

	printf("%d\n", ans);
	return 0;
}
