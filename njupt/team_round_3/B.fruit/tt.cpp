#include <vector>
#include <stdio.h>
using namespace std;
#define		MAXN		(1 << 17)
vector<int> v[2];
int a[MAXN];

int calc(int a, int b, int ch)
{
	if(ch == 0) return (a|b);
	else return (a^b);
}
int work(int n, char ch, int cur)
{
	if(n == 1) return v[cur][0];
	v[1-cur].clear();
	for(int i = 0; i < n; i += 2) {
		v[1-cur].push_back( calc(v[cur][i], v[cur][i+1], ch) );
	}
	return work((n >> 1), !ch, 1-cur);
}
int main()
{
	int n, p, b, query;
	scanf("%d%d", &n, &query);
	for(int i = 0; i < (1 << n) ; i++) {
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < (1 << n); i++) {
		v[0].push_back(a[i]);
	}

	printf("0 : %d\n", work((1<<n), 0, 0));
	for(int i = 1; i <= query; i++) {
		scanf("%d%d", &p, &b);
		a[p-1] = b;
		v[0].clear();
		for(int j = 0; j < (1 << n); j++) {
			v[0].push_back(a[j]);
		}
		printf("%d : %d\n", i, work((1<<n), 0, 0));
	}
	return 0;
}
