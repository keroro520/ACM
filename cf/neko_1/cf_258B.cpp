/*
	数位DP + dfs   好题  好实现

	题意：有包含4或7的数称为Lucky number。现在Little Elephant所在的党派要与其它6个党派竞选，我们分别用[1..m]内的一个数字来代表每个党派，当然不同党派的代表数字不同。现要求Little Elephant的党派的代表数字包含的4/7的数目要比其余6个党派的代表数字包含的4/7数目的总和大，问[1..m]有多少中符合要求的方案。

	思路：数位DP预处理出cnt[x]表“[1..m]内有包含x个4/7的数字有多少个”。   但我就是这里不会...=_= 在cf上找代码看，刚好有个好人不仅风格好，还有中文注释~~Thanks~~
		   后面的就直接递推搞之。
		    直接卡看代码。
	//DP state [position][less][count].
*/
#include <stdio.h>
#include <string.h>
#define		MOD		1000000007
int digit[11], dp[11][11][11], cnt[11];
long long solve(int rest, int luckyNums) 
//计算其他6个人幸运数和小于(luckyNums)的情况数
{
	if(rest == 0) return 1;
	long long res = 0;
	for(int i = 0; i <= luckyNums; i++) if(cnt[i] > 0) {
		cnt[i]--;
		//若选择幸运数长度为i的数,下一个人最多能选择的长度为luckyNums - i
		res = (res + ((cnt[i] + 1) * solve(rest-1, luckyNums-i)) % MOD) % MOD;
		cnt[i]++;
	}
	return res;
}
int dfs(int pos, int luckyNums, int pre, bool full)
// 返回值为 0 ~ m 中 lucky nuberm 个数是 luckyNums(第二个参数)的数有多少个
{
	if(pos == -1) return pre == 0;
	if(pre < 0) return 0;
	if(!full && dp[pos][luckyNums][pre] != -1) return dp[pos][luckyNums][pre];

	int res = 0, end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) 
		res += dfs(pos-1, luckyNums, pre - (i==4 || i==7), full && i == end);
	
	return full ? res : dp[pos][luckyNums][pre] = res;
}
int calc(int n, int luckyNums)
{
	int idx = 0;
	while(n) {
		digit[idx++] = n % 10;
		n /= 10;
	}
	return dfs(idx, luckyNums, luckyNums, true);
}
int main()
{
	int n;
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	//求出结果(枚举第一个人的幸运数长度)
	for(int i = 0; i <= 9; i++) cnt[i] = calc(n, i);
	if(cnt[0]) cnt[0]--;

	long long ans = 0;
	for(int i = 1; i <= 9; i++) 
		if(cnt[i] > 0) 
			ans = (ans % MOD + cnt[i] * solve(6, i-1) % MOD) % MOD;
	printf("%I64d\n", ans);
}
