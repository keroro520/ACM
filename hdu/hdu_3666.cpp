/*
    差分约束  简单题

    题意：给出矩阵{Cij}，问是否存在数列{A} 和 {B}，使得对于矩阵内所有Xij满足: L <= Xij * Ai / Bj <= U 

    思路：构图还不错。用log把乘除变成加减，就可以差分约束来做了。我用的是SPFA+stack求最短路，最长路应该也是可以的。没有建源点，直接一开始把所有点push进去...  14xx ms 过挺险的~

*/
#include <string.h>
#include <stdio.h>
#include <math.h>

#define     MAXN    802
#define     INITIAL 1000.0
int N, M, L, U;
double edge[MAXN][MAXN];
double dis[MAXN];
bool visit[MAXN];
int times[MAXN];
int S[MAXN];

bool SPFA(int n);
int hash(int x) { return x + N; }
int main()
{
#define     debug printf("!\n")
    double x;
    while(scanf("%d%d%d%d", &N, &M, &L, &U) != EOF) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                scanf("%lf", &x);
                edge[i][hash(j)] = log2(x/L);
                edge[hash(j)][i] = log2(U/x);
            }
        }
        printf(SPFA(M+N) ? "YES\n" : "NO\n");
        //for(int i = 0; i < M+N; i++) printf("%lf\n", dis[i]);
    }
    return 0;
}
bool SPFA(int n)
{
    memset(visit, true, sizeof(visit));
    memset(times, 0, sizeof(times));
    int S_top = 0;
    for(int i = 0; i < n; i++) dis[i] = INITIAL, S[++S_top] = i;
    while(S_top) {
        int u = S[S_top--];
        visit[u] = false;
        int v = u < N ? N : 0;
        int deadline = u < N ? M+N : N;
        for( ; v < deadline; v++) {
            if(dis[v] > dis[u] + edge[u][v]) {
                dis[v] = dis[u] + edge[u][v];
                if(visit[v] == false) {
                    if(++times[v] > N) return false;        //@
                    visit[v] = true;
                    S[++S_top] = v;
                }
            }
        }
    }
    return true;
}
