//============================================================================
// Name        : ZOJ.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN=1010;
const int INF=0x3f3f3f3f;
struct Node
{
    int x,b;
};
Node node[MAXN];
int dp[MAXN][MAXN][2];
bool cmp(Node a,Node b)
{
    return a.x<b.x;
}
int sum[MAXN];

int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,v,x;
    while(scanf("%d%d%d",&n,&v,&x)==3)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&node[i].x,&node[i].b);
        }
        n++;
        node[n].x=x;
        node[n].b=0;
        sort(node+1,node+n+1,cmp);
        sum[0]=0;
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+node[i].b;
        int tmp;
        for(int i=1;i<=n;i++)
            if(node[i].x==x)
            {
                tmp=i;
                break;
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dp[i][j][0]=dp[i][j][1]=INF;
        dp[tmp][tmp][0]=dp[tmp][tmp][1]=0;
        for(int i=tmp;i>=1;i--)
            for(int j=tmp;j<=n;j++)
            {
                if(i==j)continue;
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(sum[i]+sum[n]-sum[j])*(node[i+1].x-node[i].x));
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(sum[i]+sum[n]-sum[j])*(node[j].x-node[i].x));

                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(sum[i-1]+sum[n]-sum[j-1])*(node[j].x-node[i].x));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(sum[i-1]+sum[n]-sum[j-1])*(node[j].x-node[j-1].x));
            }
        printf("%d\n",v*min(dp[1][n][0],dp[1][n][1]));//本题的v一定要留到后面来乘，中间DP的时候乘可能会溢出，导致WA
    }
    return 0;
}
