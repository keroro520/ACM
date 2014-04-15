#include <stdio.h>
#include <string.h>
int n, m;
int a[10];
char str[10];
int ans[1003][1003], inf;
int main()
{
	memset(ans, 127, sizeof ans); memset(&inf, 127, sizeof inf);
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) 
		for(int j = 0; j < m; j++) {
			scanf("%s", str);
			a[ str[0] + str[1] - '0' - '0' ] ++;
		}
	int row = 0, col = 0, tt = 1;
	while(a[1]) {
		if(ans[row][col] == inf) {
			ans[row][col] = tt;
			a[1]--;
			if(a[1] && row + 1 < n) ans[row+1][col] = -tt, a[1]--;
		}
		if(++col >= m) col = 0, row++, tt = -tt;
	}
	while(a[2]) {
		if(ans[row][col] == inf) {
			ans[row][col] = 2;
			a[2]--;
		}
		if(++col >= m) col = 0, row++;
	}
	while(a[0]) {
		if(ans[row][col] == inf) {
			ans[row][col] = 0;
			a[0]--;
		}
		if(++col >= m) col = 0, row++;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) 
			if(ans[i][j] == 0) printf("00 ");
			else if(ans[i][j] == 1) printf("01 ");
			else if(ans[i][j] == -1) printf("10 ");
			else printf("11 ");
		puts("");
	}
	return 0;
}
