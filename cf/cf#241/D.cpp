/*
	思路题    多if
	题意：给一个正整数数列A. 问你这个数列至少可以拆成多少个等差数列. 拆的时候要连续.
		  如(8, 6, 4, 2, 1, 4, 7, 10, 2) 就可以拆成(8, 6, 4, 2), (1, 4, 7, 10), (2)
		  现在这个数列里面会出现 -1 ，表示这个位置的数未知，你可以用任意正整数替换.
		  所以，要求输出-1都被替换之后，这个数列至少可以拆成多少个等差数列.

	分析：难点就是在必须ai > 0

		  一开始想了个错误贪心，先把一块儿一块儿的 -1 和起来成一个总和，如 -1 -1 -1 就合成-3;
		  再贪心对于当前的ai (ai>0) ，让它尽量属于前面的等差数列;
		  下一步就是把还没归到等差数列里的-x 归到已知的由正整数构成的等差数列里，归不了的就ans++
		  但这样的贪心遇到下面的数据就跪了:
				  -1  1  5  -1  7


		  意识到这样贪心不对就好办啦，换种贪心呗.
		  改为贪心当前-1尽量属于前面的等差数列
		  实现很简单，从左往右扫，记录pre 表前一个数，d公差，tmp1/tmp2分别表示pre之前有多少个-1，
		  pre之后到当前ai有多少个-1。
		  对于ai > 0时，根据(pre, d, tmp1, tmp2)看当前ai是否能归为前面的等差数列;
		  对于ai==-1时，如果d 已知，则能根据(pre, d)确定当前-1应该替换为pre + d
		  NA表示未知，如新开一个等差数列时d当然是未知的啦；刚开始扫描时和以-1起始新开等差数列时 pre也是未知的

		  有个坑，会超int...
*/
#include <stdio.h>
#define		NA	1000000009LL
typedef long long ll;
int n; 
ll a[200005];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
	ll pre = NA, d = NA, tmp1 = 0, tmp2 = 0;
	int ans = 1;
	for(int i = 1; i <= n; i++) {
		if(a[i] == -1) {
			if(d == NA) tmp2++;			//d未知，无法确定当前-1应该替换为啥
			else {
				if(pre + d <= 0) {		//不能在同一个等差数列，新开一个，注意这时候是以-1开头，所以pre = NA
					pre = d = NA, tmp2 = 1, tmp1 = 0, ans++;
				} else pre += d;		//替换-1后可以在同一个等差数列，-1替换为pre+d
			}
		} else {
			if(pre == NA) pre = a[i]; tmp1 = tmp2, tmp2 = 0;		//第一次遇到ai>0，一定要tmp1 = tmp2
			else {
				if(d == NA) {
					if((a[i] - pre) % (tmp2 + 1) == 0) {
						d = (a[i] - pre) / (tmp2 + 1);
						if(1 + tmp1 * d <= pre) tmp1 = tmp2 = 0, pre = a[i];
						else d = NA, pre = a[i], tmp1 = tmp2 = 0, ans ++;
					} else {
						d = NA, pre = a[i], tmp1 = tmp2 = 0, ans ++;
					}
				} else {
					if(pre + d == a[i]) pre = a[i];
					else d = NA, pre = a[i], tmp1 = tmp2 = 0, ans ++;
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
