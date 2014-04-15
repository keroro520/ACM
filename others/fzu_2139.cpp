/*
	二分答案  思路题
	题意：好久没举办月赛了，这次lqw又给大家出了5道题，因为hsy学长宣传的很到位，吸引了n个DDMM们来做，另一位kk学长说，全做对的要给金奖，做对4题要给银奖，做对3题要给铜奖。统计数据的时候，发现每题分别在n个人中有n1、n2、n3、n4、n5个人通过，lqw问kk：“这次难度稍微提高了些，你再猜下，至少会有多少个人获奖？”

	思路：二分答案
*/
//problem link : http://acm.fzu.edu.cn/contest/problem.php?cid=130&sortid=8
#include <stdio.h>
#include <algorithm>
using namespace std;

int n, a[6];
bool check(int _std, int n)
{
	int level = 1, j = 0;
	for(int i = 0; i < 5; i++) if(a[i] > _std) {
		int x = a[i] - _std;
		if(j + x > n) level++, j = j + x - n;
		else j += x;
	}
	return level < 3;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int  i = 0 ; i < 5; i++) scanf("%d", &a[i]);		sort(a, a+5);
		int l = 0, r = n, ans = n, mid;
		while(l <= r) {
			mid = (l + r) >> 1;
			if(check(mid, n-mid)) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
