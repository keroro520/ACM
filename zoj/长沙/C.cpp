#include <string.h>
#include <stdio.h>
int a[2][800][800];
int n;
bool check(int cur)
{
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) 
		if(a[cur][i][j] != i*n+j) {
			return false;
		}
	return true;
}
void change(int cur)
{
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) 
		a[1-cur][ (i+j)%n ][ (i+2*j)%n ] = a[cur][i][j];	
}
int calc(int n)
{
	memset(a, -1, sizeof(a));
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) a[0][i][j] = i*n+j;
	int ans = 0, cur = 0;
	do {
		change(cur);
		ans ++;
		if(check(1-cur)) return ans;
		cur = 1 - cur;
		memset(a[1-cur], -1, sizeof(a[cur]));
	} while(true);
}
long long fab[50000];
void init()
{
	fab[0] = fab[1] = 1;
	for(int i = 2; i <= 100; i++) fab[i] = fab[i-1] + fab[i-2];
//	for(int i = 1; i <= 100; i++) printf("%d: %lld\n",i, fab[i]);
}
int main()
{
	init();
	for(int i = 2; i <= 42; i++) { n = i, printf("%d : %d\n", i, calc(i)); }
//	long long x;
//	while(scanf("%lld", &x) != EOF) {
//		for(int i = 1; i <= 91; i += 2) 
//			if(fab[i] % x == 0 && fab[i+1] % x == 1) {
//				printf("%d\n", (i+1)/2);
//				break;
//			}
//	}
	return 0;
}
