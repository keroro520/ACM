/*
	博弈论 SG 简单题 Nim游戏


*/
#include <stdio.h>
#include <string.h>
#define			MAXN		1005
int n, sg[MAXN];
int SG(int u)
{
	if(u == 0) return 0;
	if(sg[u] != -1) return sg[u];
//	bool vis[MAXN];
//	memset(vis, false, sizeof(vis));
	for(int i = 0; u >= (1 << i); i++)
		if(!SG(u - (1 << i))) return sg[u] = 1;
//		vis[SG(u - (1 << i))] = true;
//	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
	return sg[u] = 0;
}

int main()
{
	memset(sg, -1, sizeof(sg));
	while(scanf("%d", &n) != EOF) {
		puts(SG(n) ? "Kiki" : "Cici");
	}
	return  0;
}
