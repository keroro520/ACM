/*
	数位DP  好题  稍难有细节
	题意：[l,r]内有多少个回文数？如12321, 7227

	思路：http://blog.csdn.net/auto_ac/article/details/8803952

		  开始想按hdu_3709那样枚举中心点来搞，但是这种方法要记录前缀和preSum，而这里的前缀和太大了存不下...

		  LZ的写法挺少见的。他是像区间DP一样，两端l/r往中间移，边移边算。跟一般数位DP只有一个指针pos从左往右移复杂。由一端指针移动变到现在两端指针移动要改得也不多，改一下边界条件(l < r)，改一下移动方式(l--, r++)
		  这里是枚举长度搞，其实跟枚举中心位是一个道理，虽然枚举长度比枚举中心少见，不过个人感觉对于这道题来讲，枚举长度比较方便：
		  
		  dfs()加了个参数preFit，这跟回文有关，就是记录已经遍历过的两端是否能够达到回文。
*/
//lightoj 1205
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long dp[20][20];
int digit[20];

long long dfs(int len, int l, int r, bool full, bool preFit)	//preFit表s[len..l]与s[r..0]的的关系，preFit为true表示s[len..l+1]与s[r-1..0]可以匹配，否则需要当前digit[r] > i才能fit~~
{
	if(l < r) return !full || preFit;	//为什么写成‘=’等于就不对？
									//估计跟preFit有关。因为虽然l == r之前preFit = false，但是如果a[l=r] > 0时，preFit是应该变为true的
	if(!full && dp[len][l] != -1) return dp[len][l];

	long long res = 0;
	int end = full ? digit[l] : 9;

	for(int i = 0; i <= end; i++) {
		if(i == 0 && l == len-1) continue;				//l == len-1表示当前是第1位。就是0啦~前导0真是麻烦
		bool nowFit = preFit;
		if(nowFit) nowFit = (digit[r] >= i);			//跟回文性质有关
		else nowFit = (digit[r] > i);

		res += dfs(len, l-1, r+1, full && i == end, nowFit);
	}

	if(!full) dp[len][l] = res;
	return res;
}
long long calc(long long n)
{
	if(n <= 1) return n+1;		//1还是0？
	int Index = init(n);
	long long res = 1;			//估计1是表示0也是palindromic
	for(int i = Index; i >= 1; i--) {
		int len = i;
		res += dfs(len, len-1, 0, len == Index, true);			//第一次见这样搞的
	}
	return res;
}
int init(long long x);
int main()
{
	int cases, Cas = 0;
	long long l, r;
	memset(dp, -1, sizeof(dp));
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lld%lld", &l, &r);
		if(l > r) swap(l, r);
		printf("Case %d: %lld\n", ++Cas, calc(r) - calc(l-1));
	}
	return 0;
}
int  init(long long x)
{
	int Index = 0;
	while(x) {
		digit[Index++] = x % 10;
		x /= 10;
	}
	return Index;
}
