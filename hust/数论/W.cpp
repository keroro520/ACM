/*
	条件概率  好题

	题意：n个人去商店，每个人买东西的概率为ai。问在确定有r个人买东西的情况下第i个人包括在内的概率
	思路：直接根据条件概率的定义来
	   	  P(A|B) = P(AB)/P(B)
		  在这道题中B就是r个人买了东西
		  A就是某个人买了东西
	  	  然后考虑所有情况的概率，累加起来求的各个事件的概率

		  实现就是类似于二进制暴力枚举。

		  * *************************************** *
		  * 重点是P(AB)怎么表示						*
		  * 这里表示得很经典，值得学习				*
		  *											*
		  * *************************************** *

	疑问：我的第一个wa的程序(W_WA.cpp)为什么不对？好累，看W_WA.cpp，内有写。
*/
#include <stdio.h>
#define		MAXN			21
typedef		long long		ll;
double pro_b, pro_a[MAXN], a[MAXN];
int n;

void rec(double pre, ll stat)
{
	for(int i = 0; i < n; i++) 	
		if((1LL << i) & stat) pro_a[i] += pre;
	pro_b += pre;
}
void dfs(int cur, int rest, double pre, ll stat)
{
	if(rest < 0 || n - cur < rest) return ;			//漏了r < 0这个判断郁闷了好久
	if(cur == n) {
		rec(pre, stat);
		return ;
	}
	dfs(cur+1, rest-1, pre*a[cur],     stat|(1LL << cur));
	dfs(cur+1, rest  , pre*(1-a[cur]), stat);

//	if(n - cur < rest) return ;
//	if(rest == 0) {
//		double tmp = 1;
//		for(int i = 0; i < n; i++)
//			tmp *= ( (1LL << i) & stat ? a[i] : (1 - a[i]));
//		pro_b += tmp;
//		for(int i = 0; i < n; i++) if((1LL << i) & stat) pro_a[i] += tmp;
//		return ;
//	}
//	for(int i = cur; i < n; i++) dfs(i+1, rest-1, pre, stat|(1LL<<i));
}
int main()
{
	int r, Cas = 0;
	while(scanf("%d %d", &n, &r) , n || r) {
		printf("Case %d:\n", ++Cas);
		for(int i = 0; i < n; i++) scanf("%lf", &a[i]), pro_a[i] = 0;
		pro_b = 0;
		dfs(0, r, 1, 0);
		for(int i = 0; i < n; i++) pro_a[i] = pro_a[i] / pro_b, printf("%.6f\n", pro_a[i]);
	}
	return 0;
}
