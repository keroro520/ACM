/*
    最短路  模板题
*/
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;
#define     start   0
#define     end     1002
#define     INF     9999999
#define     MAXN    1004
vector<int> v[MAXN], e[MAXN];
int  dis[MAXN];
bool visit[MAXN];
void init()
{
    for(int i = 0; i <= end; i++) {
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
    while(true) {
        int min = INF, mini = -1;
        for(int i = 0; i <= end; i++) if(visit[i] == false && dis[i] < min) {
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
int main()
{
    int T, S, D, x, y, z;
    while(scanf("%d%d%d", &T, &S, &D) != EOF) {
        init();
        while(T--) {
            scanf("%d%d%d", &x, &y, &z);
            v[x].push_back(y);
            v[y].push_back(x);
            e[x].push_back(z);
            e[y].push_back(z);
        }
        while(S--) {
            scanf("%d", &x);
            v[start].push_back(x);
            e[start].push_back(0);
        }
        while(D--) {
            scanf("%d", &x);
            v[x].push_back(end);
            e[x].push_back(0);
        }
        dijkstra(start, end);;
        printf("%d\n", dis[end]);
    }
    return 0;
}
