/*
	详细题解：http://blog.csdn.net/joy32812/article/details/5663111
*/
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define		low(x)		((x) & (-(x)))

int f[105][65][65], num[65], state[65], cur[105];
char str[105];
int n, m, idx, inf;

bool ok(int S)
{
	if(S & (S >> 1)) return false;
	if(S & (S >> 2)) return false;
	return true;
}
int  calc(int S)
{
	int sum = 0;
	while(S) {
		sum ++;
		S -= low(S);
	}
	return sum;
}
void init(int m)
{
	for(int i = 0, oo = (1 << m); i < oo; i++) if(ok(i)) state[idx] = i, num[idx++] = calc(i);
}
inline bool fit(int i, int y)
{
	return y == (cur[i] & y);
}
inline bool adapt(int x, int y)
{
	return !(x & y);
}
bool solve();
int main()
{
	while(solve()) ;
	return 0;
}

bool solve()
{
	memset(&inf, 127, sizeof inf);
	if(scanf("%d %d", &n, &m) == EOF) return false;
	init(m);
	for(int i = 2; i <= n+1; i++) {
		scanf("%s", str);
		cur[i] = 0;
		for(int j = 0; j < m; j++) if(str[j] == 'P') cur[i] |= (1 << j);
	}
	
	memset(f,    127, sizeof    f);
	memset(f[0],   0, sizeof f[0]);
	memset(f[1],   0, sizeof f[1]);
	
	for(int i = 2; i <=  n+1; i++)
		for(int j = 0; j < idx; j++) if(fit(i-1, state[j])) {
			for(int k = 0; k < idx; k++) if(fit(i-2, state[k]) && adapt(state[j], state[k]) && f[i-1][j][k] != inf) {
				for(int t = 0; t < idx; t++) if(fit(i, state[t]) && adapt(state[j], state[t]) && adapt(state[k], state[t])) {
					if(f[i][t][j] == inf) f[i][t][j] = f[i-1][j][k] + num[t];
					else f[i][t][j] = max(f[i][t][j], f[i-1][j][k] + num[t]);
				}
			}
		}

	int ans = 0;
	for(int i = 0; i < idx; i++) 
		for(int j = 0; j < idx; j++) if(f[n+1][i][j] != inf) ans = max(ans, f[n+1][i][j]);
	printf("%d\n", ans);
	return true;
}
