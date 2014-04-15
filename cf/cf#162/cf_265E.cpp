/*
	DP  好题  实现
	题意：n个小球排成一列，有颜色ci，权值vi
		  要求选出若干的小球，选出来的小球相对顺序不变，这个序列的序列权值最大
		  序列{Xi}权值计算方法：(1)小球xi在第一个或者与xi前面的小球同色，即i==1或者c[xi]==c[xi+1]，则序列选择和加v[xi]*A
		  						(2)否则序列权值加v[xi]*B
								其中A，B是给出的常量，|vi|<=10^5, |A|,|B|<=10^5
	
	思路：之前个人赛的题呀，到现在还是不会做......看题解貌似很简单，但是感觉自己写的话就会栽在细节处理和逻辑转换上...>_<
		 
		  定义dp[c]为以颜色c结尾的最优值		    //是的，我根本没有想过是这样定义状态的好不好，很妙好不好...
		  易知dp[c]至于之前颜色c和其它颜色的最大值有关，那定义fir,sec为之前出现的最大值和次大值的颜色，分类讨论(c=ci)：
		    (1)跟前面的颜色相同，即dp[c] = max(dp[c], dp[c] + vi*A)
			(2)跟前面的颜色不同，
			   c != fir，则用dp[fir]更新dp[c]肯定是最优的，dp[c] = max(dp[c], dp[fir] + vi*B)
			   c == fir，因为我们在DP过程中一直维护fir!=sec（除了初始化），所以c == fir也就是c != sec，这时用dp[sec]更新dp[c]是最优的
			   			 dp[c] = max(dp[c], dp[sec] + vi*B)


		  然后维护fir和sec其实很简单，我之前想复杂了>_<
			if(c != fir) {
				if(dp[c] > dp[fir]) sec = fir, fir = c;
				else if(dp[c] > dp[sec]) sec = c;
			}
*/
//codeforce 265E
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN	100005
typedef		long long ll;
ll dp[MAXN], col[MAXN], val[MAXN];
int n, query;

void solve(ll A, ll B)			//代码虽然很简，但肯定是在思路很清晰下才能写这么简的代码的..
{
	memset(dp, 128, sizeof(dp));				//初始化为什么是无穷大	//初始化为-1加些判断也错了，不知道怎么解决
	dp[0] = 0;
	ll fir = 0, sec = 0;
	for(int i = 1; i <= n; i++) {
		ll c = col[i], v = val[i];
		dp[c] = max(dp[c], dp[c] + v * A);	

		if(c != fir) dp[c] = max(dp[c], dp[fir] + v * B);
		else dp[c] = max(dp[c], dp[sec] + v * B);
		
		if(c != fir) {
			if(dp[c] > dp[fir]) sec = fir, fir = c;
			else if(dp[c] > dp[sec]) sec = c;
		}
	}
	printf("%I64d\n", dp[fir]);
}
int main()
{
	ll A, B;
	scanf("%d%d", &n, &query);
	for(int i = 1; i <= n; i++) scanf("%I64d", &val[i]);
	for(int i = 1; i <= n; i++) scanf("%I64d", &col[i]);
	while(query--) {
		scanf("%I64d%I64d", &A, &B);
		solve(A, B);
	}
	return 0;
}
