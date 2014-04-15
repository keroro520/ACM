#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int s[100005], f[100005];

int S, T, M, L;
int main()
{
	int x;
	while(scanf("%d", &L) != EOF) {
		if(L > 100000) while(true);
		scanf("%d%d%d", &S, &T, &M);
		memset(s, 0, sizeof(s));
		for(int i = 0; i < M; i++) {
			scanf("%d", &x);
			s[x] = 1;
		}
		memset(f, 127, sizeof(f));
		f[0] = 0;
		for(int i = 0; i <= L; i++) {
			for(int j = i - S; i - T <= j && j >= 0 ; j--) f[i] = min(f[i], f[j]);
			f[i] += (s[i] == 1);
		}
		int ans = 999999;
		for(int i = L; i <= L + 10; i++) ans = min(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}
