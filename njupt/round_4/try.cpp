#include <iostream>
#include <cstdio>
const int LMT=102;
using namespace std;
int gra[LMT][LMT],vis[LMT];
int n,m;
void dfs(int u)
{
    vis[u]=1;
    for(int i=1;i<=n;i++)
    if(0==vis[i]&&gra[u][i])dfs(i);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        gra[u][v]=gra[v][u]=1;
    }
    dfs(1);
    for(int i=1;i<=n;i++)
    if(0==vis[i])
    {
        printf("NO\n");
        return 0;
    }
    if(m==n)printf("FHTAGN!\n");
    else printf("NO\n");
    return 0;
}
