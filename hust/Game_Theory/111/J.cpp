/*
	博弈  对称性  好题
	题意：给你一个由n个硬币组成的环。每次可取1-k个硬币，取最后硬币的胜。

	思路：利用对称性解决问题。
		  若先手不能在第一次翻完，则因为第一次先手把环拆成了链，那么这是只要后首一次翻完或者把其分成相等数量的两段，之后先手不怎操作后手怎么做，做Nim。
*/
//hdu 3951
#include <stdio.h>

int main()
{
	int n, k, cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &k);
		int win;
		if( k >= n ) win = 0;
		else if(k == 1) win = !(n % 2);
		else win = 1;
		printf("Case %d: ", ++Cas);
		puts(!win ? "first" : "second");
	}
	return 0;
}
