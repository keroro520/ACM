/*
	博弈论 简单题
	题意：bash博弈

	小记：如果只剩1~m个，则先手赢；如果剩下m+1个，则后手赢；
	对于2*(m+1) > n > m+1，我们总有办法把数量变成m+1；同理k*(m+1) > n > (k-1)*(m+1).
	所以只要先手初始时在k*(m+1)位置，那他就囧了。
*/

#include <stdio.h>
int main()
{
	int cases, n, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		if(n % (1 + m) == 0) printf("second\n");
		else printf("first\n");
	}	
	return 0;
}
