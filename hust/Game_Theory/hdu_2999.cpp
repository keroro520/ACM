/*
	博弈  构造   好题

	题意：一排石头，一个数字集合，每次只能取若干个连续的石头（数量必须是给出的数字集合里的)。

	思路：看了题解之后觉得跟hdu 3032类似，都可以“把一堆石子分成两堆石子”这个操作。
		  hdu 3032我是打表找规律的，因为数太大。这道题数据不大，直接SG之。

		  一个可行操作可以把一个区间分成两个区间（如果操作取的是两端的连续石头，则分出的区间里面有一个为空区间'() ），如长度为5，可行操作为2，则取了之后后继可能为{[1,3]} , {[1], [4,5]} , {[1,2], [5]} , {[3,5]} 四种情况，跟Nim一样，当前状态的sg值等于两个后继状态的sg值的抑或和。
*/
//hdu 2999
#include <stdio.h>
#include <string.h>
#define		MAXN		1005
int sg[MAXN], S[MAXN], n;

int SG(int u)
{
	if(u == 0) return 0;
	if(sg[u] != -1) return sg[u];
	bool vis[MAXN];
	memset(vis, false, sizeof(vis));
	for(int i = 0; i < n && S[i] <= u; i++) {
		for(int j = 0; j <= u - S[i] && j <= u - S[i] - j; j++)		//不加j<=u-S[i]-j剪枝会TLE
			vis[ SG(j) ^ SG(u - S[i] - j) ] = true;
	}
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}

int main()
{
	int m, x;
	while(scanf("%d", &n) != EOF) {
		memset(sg, -1, sizeof(sg));
		for(int i = 0; i < n; i++) scanf("%d", &S[i]);
		scanf("%d", &m);
		while(m--) {
			scanf("%d", &x);
			puts(SG(x) ? "1" : "2");
		}
	}
	return 0;
}
