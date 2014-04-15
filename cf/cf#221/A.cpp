#include <stdio.h>
int a[10000005], num[11];
int main()
{
	int n = 0, x;
	while(scanf("%1d", &x) != EOF) {
		num[x]++;
	}
	num[1]--, num[6]--, num[8]--, num[9]--;

	for(int i = 9; i >= 0; i--)
		for(int j = 0; j < num[i]; j++)
			a[n++] = i;


	bool flag = false;
	for(int i = 1; i <= 9; i++) if(num[i]) flag = true;
	if(!flag) {
		printf("1869");
		for(int i = 0; i < num[0]; i++) printf("0");
		puts("");
		return 0;
	}

	int r = 0;
	for(int i = 0; i < n; i++) {
		r = (r * 10 + a[i]) % 7;
		printf("%d", a[i]);
	}
	r = r * 10000 % 7;
	r = 7 - r;
	if(r == 7) r = 0;
	int ans ;
	switch (r) {
		case 0 : ans = 1869; break;
		case 1 : ans = 1968; break;
		case 2 : ans = 1689; break;
		case 3 : ans = 6198; break;
		case 4 : ans = 1698; break;
		case 5 : ans = 1986; break;
		case 6 : ans = 1896; break;
	}
	printf("%d\n", ans);
	return 0;
}
