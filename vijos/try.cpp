
/****************************************************
* author:crazy_石头
* Pro:石子合并问题
* algorithm:区间DP
* Time:ms
* Judge Status:Accepted
*******************************************************/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define rep(i,h,n) for(int i=(h);i<=(n);i++)
#define ms(a,b) memset((a),(b),sizeof(a))
#define eps (1e-6)
#define INF 1<<29			//
#define LL __int64
const int maxn=1000+5;
const int maxm=1000000+10;

int dp[maxn][maxn];
int sum[maxn],num[maxn];

inline int dfs(int i,int j)
{
    if(dp[i][j]!=INF)return dp[i][j];

    if(i==j)return dp[i][j]=0;
    if(i+1==j)return dp[i][j]=num[i]+num[j];
    if(i>j)return dp[i][j]=0;

    for(int k=i;k<j;k++)
    dp[i][j]=min(dp[i][j],dfs(i,k)+dfs(k+1,j)+sum[j]-sum[i] + num[i]);//, printf("! [%d,%d,    %d]  %d %d %d\n", i,j,k,dfs(i,k),dfs(k+1,j),sum[j]-sum[i]+num[i]);
    return dp[i][j];
}

int main()
{
    int n;
    while(scanf("%d", &n) != EOF) 
    {
        int m;
        ms(sum,0);
        cin>>num[0];
        sum[0]=num[0];
        for(int i=1;i<n;i++)
        {
            cin>>num[i];
            sum[i]=sum[i-1]+num[i];
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                dp[i][j]=INF;
            }
        }

        int res=dfs(0,n-1);
        printf("%d\n",res);
    }
    return 0;
}
