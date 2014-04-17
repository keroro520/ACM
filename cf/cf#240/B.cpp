/*
	DP

	f(k,i)表长为k，以i结尾的good数列有多少个
	f(k,i) = Σf(k-1,j)   ,   j<=i and j|i

	ans(k,n) = Σf(k,i)   ,   i<=n
*/
#include <vector>
#include <stdio.h>
using namespace std;
#define		MAXN	2005
#define		MOD		(1000000007)
typedef		long long		ll;
ll cnt[MAXN][MAXN];
vector<int> fac[MAXN];
int n, K;
void init()
{
	for(int i = 1; i < MAXN; i++) {
		int j = i;
		do {
			fac[j].push_back(i);
			j += i;
		} while(j < MAXN);
	}
}
int main()
{
	init();

	scanf("%d %d", &n, &K);
	for(int k = 0; k <= K; k++) cnt[k][1] = 1;
	for(int i = 0; i <= n; i++) cnt[1][i] = 1;

	for(int k = 2; k <= K; k++)
		for(int i = 2; i <= n; i++)
			for(vector<int> :: iterator it = fac[i].begin(); it != fac[i].end(); it++) {
				cnt[k][i] = (cnt[k][i] + cnt[k-1][*it]) % MOD;
			}
	ll ans = 0;
	for(int i = 1; i <= n; i++) ans = (ans + cnt[K][i]) % MOD;
	printf("%I64d\n", ans);
}
