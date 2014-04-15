/*
	DP	记忆化搜索  好题 LCS

	题意：给出a，b串，要求求出a与b的最短父串c，和有多少种不同最短父串

	思路：求出最短父串的长度很容易，一遍LCS即可。
		  然后后面就是记忆化递归算出方案数了，f[i, j, k]表示A串的前i个字母，B串的前j个字母组合成c串的前k个字母的方案数。
		  那转移方程就很简单啦，
		  	if A[i] == B[j] then f[i,j,k] = f[i-1, j-1, k-1];	//A[i]与B[j]在都为c串的c[k]，所以这里递归的时候k只减1
			if A[i] != B[j] then f[i,j,k] = f[i-1, j, k-1] + f[i, j-1, k-1] 	//A[i]为c[k]，则递归(i-1,j,k-1)；B[j]为c[k]同理

		  虽然方程简单，但我还是卡在细节上了，就是递归的结束条件。我原来是写 "if k == 0 then return 1" ，因为总觉得k == 0那i,j此刻理所当然也等于0啦。这就是没有理解透的缘故吧...正确写法是 " if k == 0 then return (i == 0 && j == 0) "
*/
//lightoj 1013
//http://blog.csdn.net/u011433745/article/details/10050257
//http://blog.csdn.net/sharpy_gu/article/details/9988755
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		33
int dp[MAXN][MAXN]; 
long long f[MAXN][MAXN][MAXN+MAXN];
char A[MAXN], B[MAXN];
int n, m, ans;

long long dfs(int len_a, int len_b, int len_c)
{
	if(len_c == ans) return len_a == n && len_b == m;		//TODO	细节!!!
	long long &x = f[len_a][len_b][len_c] ;
	if(x != -1) return x;

	if(n == len_a) x = dfs(len_a, len_b+1, len_c+1);
	else if(m == len_b) x = dfs(len_a+1, len_b, len_c+1);
	else if(A[len_a] == B[len_b]) x = dfs(len_a+1, len_b+1, len_c+1);
	else x = dfs(len_a+1, len_b, len_c+1) + dfs(len_a, len_b+1, len_c+1);
	return x;
}
/* 逆向版本
在main()里面用dfs(n-1, m-1, max_len) 调用
long long dfs(int len_a, int len_b, int len_c)
{
	if(len_c == 0) return !(len_a || len_b);			//TODO

	long long &x = f[len_a][len_b][len_c] ;
	if(x != -1) return x;

	if(len_a == 0) x = dfs(0, len_b-1, len_c-1);
	else if(len_b == 0) x = dfs(len_a-1, 0, len_c-1);
	else if(A[len_a] == B[len_b]) x = dfs(len_a-1, len_b-1, len_c-1);
	else x = dfs(len_a-1, len_b, len_c-1) + dfs(len_a, len_b-1, len_c-1);
	return x;
}
*/
int DP()
{
	memset(dp, 0, sizeof(dp));
	for(int i = 1; i < n; i++)
		for(int j = 1; j < m; j++)
			if(A[i] == B[j]) dp[i][j] = dp[i-1][j-1] + 1;
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
	return m-1 + n-1 - dp[n-1][m-1];
}

int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	A[0] = B[0] = '*';
	while(cases--) {
		scanf("%s%s", A+1, B+1);
		n = strlen(A), m = strlen(B);
		memset(f, -1, sizeof(f));
		ans = DP();
		printf("Case %d: %d %lld\n", ++Cas, ans, dfs(1,1,0));
	}
}
