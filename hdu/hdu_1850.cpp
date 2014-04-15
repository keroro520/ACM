/*
	简单博弈
*/
//hdu 1850
#include <stdio.h>

int a[105];
int main()
{
	int n;
	while(scanf("%d", &n), n) {
		int sum = 0, ans = 0;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]), sum ^= a[i];
		for(int i = 0; i < n; i++) 
			if(a[i] >= (sum ^ a[i])) ans ++ ;
		if(sum == 0) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}
