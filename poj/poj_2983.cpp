/*
    差分约束

    题意：给出两种约束条件，一种是P A B X，意为精确地约束A比B远X个单位；另一种V A B，意为模糊地约束A至少比B远1个单位。是否有可行解？

    好点：两种约束条件，其中Precise约束可以转换为X <= A-B <= X
          有V i i 这种数据，这种数据在SPFA里会WA，在ballman_ford里AC，不过预处理一下就可以了，还是用SPFA.

    试着add_edge的时候换一下u和v的位置，看看结果有什么不同？是否正确，再把最短路换成最长路呢？
*/
#include <stdio.h>
#include <string.h>
#define     debug   printf("!\n")
#define     MAXN    1010
#define     MOD     1010
#define     MAXM    101010*2

struct Node { int v, value, next; } edge[MAXM];
int head[MAXN];
int visit[MAXN], dis[MAXN], times[MAXN];
//int S[MAXN];
int Q[MAXN+MAXN];
int N, edge_num;

void init()
{
    memset(head, -1, sizeof(head));    
    edge_num = 0;
}
void add_edge(int u, int v, int w)
{
    Node tmp = {v, w, -1};
    edge[edge_num] = tmp;
    edge[edge_num].next = head[u];
    head[u] = edge_num;
    edge_num++;
}
bool SPFA(int s, int when);
int main()
{
    char op;
    int when = 0, u, v, w, M;
    while(scanf("%d%d", &N, &M) != EOF) {
        init();
        bool flag = true;
        for(int i = 0; i < M; i++) {
            while(getchar() != '\n') ;
            scanf("%c%d%d", &op, &u, &v);
            if(op == 'P') {
                scanf("%d", &w);
                add_edge(u, v, -w);
                add_edge(v, u, w);
            } else {
                if(u == v) flag = false;
                add_edge(u, v, -1);
            }
        }
        if(!flag) {
            printf("Unreliable\n");
            continue;
        }
        int src = N + 2;        //源点
        for(int i = 0; i <= N; i++) add_edge(src, i, 0);
        printf(SPFA(src, ++when) ? "Reliable\n" : "Unreliable\n");
    }
    return 0;
}
bool SPFA(int s, int when)
{
    memset(times, 0, sizeof(times));
    memset(dis, 128, sizeof(dis));
    dis[s] = 0;
    visit[s] = when;
    //int S_top = 0;
    //S[++S_top] = s;
    int car = 0, cdr = 0;
    Q[++car] = s;
    while(cdr != car) {
        //int u = S[S_top--];
        if((++cdr) == MOD) cdr = 0;
        int u = Q[cdr];
    //printf("%d  %d   -- %d   %d\n", car, cdr, u, dis[u]);
        visit[u] = -1;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if(dis[v] < dis[u] + edge[i].value) {
                dis[v] = dis[u] + edge[i].value;
                if(visit[v] != when) {
                    visit[v] = when;
                    //S[++S_top] = v;
                    if((++car) == MOD) car = 0;
                    Q[car] = v;
                    if(++times[v] == N) return false;
                }
            }
        }
    }
    return true;
}
