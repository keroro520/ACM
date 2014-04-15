/*
	博弈论 简单
*/
#include <stdio.h>

int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m), n) {
		n--, m--;
		if(!((n & 1) || (m & 1))) printf("What a pity!\n");
		else printf("Wonderful!\n");
	}
	return 0;
}
