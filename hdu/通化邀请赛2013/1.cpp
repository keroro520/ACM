#include <stdio.h>
#include <string.h>
#include <algorithm>
#include<iostream>
using namespace std;
#define		N	22
#define		INF	999999999
int f[N][N][N][N], a[N], b[N], sum[2][N];
bool vis[N][N][N][N];
int n;
int dfs(int i, int j, int k , int h)
{
	//cout<<" ##"<<i<<" "<<j<<" "<<k<<" "<<h<<endl;
	int &x = f[i][j][k][h];
	if(vis[i][j][k][h]) return x;
	vis[i][j][k][h] = true;
	x=-INF;
	if(k==0&&h==0&&i==0&&j==0) return x=0;
	else
	if(k==0&&h==0 && i==j) return x=a[i];
	else
	if(i==0&&j==0 && k==h) return x=b[k];
	else
	if(k==0&&h==0) 
	{
		x=max(max(-dfs(i+1,j,0,0)+a[i],-dfs(i,j-1,0,0)+a[j]),x);
	}
	else
	if(i==0&&j==0)
	{
		x=max(max(-dfs(0,0,k+1,h)+b[k],-dfs(0,0,k,h-1)+b[h]),x);
	}
	else
	if(i==j && k!=h) 
		{
	           x=max(max(max(-dfs(0,0,k,h)+a[i],-dfs(i,j,k+1,h)+b[k]),-dfs(i,j,k,h-1)+b[h]),x);
		}
	else
	if(k==h && i!=j)
		{
		  x=max(max(max(-dfs(i,j,0,0)+b[k],-dfs(i+1,j,k,h)+a[i]),-dfs(i,j-1,k,h)+a[j]),x);
		}
	else
	if(i==j&& k==h)
		{
		 x=max(x,max(-dfs(0,0,k,h)+a[i],-dfs(i,j,0,0)+b[k]));
		}
	else
	{
	x= max(x, max(-dfs(i, j-1, k, h) + a[j], -dfs(i+1, j, k, h) + a[i]));
        x = max(x, max(-dfs(i, j, k, h-1) + b[h], -dfs(i, j, k+1, h) + b[k]));
	}
	
	//printf("# (%d %d %d %d) %d\n", i,j,k,h,x);
	return x;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		int sum=0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]),sum+=a[i];
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]),sum+=b[i];
		memset(vis, false, sizeof(vis));
		int res = dfs(1, n, 1, n);
	//	printf("%d\n", res);
		cout<<(sum+res)/2<<endl;
	}
	return 0;
}
