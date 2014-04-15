#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		5005
int x[MAXN], num[MAXN][MAXN], a[MAXN][MAXN];
int n, m;
int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i <= 5000; i++) num[i][0] = -1;

	for(int i = 1; i <= n; i++) {
		while(getchar() != '\n') ;
		for(int j = 1; j <= m; j++) {
			a[i][j] = getchar() - '0';
			//scanf("%1d", &a[i][j]);
			if(a[i][j] == 0) num[i][j] = -1;
			else if(num[i][j-1] == -1) num[i][j] = j;
			else num[i][j] = num[i][j-1];

		}
	}

	int ans = 0;
	for(int j = m; j >= 1; j--) {	//枚举最后一列
		memset(x, 0, sizeof x);
		for(int i = 1; i <= n; i++) if(num[i][j] != -1) x[ num[i][j] ] ++;
		int tt = 0;
		for(int k = 1; k <= j; k++) {
			ans = max(ans, (x[k]+tt) * (j-k+1));
			tt += x[k];
		}
	}
	printf("%d\n", ans);
}
