/*
	博弈  好题  线性sg
	题目描述：给你一串数字，然后（长度1-6），每次可以进行两种操作：1.把里面的某位大于0的数字减1,；2.把某为0的位和右边的所有数字擦去.  最先使所有数字消失的玩家胜利。现在问是否先手胜利。
	思路：一开始想直接sg暴搞，可是因为每一位数字减到0它还不是最终状态，即对于每一位，sg[0] != END，而我们一般记忆化sg是以0为最终状态的（谁叫C的下标是以0为起始呢=_=），然后想不到办法来解决这个问题。
		  看题解知道，可以线性扫...类似素数筛一样，遇到sg[i] == 0的状态就暴力把能够到达i的前驱状态找出来，设其sg为1

		  第一次见到sg线性扫的.
*/
#include <stdlib.h>
#include <stdio.h>
bool sg[1000005];
void extend(int x)
{
	int tmp = x, base = 1, n = 0;
	while(x) {
		int d = x % 10;
		for(int i = 1; i <= 9-d; i++) sg[tmp + base * i] = 1;

		x /= 10, base *= 10, n++;
	}
	x = tmp; base = 1;
	for(int l = n+1; l <= 6; l++) {
		x *= 10;
		for(int i = 0; i < base; i++)
			sg[x + i] = 1;
		base *= 10;
	}
}
void init()
{
	sg[0] = 1;
	for(int i = 1; i < 1000000; i++) if(!sg[i]) extend(i);
}
int main()
{
	char s[10];
	init();
	while(scanf("%s", s) != EOF) {
		if(s[0] == '0') puts("Yes");
		else 			puts(sg[atoi(s)] ? "Yes" : "No");
	}
	return 0;
}
