/*
	阶梯博弈扩展

	题意：给编号为1-N的盒子里放若干颗石子，若A，B满足:A非空 && (A+B)%3==0 && (A+B)%2==1 则可以从A中取任意石头挪到盒子B去。谁不能挪动谁就输。

	思路：因为实现知道是阶梯博弈，所以就尽力往阶梯博弈上靠。
		  经典阶梯博弈是分奇数阶梯/偶数阶梯的，就想把这道题的阶梯也分个奇偶。然后就打表出所有合法(A,B)，根据(A,B)表找规律，发现确实能一个数确实只属于奇数阶梯或只属于偶数阶梯。继续下去就没分析出奇偶阶梯的分布规律了，直接暴力打表出odd_jump[i]表第i阶梯是否为奇阶梯。
		  后面就是经典阶梯博弈了。
*/
//hdu 3389
#include <stdio.h>
#include <string.h>
int sg[105];
bool       odd_jump[10005];
int SG(int u)
{
	if(u == 0) return 0;
	if(sg[u] != -1) return sg[u];
	bool      vis[105];
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= u; i++) vis[SG(u-i)] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}
void init()
{
	for(int i = 1; i <= 10002; i++) {
	    int j = i-1;
	    for( ; j > 0; j--) if((i+j) % 2 == 1 && (i+j) % 3 == 0) {
	        odd_jump[i] = !odd_jump[j];
	        break;
	    }	    
	}
}

int main()
{
	memset(sg, -1, sizeof(sg));
	init();
	int cases, Cas = 0, x, n;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if(odd_jump[i]) {
				ans ^= SG(x);
			}
		}
		printf("Case %d: %s\n", ++Cas, ans ? "Alice" : "Bob");
	}
	return 0;	
}
