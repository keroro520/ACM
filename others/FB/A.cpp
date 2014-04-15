#include <algorithm>
#include <stdio.h>
using namespace std;
#define		inf		(1 << 28)
char Map[25][25];
int main()
{
	int cases, Cas = 0, n;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		int min_x = inf, min_y = inf, max_x = -inf, max_y = -inf, black = 0;
		for(int i = 0; i < n; i++) {
			scanf("%s", Map[i]);
			for(int j = 0; j < n; j++) if(Map[i][j] == '#') {
				black++;
				min_x = min(min_x, i), min_y = min(min_y, j);
				max_x = max(max_x, i), max_y = max(max_y, j);
			}
		}
		bool ok = true;
		if(max_x - min_x != max_y - min_y) ok = false;
		for(int i = min_x; i <= max_x && ok; i++)
			for(int j = min_y; j <= max_y && ok; j++)
				if(Map[i][j] != '#') ok = false;
				else black--;
		printf("Case #%d: %s\n", ++Cas, (ok && black == 0) ? "YES" : "NO");
	}
	return 0;
}
