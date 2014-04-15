#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN			1000
int n, K;
int sg[100000002];
int SG(int u)
{
	if(u == n) return 0;
	if(sg[u] != -1) return sg[u];
	bool vis[MAXN];
	memset(vis, false, sizeof(vis));
	for(int i = u+1; u <= u+K; u++) vis[SG(i)] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}
int main()
{
	while(scanf("%d%d", &n, &K), n && K) {
		//memset(sg, -1, sizeof(sg));
		//puts(SG(n) ? "Tang" : "Jiang");
		puts((n-1) % (K+1) ? "Tang" : "Jiang");
	}
	return 0;
}
