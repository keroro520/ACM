/*
	卡特兰数
*/
#include <stdio.h>
#include <string.h>
#define		MOD		1000000007
#define		MAXN	10005
long long       f[MAXN];
int n;

void init()
{
	f[0] = f[1] = 1;
	for(int i = 2; i <= 10000; i++) {
		for(int j = 1; j < i; j++)
			f[i] += f[j]*f[i-j], f[i] %= MOD;
	}
}
int main()
{
	init();
	while(scanf("%d", &n) != EOF) {
		printf("%lld\n", f[n+1]);
	}
	return 0;
}
