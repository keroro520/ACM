#include <cstdio>

const long long mod=1000000007;

long long c[51][51],dp[210][51];
//dp[i][j]表示用j种颜色染i个格子且每种颜色都出现过的方案数，则dp[i][j]=dp[i][j-1]*j+dp[i-1][j-1]*j

void Init ()
{
	int i,j;
	for (i=1;i<=50;i++)
		c[i][0]=1,c[i][i]=1;
	for (i=1;i<=50;i++) for (j=1;j<i;j++)
		c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	for (i=1;i<=205;i++)
		for (j=1;j<=50;j++)
		{
			if (j==1) dp[i][j]=1;
			else dp[i][j]=dp[i-1][j]*j+dp[i-1][j-1]*j;
			dp[i][j]%=mod;
		}

	printf("# %d\n", c[5][1]);
}

int main ()
{
	int T,n,m,k;
	scanf("%d",&T);
	Init ();
	for (int Cas=1;Cas<=T;Cas++)
	{
		scanf("%d%d%d",&n,&m,&k);
		if (n==0 && m==0)
		{
			printf("Case %d: %d\n",Cas,k);
			continue;
		}
		n++,m++;
		long long ans=0;
		int x=(n+1)/2*((m+1)/2)+n/2*(m/2);//坐标为偶的个数
		int y=n*m-x;
		for (int i=1;i<k;i++)
			for (int j=1;i+j<=k;j++)
				ans=(ans+ (c[k][i]*c[k-i][j])%mod*((dp[x][i]*dp[y][j])%mod) )%mod;
		printf("Case %d: %lld\n",Cas,ans);
	}
	return 0;
}

/*
5
19 19 50
18 18 49
17 16 45
15 4 12
10 2 50

Case 1: 764066247
Case 2: 858252451
Case 3: 106772690
Case 4: 863343629
Case 5: 335018981
*/
