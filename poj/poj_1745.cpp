/*
	背包拓展问题  递推
	题意：给一个数列，问是否能仅用加/减法求和整个数列，使得结果模K为0

	思路：递推    滚动数组

		  这种题都看题解，哎，太弱了，neko训练法都快使我不会思考了。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
#define		MAXK		105
int a[MAXN];
bool f[2][MAXK];
int n, K;
inline		int		get(int x) {
	if(x >= 0) return  x % K;
	else return (x % K + K) % K;
}
int main()
{
	while(scanf("%d%d", &n, &K) != EOF) {
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		int cur = 0;
		memset(f, false, sizeof(f));
		f[cur][get(a[0])] = true;
		for(int i = 1; i < n; i++) {
			cur = !cur;
			memset(f[cur], false, sizeof(f)/2);
			for(int j = K-1; j >= 0; j--)
				if(f[!cur][j]) f[cur][get(j+a[i])] = f[cur][get(j-a[i])] = true;
		}
		puts(f[cur][0] ? "Divisible" : "Not divisible");
	}
	return 0;
}
