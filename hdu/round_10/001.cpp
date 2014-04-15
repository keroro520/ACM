#include <stdio.h>
#define		MAXN		100005
int T[MAXN], C[MAXN];
int n;

int main()
{
	int query, M;
	while(scanf("%d%d", &n, &query) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d", &T[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &C[i]);
		bool label = false;
		for(int i = 1; i <= n; i++) if(C[i] == 1) { label = true; break; }
		while(query--) {
			scanf("%d", &M);
			if(M <= 0) printf("NO\n");
			else if(label) printf("YES\n");
			else if(M & 1) printf("NO\n");
			else printf("YES\n");
		}
	}
	return 0;
}
