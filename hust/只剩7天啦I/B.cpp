/*
	简单题，就是题意难懂
	题意：有1～N种魔法，一般编号大的赢编号小的，但是有M对anomalous pairs是编号小的赢编号大的，没有传递性。
		  A先选一种魔法，如果接下来B无论选哪个都输给A，则输出2和A选的魔法编号。
		  如果A被B选的魔法打败了，而他能再选一种来打败B选的（B还用那个），那么输出1.
		  否则输出0.
		  假设A和B都是按最优策略选魔法，而且同一种魔法只能选一次。


	思路：输出2的情况，有一个魔法x能打败所有魔法。即没有任意anomalous pair使得所有比x编号小的魔法打败x，且x能打败所有编号比x大的魔法
		  
		  易证没有输出0的情况

		  不是2就是1咯...
*/
#include <string.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;
#define		MAXN		1000005
vector<int> v[MAXN];
bool boo[MAXN];
int n;
int main()
{
	int cases, m, x, y;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++) v[i].clear();
		memset(boo, false, sizeof boo);
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			boo[y] = true;
			v[x].push_back(y);
		}
		int ans = -1;
		for(int i = 1; i <= n; i++) if(!boo[i]) {
			sort(v[i].begin(), v[i].end());
			bool flag = true;   int tmp = i+1;
			for(vector<int> :: iterator it = v[i].begin(); it != v[i].end(); it++) {
				if(it != v[i].begin() && *it == *(it-1)) continue;
				else if(*it != tmp) { flag = false; break; }
				tmp++;
			}
			if(flag && tmp == n+1) { ans = i; break; }
		}
		if(ans == -1) puts("1"); else printf("%d %d\n", 2, ans);
	}
	return 0;
}
