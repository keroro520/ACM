/*
	博弈 打表找规律  sg
	题意：现在有一堆石子，石头数量为s个，每个人只能取{1,k,k^2,k^3...}的石子，谁不能取石子的时候就输了。现在devtang让你先取石子，你要怎样取石子才能获胜呢? 你只需要输出一个数字表示你要想赢第一步最少需要取的石子的数目。如果是你必输的话，就输出0。

	思路：打表找规律=_=  做完后搜题解想看看证明，结果发现都是打表找规律=_=
*/
#include <stdio.h>
#include <string.h>
int sg[105];
int n = 50, k  = 3, cases;

int SG(int n)
{
	if(n == 0) return 0;
	if(sg[n] != -1) return sg[n];
	bool vis[105]; memset(vis, false, sizeof vis);
	if(k == 1) vis[SG(n-1)] = true;
	for(int tmp = 1; tmp <= n && k != 1; tmp *= k) {
		vis[SG(n-tmp)] = true;
	}
	for(int i = 0; ; i++) if(!vis[i]) return sg[n] = i;
}
int main()
{
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &k);
			memset(sg, -1, sizeof sg);
			n %= (k + 1);
			if(!n) n = k + 1;
			if(SG(n) == 0) puts("0");
			else {
				for(int tmp = 1; ; tmp *= k) if(SG(n-tmp) == 0) {
					printf("%d\n", tmp);
					break;
				}
			}
	}
	return 0;
}
