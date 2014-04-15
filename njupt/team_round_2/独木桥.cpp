#include <limits.h>
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define		Limit 		(100+10)
int tone[110], s[(Limit+1) * (Limit+1) + 100 + 10], f[(Limit+1) * 150 + 100 + 10];
int L, S, T, n, M;
int main()
{
	while(scanf("%d", &L) != EOF) {
		scanf("%d%d%d", &S, &T, &M);
		tone[0] = 0; tone[M+1] = L;
		for(int i = 1; i <= M; i++) scanf("%d", &tone[i]);
		if(S == T) {
			int ans = 0;
			for(int i = 1; i <= M; i++) if(tone[i] % S == 0) ans ++;
			printf("%d\n", ans);
			continue;
		}
		M += 2;
		sort(tone, tone+M);
		int Index = 0;
		memset(s, 0, sizeof(s));
		for(int i = 1; i < M; i++) {
			if(tone[i] - tone[i-1] >= Limit) {
				Index += Limit;
				s[Index] = 1;
			} else {
				Index += tone[i] - tone[i-1];
				s[Index] = 1;
			}
		}
		s[Index] = 0;
		memset(f, 127, sizeof(f));
		f[0] = 0;
		for(int i = 1; i <= Index+Limit; i++) {
			int res = f[i];
			for(int j = i - S; j >= i - T && j >= 0; j--) res  = min(f[j], res);
			f[i] = res + (s[i]);
		}
		//for(int i = 0; i <= Index+10; i++) printf("# %d  %d  %d\n", i, s[i], f[i]);
		int ans = (INT_MAX);
		for(int i = Index; i <= 10 + Index + Limit; i++) ans = min(f[i], ans);
		printf("%d\n", ans);
	}
	return 0;
}
