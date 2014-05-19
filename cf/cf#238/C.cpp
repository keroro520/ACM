// 当年在宋威的指导下知道规律的=_=
#include <stdio.h>
int op, n, a[1005][1005], query, tot = 0, x;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
		tot += (a[i][i] ? 1 : 0);
	}
	scanf("%d", &query);
	while(query--) {
		scanf("%d", &op);
		if(op == 3) printf("%d", tot & 1 ? 1 : 0);
		else if(op == 1) {
			scanf("%d", &x);
			for(int i = 1; i <= n; i++) a[x][i] ^= 1;
			tot += (a[x][x] ? 1 : -1);
		} else if(op == 2) {
			scanf("%d", &x);
			for(int i = 1; i <= n; i++) a[i][x] ^= 1;
			tot += (a[x][x] ? 1 : -1);
		}
	}
	puts("");
	return 0;
}
