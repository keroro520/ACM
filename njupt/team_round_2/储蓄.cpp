#include <stdio.h>
int a[100];

void work();
int main()
{
	while(scanf("%d", &a[1]) != EOF) {
		work();
	}
	return 0;
}

void work()
{
	for(int i = 2; i <= 12; i++) scanf("%d", &a[i]);
	int sum = 0, ans ;
	bool flag = true;
	int rest = 0;
	for(int i = 1; i <= 12; i++) {
		rest += 300;
		if(rest < a[i]) {
			flag = false, ans = -i;
			break;
		} else {
			rest -= a[i];
			sum += rest/100 * 100;
			rest %= 100;
		}
	}
	if(flag == false) {
		printf("%d\n", ans);
		return ;
	}
	printf("%d\n", (int)(sum*1.2) + rest);
}
