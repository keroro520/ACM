/*
	这不是多校的题吗=_=
	水过。
*/
//lightoj 1025
#include <stdio.h>
#include <string.h>
#define		MAXN	205

long long f[MAXN][MAXN];
char s[MAXN];

int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	s[0] = '#';
	while(cases--) {
		scanf("%s", s+1);
		int n = strlen(s);
		memset(f, 0, sizeof(f));
		for(int j = 1; j < n; j++)
			for(int i = j; i > 0; i--)
				if(s[i] == s[j]) f[i][j] = f[i+1][j] + f[i][j-1] + 1;
				else f[i][j] = f[i+1][j] + f[i][j-1] - f[i+1][j-1];
		printf("Case %d: %lld\n", ++Cas, f[1][n-1]);
	}
	return 0;
}
