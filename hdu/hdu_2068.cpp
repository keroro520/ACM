/*
	博弈DP  记忆化博弈

	题意：题目：有两个队，每个队有n个人，每个人每次有数量限制，取最后一块的输。

	思路：dp[i][j]表示第i个人取，还有j块石头 。
	当j为0的时候，没有石头，这时候是胜，为1。
	后继中有必败态的为必胜态。
*/
//hdu 2068
#include <stdio.h>
#include <string.h>
int sg[20][8200], a[20], n;

int SG(int idx, int remain)
{
	if(remain == 0) return 1;
	if(sg[idx][remain] != -1) return sg[idx][remain];
	for(int j = 1; j <= a[idx] && remain >= j; j++) 
		if(!SG((idx+1)%(2*n), remain - j)) return sg[idx][remain] = 1;
	return sg[idx][remain] = 0;
}

int main()
{
	int s;
	while(scanf("%d", &n) != EOF && n) {
		scanf("%d", &s);
		for(int i = 0; i < 2*n; i++) {
			scanf("%d", &a[i]);
		}
		memset(sg, -1, sizeof(sg));
		printf("%d\n", SG(0, s));
	}
	return 0;
}
