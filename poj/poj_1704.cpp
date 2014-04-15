/*
	博弈  阶梯博弈  

	题意：题意：从左到右n个格子，某些有石子，每格永远只能放一个石子，每次可以将某个石子向左移若干格，但不能跨越任何石子。两人轮流操作，谁无路可走谁输。

	思路：如果n为偶数，则两两配对搞阶梯博弈
		  如果n为奇数，则在最座标原点加一个点，让这个新加点与最前面那个点配对。



	阶梯博弈：http://blog.csdn.net/kk303/article/details/6692506
			  http://blog.sina.com.cn/s/blog_6a6aa7830100p4nb.html

	看了阶梯博弈之后我对这道题的解法应该是正确的了，但是因为懒得看题，把题意误解了，wa了几次。
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
int a[1005], b[1005];

int main()
{
	int cases, n;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		sort(a+1, a+1+n);
		int Index = 0;
		if(n & 1) {
			for(int i = 2; i <= n; i += 2) b[Index++] = a[i+1] - a[i] - 1;
			b[Index++] = a[1]-1;
		} else {
			for(int i = 1; i <= n; i += 2) b[Index++] = a[i+1] - a[i] - 1;
		}
		int sum = 0;
		for(int i = 0; i < Index; i++) sum ^= b[i];
		puts(!sum ? "Bob will win" : "Georgia will win");
	}
	return 0;
}
