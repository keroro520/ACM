/*
	状压 记忆化搜索  好题
	题意：经典邮递员问题。题意：给出n个顶点m条边的无向图。从其中某个顶点出发将每条边遍历至少一次回到出发点。求最短路。

	思路：欧拉回路的每个点的度必为偶数。所以只要将所有度数为奇数的点找出，将其两两之间的最短路求出，状态压缩记忆化搜索即可。度数为奇数的点必为偶数个。因为每条边连两个顶点，所以所有点的总度数为偶数，假设奇度的点有x个，则偶度得点n-x个，可以x必为偶数。所以只要在奇度点之间每两个连一条边即可。

		  简单证明原图种度数为奇数的点必为偶数个：原图总度数tot = 边数|E| * 2，是偶数，所以...
*/
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		N	16
#define		INF	999999999
long long f[1 << N];
int a[N][N], b[N][N], odd[N], deg[N];
int n;

void init()
{
	//memset(a, 127, sizeof(a));		这里都卡。。WA了好几次，边的范围都不说一下。。
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) a[i][j] = INF;
	memset(deg, 0, sizeof(deg));
	memset(f, -1, sizeof(f));
}
void Update_min(long long &x, long long y) { if(x == -1) x = y; else if(x > y) x = y; }
long long DP(int S)
{
	if(S == 0) return 0;
	if(f[S] != -1) return f[S];
	for(int i = 0; i < n; i++) if(S & (1 << i)) {
		for(int j = i+1; j < n; j++) if(S & (1 << j)) {
			int y = S ^ (1 << i) ^ (1 << j);
			Update_min(f[S], b[i][j] + DP(y));
		}
		break;			//TODO   		跟lightoj_1018一样，这里可以用break剪枝的，原因相同，在lightoj_1018.cpp有写
	}
	return f[S];
}
int main()
{
	int cases, Cas = 0, m, x, y, z;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		init();
		long long sum = 0;
		while(m--) {
			scanf("%d%d%d", &x, &y, &z);
			a[y][x] = a[x][y] = min(a[x][y], z);
			deg[x] ++ , deg[y] ++ ;
			sum += z;
		}
		for(int k = 1; k <= n; k++)
			for(int i = 1; i <= n; i++) if(i != k)
				for(int j = 1; j <= n; j++) if(j != i && j != k)
					a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
		int Index = 0;
		for(int i = 1; i <= n; i++) if(deg[i] & 1) {
			odd[Index++] = i;
		}
		for(int i = 0; i < Index; i++)
			for(int j = i+1; j < Index; j++)
				b[i][j] = b[j][i] = a[odd[i]][odd[j]];
		n = Index;
		printf("Case %d: %lld\n", ++Cas, DP((1 << n) - 1) + sum);
	}
	return 0;
}
