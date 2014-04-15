// D1 
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define 	MAXN	2005

int n, m, x[MAXN], y[MAXN], l[MAXN];
int calc(int i, int j)
{
	if((!(x[j] < x[i] && x[i] < x[j]+l[j])) || (!(y[i] < y[j] && y[j] < y[i]+l[i]))) return 0;
	return min( abs(y[i]-y[j]), min( abs(y[i]+l[i]-y[j]), min( abs(x[j]-x[i]), abs(x[j]+l[j]-x[i]))));
}
int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d %d %d", &x[i], &y[i], &l[i]);
	for(int i = n; i < m + n; i++) scanf("%d %d %d", &x[i], &y[i], &l[i]);
	int ans = 0;
	for(int i = 0; i < n; i++) 
		for(int j = n; j < n+m; j++) 
			ans = max(ans, calc(i,j));

	printf("%d\n", ans);
	return 0;
}
