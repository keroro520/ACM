/*
	简单题  数学题  打表
	我也不知道其原理，就是打了个表，发现规律。。
	先把int内满足条件的数字打出来，就挥发现规律，略。
*/
#include <stdio.h>
typedef	long long		ll;

int main() 
{
	int n;
	scanf("%d", &n);
	if(n < 9)  { puts("0"); return 0; }
	else if(n == 9) { puts("8"); return 0; }
	printf("72");
	for(int i = 0; i < n-9-1; i++) printf("0");
	puts("");
	return 0;
}
