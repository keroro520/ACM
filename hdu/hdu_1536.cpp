/*
	博弈论  简单题  Nim  SG

	SG函数里面的vis开大了RE(stack_overflow)两次。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN	10005
int sg[MAXN], S[105], K;
int SG(int u)
{
	if(sg[u] != -1) return sg[u];
	bool vis[110];
	memset(vis, false, sizeof(vis));
	for(int i = 0; i < K && S[i] <= u; i++)
		vis[ SG(u - S[i]) ] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}

int main()
{
	int query, many, heap, m;
	while(scanf("%d", &K) , K) {
		memset(sg, -1, sizeof(sg));
		for(int i = 0; i < K; i++) scanf("%d", &S[i]);
		sort(S, S+K);
		scanf("%d", &query);
		while(query--) {
			scanf("%d", &m);
			int ans = 0;
			while(m--) {
				scanf("%d", &heap);
				ans ^= SG(heap);
			}
			printf("%c", ans == 0 ? 'L' : 'W');
		}
		printf("\n");
	}
	return 0;
}
