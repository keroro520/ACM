/*
    最大流  经典题  神构造

    题意：有 M 个猪圈（M ≤ 1000），每个猪圈里初始时有若干头猪。
        一开始所有猪圈都是关闭的。
        依次来了 N 个顾客（N ≤ 100），每个顾客分别会打开指定的几个猪圈，从中买若干头猪。
        每个顾客分别都有他能够买的数量的上限。
        每个顾客走后，他打开的那些猪圈中的猪，都可以被任意地调换到其它开着的猪圈里，然后所有猪圈重新关上。
        问总共最多能卖出多少头猪。

    题解：http://imlazy.ycool.com/post.2059102.html

    构造很经典

    "
    在面对网络流问题时，如果一时想不出很好的构图方法，不如先构造一个最直观，或者说最“硬来”的模型，
    然后再用合并节点和边的方法来简直化这个模型。经过简化以后，好的构图思路自然就会涌现出来了。
    这是解决网络流问题的一个好方法。
    "
*/
#include <vector>
#include <deque>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    105
#define     MAXM    10005
#define     INF     999999999
int cap[MAXM], key[MAXN][MAXM], buy[MAXN], path[MAXN][MAXN], f[MAXN][MAXN];
vector<int> v[MAXM];
bool visit[MAXN];
int pre[MAXN];
int house, people;

bool EK(int src, int sink) ;
void build(int src, int sink) ;
int max_flow(int src, int sink) ;

int main()
{
    scanf("%d%d", &house, &people);
    for(int i = 1; i <= house; i++) scanf("%d", &cap[i]);
    for(int i = 1; i <= people; i++) {
        scanf("%d", &key[i][0]);
        for(int j = 1; j <= key[i][0]; j++) {
            scanf("%d", &key[i][j]);
            v[key[i][j]].push_back(i);
        }
        scanf("%d", &buy[i]);
    }
    int src = 0, sink = people+1;
    build(src, sink);
    printf("%d\n", max_flow(src, sink));
    return 0;
}

bool EK(int src, int sink)
{
    memset(visit, false, sizeof(visit));
    deque<int> Q;
    Q.push_back(src);
    visit[src] = true;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        for(int v = 0; v <= sink; v++) 
            if(!visit[v] && path[u][v] > f[u][v]) {
                visit[v] = true;
                pre[v] = u;
                if(v == sink) return true;
                Q.push_back(v);
            }
    }
    return false;
}
int max_flow(int src, int sink) 
{
    int ans = 0;
    while(EK(src, sink)) {
        int Min = INF, v = sink;
        do {
            Min = min(Min, path[pre[v]][v] - f[pre[v]][v]);
            v = pre[v];
        } while (v != src);
        ans += Min;
        v = sink;
        do {
            f[pre[v]][v] += Min;
            f[v][pre[v]] -= Min;
            v = pre[v];
        } while(v != src);
    }
    return ans;
}

void build(int src, int sink)
{
    for(int i = 1; i <= house; i++) if(!v[i].empty()) {
        path[src][v[i][0]] += cap[i];
        for(int Size = v[i].size(), j = 1; j < Size; j++)
            path[v[i][j-1]][v[i][j]] = INF;
    }
    for(int i = 1; i <= people; i++) path[i][sink] = buy[i];
}
