/*
	单调栈  思路题
	题意：有N个袋子放成一排，每个袋子里有一定数量的糖果，lzs会随机选择连续的几个袋子，然后拿走这些袋子中包含最多糖果的袋子。现问你，在选择x个袋子的情况下，lzs最坏情况下，也就是最少会拿到多少个糖果？对于x取值为1到n都分别输出答案。

	思路：我们定义一个区间最多糖果的袋子叫做key_value。
		  用单调栈处理出Li/Ri表ai在(Li, Ri)区间上是key_value

		  t = Ri - Li - 1; 
		  用ans[x]表连续取x个袋子，能取到最少的糖果数。那我们对每个ai，有了(Li,Ri)，就可以用ai去更新每个x ∈ (1, t)啦~
*/
//fzu 2136
//problem link : http://acm.fzu.edu.cn/contest/problem.php?cid=130&sortid=5
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		INF			999999999
#define		MAXN		100005
int n, S[MAXN], a[MAXN], ans[MAXN], L[MAXN], R[MAXN];

void init()
{
	int top = 1;  S[0] = 0;   a[0] = INF;
	for(int i = 1; i <= n; i++) {
		while(a[S[top-1]] < a[i]) top--;
		int j = top;
		while(a[S[top-1]] == a[i]) j--;
		L[i] = S[top-1];

		S[top++] = i;
	}
	top = 1; S[0] = n+1; a[n+1] = INF;
	for(int i = n; i >= 1; i--) {
		while(a[S[top-1]] < a[i]) top--;
		int j = top;
		while(a[S[top-1]] == a[i]) j--;
		R[i] = S[top-1];

		S[top++] = i;
	}
	//for(int i = 1; i <= n; i++) printf("! %d %d %d\n", i, L[i], R[i]);
}
void solve()
{
	memset(ans, 127, sizeof(ans));
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= R[i] - L[i] - 1; j++) ans[j] = min(ans[j], a[i]);
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		init();
		solve();
		for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	}
	return 0;
}
