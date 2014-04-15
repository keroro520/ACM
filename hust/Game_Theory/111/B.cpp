/*
	博弈  推规律  欧几里得游戏   Euclid's Game

	题意：给出a,b，每一步只能用a，b中较大的数减去a，b中较小的数的倍数，最终有一个数为0的取胜。

	思路：对于两个数a, b(a>=b)，总会出现这样一个局面(a%b, b)。而如果a/b >= 2的话，则先手有可以选择谁面对(a%b, b)局势的优势。
		  显然，第一次有这个优势的人胜，即第一面对a/b >= 2局面者胜。


		  因为没有给出数据范围，所以不知道怎么sg，然后就看了题解。
*/
//hdu 1525
#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
	int a, b;
	while(scanf("%d%d", &a, &b), a&&b) {
		bool win = 0;
		while(true) {
			if(a < b) swap(a, b);
			if(a % b == 0) break;
			if(a / b >= 2) break;
			a %= b;
			win = !win;
		}
		puts(!win ? "Stan wins" : "Ollie wins");
	}
	return 0;
}
