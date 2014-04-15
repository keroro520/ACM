/*
	博弈   打表找规律
	找不出规律，看到有人打表找规律，我也打了一下，发现真的有规律。
	下面是cxlove的证明：
	..Lasker's Nim游戏：每一轮允许两会中操作之一：①、从一堆石子中取走任意多个，②、将一堆数量不少于2的石子分成都不为空的两堆。
	..很明显：sg(0) = 0，sg(1) = 1。
    ..状态2的后继有：0，1和（1，1），他们的SG值分别为0，1，0，所以sg(2) =2。
    ..状态3的后继有：0、1、2、（1，2），他们的SG值分别为0、1、2、3，所以sg(3) = 4。
    ..状态4的后继有：0、1、2、3、（1，3）和（2，2），他们的SG值分别为0，1，2，4，5，0，所以sg(4) = 3.
	..由数学归纳法可以得出 sg(4k)=4k-1;sg(4k+1)=4k+1;sg(4k+2)=4k+2;sg(4k+3)=4k+4;
*/
//hdu 3032
#include <stdio.h>

int main()
{
	int x, cases, n;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		int ans = 0;
		while(n--) {
			scanf("%d", &x);
			if(x % 4 == 0) ans ^= x-1;
			else if(x % 4 == 3) ans ^= x+1;
			else ans ^= x;
		}
		puts(ans ? "Alice" : "Bob");
	}
	return 0;
}


/*  打表程序 =====================================================
int SG(int u)
{
	if(u == 0) return 0;
	if(sg[u] != -1) return sg[u];
	bool vis[1000];
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= u; i++) vis[SG(u-i)] = true;
	for(int i = 1; i <= u/2; i++) vis[SG(i) ^ SG(u-i)] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}
int main()
{
	memset(sg, -1, sizeof(sg));
	for(int i = 0; i < 20; i++) printf("sg[%d] = %d\n", i, SG(i));
	return 0;
}
===================================================================*/
