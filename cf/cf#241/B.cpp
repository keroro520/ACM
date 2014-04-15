#include <stdio.h>
#include <algorithm>
using namespace std;

#define		MAXM		50004
typedef long long ll;
int t[MAXM][6];
ll used[6];

int main()
{
	int n, m;
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= m; i++) 
		for(int j = 1; j <= n; j++) scanf("%d", &t[i][j]);

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			used[j] = max(used[j], used[j-1]);
			used[j] += t[i][j];
		}
		printf("%I64d ", used[n]);
	}
	puts("");
	return 0;
}
