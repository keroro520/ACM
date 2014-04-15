#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN	50005
int b[MAXN][2], pos[MAXN], here[MAXN], n, result[MAXN];
int ans;
bool boo[MAXN], used[MAXN];

void work();
int main()
{
	while(scanf("%d", &n) != EOF) {
		memset(boo, false, sizeof(boo));
		for(int i = 1; i <= n; i++) {
			scanf("%d%d", &b[i][0], &b[i][1]);
		}
		pos[1] = 1;
		boo[1] = true;
		here[1] = 1;
		bool flag = true;
		for(int i = 2; i <= n; i++) {
			int x = pos[i-1];
			if(!boo[b[x][0]]) pos[i] = b[x][0];
			else if(!boo[b[x][1]]) pos[i] = b[x][1];
			else {
				flag = false;
				break;
			}
			boo[pos[i]] = true;
			here[pos[i]] = i;
		}
		if(!flag) {
			printf("-1\n");
			continue;
		}
		ans = -1;
		work();
		int p = 2, q = n;
		while(p < q) {
			swap(pos[p], pos[q]);
			p++, q--;
		}
		work();
		printf("%d\n", n - ans);
	}
	return 0;
}

void work()
{
	int sum = 0;
		for(int i = 1; i <= n; i++) 
			//if(i > pos[i]) result[i] = n + pos[i] - i;
			//else result[i] = pos[i] - i;
			sum += (pos[i] == i);
	ans = max(ans, sum);
//		int tmp = 0;
//		sort(result+1, result+n+1);
//		int sum = 1;
//		for(int i = 2; i <= n; i++)
//			if(result[i] == result[i-1]) sum++;
//			else ans = max(ans, sum), sum = 1;
//		ans = max(ans, sum);
}
