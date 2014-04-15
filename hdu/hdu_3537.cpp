/*
	博弈 翻硬币博弈

	题意：每次只能翻1-3个硬币，最右边必须是head-up

	思路：我们称一个非负整数为odious，当且仅当该数的二进制形式的1出现的次数是奇数，否则称作evil。而上面那个表中，貌似sg值都是odious数。所以当2x为odious时，sg值是2x，当2x是evil时，sg值是2x+1.

		  一开始我的sg是nim的sg，跪跪跪...上述结论一点也不看懂...


	http://blog.csdn.net/acm_cxlove/article/details/7854181			题解
	http://blog.csdn.net/acm_cxlove/article/details/7854534			翻硬币小结
*/
/*
	经典翻硬币游戏结论：局面的sg值为局面种每个正面朝上的棋子单一存在是的sg值的异或值。
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int a[1000];
int calc(int x)
{
	int sum = 0;
	while(x) {
		x &= (x-1);
		x >>= 1;
	}
	return sum;
}
int SG(int x)
{
	int res = calc(x*2);
	if(res & 1) return 2*x;
	else return 2*x+1;
}
int main()
{
	int n;
	while(scanf("%d", &n) != EOF) {
		int ans = 0;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a+n);
		int idx = 0;
		for(int i = 0; i < n; i++) 
			if(i == 0 || a[i] != a[i-1]) a[idx++] = a[i];
		n = idx;
		for(int i = 0; i < n; i++) ans ^= SG(a[i]);
		puts(!ans ? "Yes" : "No");
	}
	return 0;
}
