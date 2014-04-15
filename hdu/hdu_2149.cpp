/*
	博弈论 简单
*/
#include <stdio.h>
int n,m;

int main()
{
	while(scanf("%d%d", &m, &n) != EOF) {
		if(n >= m) 
			for(int i = m; i <= n; i++) printf("%d%c", i, i == n ? '\n' : ' ');
		else if(m % (n + 1) == 0) printf("none\n");
		else printf("%d\n", m % (n+1));
	}
	return 0;
}
