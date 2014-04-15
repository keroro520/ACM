/*
	
	简单DP

	貌似自己DP实力有上涨呀??
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		1005

char str[1005];
int K, n;
bool boo[MAXN][27];
int  sum[MAXN], f[MAXN][27];

int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %s", &K, str);
		n = strlen(str);
		memset(boo, false, sizeof boo);
		memset(sum,     0, sizeof sum);
		for(int i = 1; i <= n/K; i++)
			for(int j = (i-1)*K; j < i*K; j++)
				if(boo[i][str[j]-'a'] == 0) boo[i][str[j]-'a'] = true, sum[i]++;

		memset(f,    127, sizeof    f);
		for(int j = 0; j < 26; j++) f[0][j] = 1, boo[0][j] = true;
		for(int i = 1; i <= n/K; i++)
			for(int j = 0; j < 26; j++) if(boo[i][j]) {
				for(int k = 0; k < 26; k++) if(boo[i-1][k]) {
					if(k == j) {
						if(sum[i] == 1) f[i][j] = f[i-1][j];
						else 			f[i][j] = min(f[i][j], f[i-1][j] + sum[i]);
					} else {
						f[i][j] = min(f[i][j], f[i-1][k] + sum[i] - (boo[i][k]));
					}
				}
			}
		int ans = 999999999;
		for(int i = 0; i < 26; i++) ans = min(ans, f[n/K][i]);
		printf("%d\n", ans);
	}
	return 0;
}
