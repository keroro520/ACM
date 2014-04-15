/*
    最短路模板题

    dijkstra  
*/
#include <string.h>
#include <vector>
#include <stdio.h>
using namespace std;
#define     MAXN    102
#define     INF     99999999
int n;
int dis[MAXN];
bool visit[MAXN];
vector<int> v[MAXN], e[MAXN];

void init();
void dijkstra(int s, int t);

int main()
{   
    int m, x, y, z;
    while(scanf("%d%d", &n, &m) , (n+m)) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            v[x].push_back(y);
            e[x].push_back(z);
            v[y].push_back(x);
            e[y].push_back(z);
        }

        dijkstra(1, n);
        printf("%d\n", dis[n]);
    }
    return 0;
}
void init() 
{ 
    for(int i = 1; i <= n; i++) {
        v[i].clear();
        e[i].clear();
    }
}
void dijkstra(int s, int t)
{
    memset(dis, 127, sizeof(dis));
    memset(visit, false, sizeof(visit));
    dis[s] = 0;
    visit[s] = true;
    for(int Size = v[s].size(), i = 0; i < Size; i++) dis[v[s][i]] = e[s][i];
    for(int k = 0; k < n; k++) {
        int min = INF, mini = -1;
        for(int i = 1; i <= n; i++) if(visit[i] == false && min > dis[i]) {
            min  = dis[i];
            mini = i;
        }
        visit[mini] = true;
        if(mini == t) return ;
        for(int Size = v[mini].size(), i = 0; i < Size; i++) {
            int tmp = v[mini][i];
            if(visit[tmp]) continue;
            if(dis[tmp] > dis[mini] + e[mini][i]) dis[tmp] = dis[mini] + e[mini][i];
        }
    }
}
