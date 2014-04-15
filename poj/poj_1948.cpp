/*
	二维DP  
	题意：n(n<=40)根棍子，长为ai(ai<=40)，连成一个三角形，使得面积最大（要所有棍子都参与）。
	
	思路：一开始像判定性DP那样预处理出boo[i]是否能到达，然后枚举两条边长搞，这样是错的。如数据： 3 8 23 90  就会WA。因为dp[n]=true,dp[m]=true(n>m)，不代表dp[n-m]也等于true！

		  看数据范围很小。令dp[i][j]表示第一条边长为i，第二条边长为j是否可达。
		  则dp[i][j] = dp[i][j] || (j>=w&&dp[i-w][j]) || (j>=w&&dp[i][j-w])


		  二维DP，二维DP都长怎样呢？
*/
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
#define		MAXN		45
int a[MAXN];
bool f[MAXN*MAXN][MAXN*MAXN];
int n;
double area(int x,int y,int z)  
{  
	if(x+y <= z || x+z <= y || y+z <= x) return -1;
    double p=(x+y+z)/2.0;  
    return sqrt(p*(p-x)*(p-y)*(p-z));  
}  
int main()
{
	while(scanf("%d", &n) != EOF) {
		int sum = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
		int half = sum / 2 ;
		memset(f, false, sizeof(f));
		f[0][0] = true;
		for(int i = 1; i <= n; i++)
			for(int j = half; j >= 0; j--)
				for(int k = j; k >= 0; k--)
					f[j][k] = f[j][k] || (j>=a[i] && f[j-a[i]][k]) || (k>=a[i] && f[j][k-a[i]]);
		double ans = -1;
		for(int j = 1; j <= sum; j++)
			for(int k = 1; k <= sum; k++) if(f[j][k])
				ans = max(ans, area(k, j, sum-k-j));
		if(ans - (-1) <= 0.0001) printf("-1\n");
		else printf("%d\n", (int)(ans*100));
	}
	return 0;
}
