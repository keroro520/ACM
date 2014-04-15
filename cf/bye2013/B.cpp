#include <stdio.h>
int a[305], n;

int main()
{
	int sum = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		while(a[i]) {
			sum--;
			putchar('P');
			if(sum == 0) break;
			if(i == n) {
				putchar('L'), putchar('R');
			} else {
				putchar('R'), putchar('L');
			}
			a[i]--;
		}
		if(sum == 0) break;
		else putchar('R');
	}
	puts("");
	return 0;
}
