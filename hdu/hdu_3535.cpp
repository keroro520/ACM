/*
	混合背包  好题
	题意：3种组别，每种组别有不同要求：组别为0的要求一组内至少取一个；组别为1的要求一组内之多取一个；组别为2的随便

	思路：一开始自己按组0分类DP出一个f[i][j]表示组别为0的前i组，花j元钱，能达到的最大价值；其它两个组别DP出一个g[i][j]，含义跟f相似。然后取f[I][j] + g[I'][T-j]的最大值，可能是细节地方写撮了吧，老是WA，但分析这样做是没错的。太惨了=_= 太弱了>_<

		  这里也是按组别不同分别DP
		  至少取一个：f[i][j]状态的选择可以来自上一组的状态，也可以来自本组的状态
		  至多取一个：只能来自上一组的状态
		  随便取    ：0/1背包

		  注意到，因为后两种组别没有“必须取一个”这种要求，所以在者两种组别DP时可以完全继承上一组的结果先；而“至少取一个”就不能直接继承上一组的状态，而是要判断目前状态的前继状态是否合法，才继续更新状态。
*/
//hdu 3535
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN			105
#define			AT_LEAST_ONE	0
#define			AT_MOST_ONE		1
#define			FREELY			2
struct Job {
	int cost, happy;
} job[MAXN][MAXN];
int f[MAXN][MAXN], n, T, num[MAXN], type[MAXN];
int main()
{
	while(scanf("%d%d", &n, &T) != EOF) {
		memset(f, -1, sizeof(f));
		memset(f[0], 0, sizeof(f[0]));
		for(int i = 1; i <= n; i++) {
			scanf("%d%d", &num[i], &type[i]);
			for(int j = 0; j < num[i]; j++) scanf("%d%d", &job[i][j].cost, &job[i][j].happy);
		}
		for(int i = 1; i <= n; i++) {
			if(type[i] == AT_LEAST_ONE) {
				for(int k = 0; k < num[i]; k++) {
					Job & tmp = job[i][k];
					for(int j = T; j >= tmp.cost; j--) {
						if(f[i][j-tmp.cost] != -1)   f[i][j] = max(f[i][j], f[i][j-tmp.cost] + tmp.happy);
						if(f[i-1][j-tmp.cost] != -1) f[i][j] = max(f[i][j], f[i-1][j-tmp.cost] + tmp.happy);
					}
				}
			} else if(type[i] == AT_MOST_ONE) {
				memcpy(f[i], f[i-1], sizeof(f[i]));
				for(int k = 0; k < num[i]; k++) {
					Job & tmp = job[i][k];
					for(int j = T; j >= tmp.cost; j--)
						if(f[i-1][j-tmp.cost] != -1)		//TODO
							f[i][j] = max(f[i][j], f[i-1][j-tmp.cost] + tmp.happy);
				}
			} else {
				memcpy(f[i], f[i-1], sizeof(f[i]));
				for(int k = 0; k < num[i]; k++) {
					Job & tmp = job[i][k];
					for(int j = T; j >= tmp.cost; j--)
						if(f[i][j-tmp.cost] != -1) 
							f[i][j] = max(f[i][j], f[i][j-tmp.cost] + tmp.happy);
				}
			}
		}
		printf("%d\n", f[n][T]);
	}
	return 0;
}
