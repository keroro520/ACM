/*
	凑1-n最少要多少个数字
*/
//http://acm.csu.edu.cn/OnlineJudge/problem.php?cid=2037&pid=0
#include <math.h>
#include <stdio.h>
double LOG2(int x)
{
	return log(x*1.0)/log(2.0);
}
int main() 
{
	int n;
	while(scanf("%d", &n) == 1) {
		printf("%d\n", (int)LOG2(n)+1);
	}
	return 0;
}
