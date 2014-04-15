/*
	好题 
	初次次数最多的数，已知出现的次数 > n/2
*/
//
#include <stdio.h>

int main()
{
	int n, a, x;
	while(scanf("%d", &n) != EOF) {
		scanf("%d", &a);
		int cnt = 1;
		for(int i = 2; i <= n; i++) {
			scanf("%d", &x);
			if(x != a) cnt--; else cnt++;
			if(cnt == 0) a = x, cnt = 1;
		}
		printf("%d\n", a);
	}
	return 0;
}
