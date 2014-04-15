/*
    最短路 好题     给定两对{s,t}，问这两条最短路上的最多公共点数。


    思路：题解说“容易验证相交公共点连续“，可是我没尝试证过。。
    我们用dp[i][j] 代表 从点i到点j最短路上最多有多少个点！ 
     那么 map[s1][i]+map[i][j]+map[j][e1]=map[s1][e1] 不就表示i到j的最短路为 s1到e1最短路的子路嘛； 
      我们只需更新dp[i][j]中的最大值即可 


      摘抄：   显然，两条最短路径里面公共的那部分子路径一定
      是连续的（如果一定要间断的话，那么说明有更短的路
      径）。
*/
#include <stdio.h>
#define     MAXN    301
#define     INF     99999999
int dp[MAXN][MAXN], map[MAXN][MAXN];
int n;
void init()
{
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            map[i][j] = INF;
            dp[i][j] = 2;
        }
        dp[i][i] = 1; 
        map[i][i] = 0;
    }
}
int min(int x, int y) { return x < y ? x : y; }
int main()
{
    int m, u, v, w, s1,s2,t1,t2;
    while(scanf("%d%d", &n, &m), n+m) {
        init();
        while(m--) {
            scanf("%d%d%d", &u, &v, &w);
            map[v][u] = map[u][v] = min(map[u][v], w);
        }
        for(int k = 1; k <= n; k++) 
            for(int i = 1; i <= n; i++) if(i != k)
                for(int j = 1; j <= n; j++) if(j != i && j != k) {
                    if(map[i][j] > map[i][k] + map[k][j]) {
                        map[i][j] = map[i][k] + map[k][j];
                        dp[i][j]  = dp[i][k] + dp[k][j] - 1;
                    } else if(map[i][j] == map[i][k] + map[k][j] && dp[i][j] < dp[i][k] + dp[k][j] - 1) {
                        dp[i][j] = dp[i][k] + dp[k][j] - 1;
                    }
                }
        scanf("%d%d%d%d", &s1,&t1,&s2,&t2);
        int ans = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++) 
                if(map[s1][i] + map[i][j] + map[j][t1] == map[s1][t1] &&
                   map[s2][i] + map[i][j] + map[j][t2] == map[s2][t2])
                        if(ans < dp[i][j]) ans = dp[i][j];
        printf("%d\n", ans);
    }
    return 0;                   
}
/*
    http://blog.csdn.net/azheng51714/article/details/8465357
*/
