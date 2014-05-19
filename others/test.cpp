#include <stdio.h>
int a[100000];
int main()
{
	int cases, n, x, y, z;
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d", &n);
		x = y = z = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			switch (a[i]) {
				case 0 : x++; break;
				case 2 : y++; break;
				default : z++; break;
			}
		}
		
		int ans = -1;
		if (x && y && z) {
		} else if (x && y) {
			if (x == 1) ans = 0;
	  	} else if (y && z) {
			if (y == 1) ans = 2;
		} else if (x && z) {
			if (z == 1) ans = 5;
		}
		if (ans == -1) puts("No winner");
		else for (int i = 0; i < n; i++) if (a[i] == ans) { printf("%d\n", i+1); break; }
	}
	return 0;
}
