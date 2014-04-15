/*
    KM  二分图带权匹配  
    题意：两个字符串的similarity定义为：
            Similarity(S, T) = sum(Si == Ti) / L
          L = Length(S) = Length(T), i = 1, 2,... L, where sum(Si == Ti) indicates the total number of equal labels in corresponding positions.
          就是算两个串的最大similarity.

    思路：按字母定义点。边权用上式算，其实只要扫一遍即可，在build里面算边权.
*/
//zoj 3425
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <limits.h>
using namespace std;
#define     MAXK    30
#define     MAXN    10005
int n, m, N;
int dis[MAXK][MAXK], link[MAXK], LX[MAXK], LY[MAXK], slack[MAXK], map[2][256];
char a[MAXN], b[MAXN];
bool visx[MAXK], visy[MAXK], boo[256];
void build()
{
    memset(dis, 0, sizeof(dis));
    for(int i = 0; i < N; i++) 
        dis[map[0][a[i]]][map[1][b[i]]] ++;             //算边权
}
bool find(int u)
{
    visx[u] = true;
    for(int v = 0; v < m; v++) if(!visy[v]) {
        int rest = LX[u] + LY[v] - dis[u][v];
        if(rest == 0) {
            visy[v] = true;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
        } else slack[v] = min(rest, slack[v]);
    }
    return false;
}
void KM()
{
    memset(LX, 128, sizeof(LX));
    memset(LY,   0, sizeof(LY));
    memset(link,-1, sizeof(link));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) LX[i] = max(LX[i], dis[i][j]);
    for(int s = 0; s < n; s++) {
        for(int i = 0; i < m; i++) slack[i] = (INT_MAX);
        while(true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(find(s)) break;
            int d = (INT_MAX);
            for(int i = 0; i < m; i++) if(!visy[i]) d = min(d, slack[i]);
            for(int i = 0; i < n; i++) if(visx[i]) LX[i] -= d;
            for(int i = 0; i < m; i++) 
                if(visy[i]) LY[i] += d;
                else slack[i] -= d;
        }
    }
}
inline char rdc() { scanf(" "); return getchar(); }
int main()
{
    int cases, K, M;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d%d", &N, &K, &M);
        memset(boo, false, sizeof(boo));
        m = 0;
        for(int i = 0; i < N; i++) {
            char ch = rdc();
            b[i] = ch;
            if(!boo[ch]) boo[ch] = true, map[1][ch] = m++;
        }
        while(M--) {
            memset(boo, false, sizeof(boo));
            n = 0;
            for(int i = 0; i < N; i++) {
                char ch = rdc();
                a[i] = ch;
                if(!boo[ch]) boo[ch] = true, map[0][ch] = n++;
            }
            build();
            KM();
            int sum = 0;
            for(int i = 0; i < m; i++) if(link[i] != -1) sum += LX[link[i]] + LY[i];
            printf("%.4f\n", sum*1.0/N);
        }
    }
    return 0;
}
