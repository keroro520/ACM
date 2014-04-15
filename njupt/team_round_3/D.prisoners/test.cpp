#include <stdio.h>

int main()
{
	int n;
	while(scanf("%d", &n) != EOF) {
		if(n == 0) printf("0\n");
		else printf("%d\n", n-1);
	}
	return 0;
}
