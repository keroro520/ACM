/*
    K最短路  模板题

    题解：http://www.cnblogs.com/acSzz/archive/2012/07/31/2616268.html
*/
#include <stdio.h>
#include <vector>
#include <deque>
#include <queue>
#include <string.h>
using namespace std;
#define     MAXN    1002
#define     INF     9999999
#define     debug   printf("!\n")

int A_star(int start, int end);
void dijkstra(int s, int t);

int dis[MAXN], times[MAXN];
bool visit[MAXN];
int n, K;
vector<int> v[MAXN], rv[MAXN], e[MAXN], re[MAXN];
class KNode {
    public :
    int u, len;
    KNode(int u, int len) : u(u), len(len) { }
    friend bool operator < (const KNode &a, const KNode &b) {
        return a.len + dis[a.u] > b.len + dis[b.u]; //
    }
};

int main()
{
    int x, y, z, m, start, end;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        v[x].push_back(y);
        e[x].push_back(z);
        rv[y].push_back(x);
        re[y].push_back(z);
    }
    scanf("%d%d%d", &start, &end, &K);
    if(start == end) K++;

    dijkstra(end, start);
    if(dis[start] == INF) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", A_star(start, end));
    return 0;
}
int A_star(int start, int end)
{
    memset(times, 0, sizeof(times));
    priority_queue<KNode> Q;
    while(!Q.empty()) Q.pop();
    Q.push(KNode(start, 0));
    while(!Q.empty()) {
        KNode now = Q.top();
        Q.pop();
        int u = now.u;
        int len = now.len;
        times[u]++;
        if(times[end] == K) return len;
        if(times[u] > K) continue;  //
        for(int Size = v[u].size(), i = 0; i < Size; i++) {
            int tmp = v[u][i];
            Q.push(KNode(tmp, len+e[u][i]));
        }
    }
    return -1;
}

void dijkstra(int s, int t)
{
    deque<int> Q;
    Q.clear();
    for(int i = 0; i <= n; i++) dis[i] = INF;
    memset(visit, false, sizeof(visit));
    dis[s] = 0;
    visit[s] = true;
    Q.push_back(s);
    while(!Q.empty()) {
        int now = Q.front();
        Q.pop_front();
        visit[now] = false;
        for(int Size = rv[now].size(), i = 0; i < Size; i++) {
            int tmp = rv[now][i];
            if(dis[now] + re[now][i] < dis[tmp]) {
                dis[tmp] = dis[now] + re[now][i];
                if(!visit[tmp]) {
                    visit[tmp] = true;
                    Q.push_back(tmp);
                }
            }
        }
    }
}
