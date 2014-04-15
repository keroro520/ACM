/*
    差分约束
    建源点就是为了让整个图连通。

    //@ ?? 我在SPFA后面输出了dis[]数组来看，这些值并不符合题目的要求，那为什么整个程序是对的？如果要输出一个解的话怎么写？
    答：因为这里的dis[i]表示的是s1+s2+...+si的和，用第一个样例来说，
    sample input:
        4 2
        1 2 gt 0
        2 2 lt 2
    输出的dis[0--n] : -1 0 0 0 0

    s1+s2+s3 = sum[3] - sum[1-1] = dis[3] - dis[0] = 1 , 满足gt 0
    s2+s3+s4 = sum[4] - sum[2-1] = dis[4] - dis[1] = 0 , 满足lt 2
    所以，{si}的一组解应该为0,1,0,0,0.
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    105
#define     MAXM    100+100
int n, edge_num;
int head[MAXN], times[MAXN], dis[MAXN], visit[MAXN];
int S[MAXN];

bool SPFA(int s, int when);
struct Node { int v, value, next; } edge[MAXM];
void add_edge(int u, int v, int w)
{
    Node tmp = {v, w, -1};
    edge[edge_num] = tmp;
    edge[edge_num].next = head[u];
    head[u] = edge_num;
    edge_num++;
}
void init()
{
    memset(head, -1, sizeof(head));
    edge_num = 0;
}
int main()
{
    int when = 0, m, si, ni, ki;
    char oi[3];

    while(scanf("%d%d", &n, &m), n) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%s%d", &si, &ni, oi, &ki);
            if(0 == strcmp(oi, "gt")) {     //在这里WA了好久，误会了strcmp的返回值
                add_edge(si+ni, si-1, -ki-1);
            } else {
                add_edge(si-1, si+ni, ki-1);
            }
        }
        int src = n+1;
        for(int i = 0; i <= n; i++) add_edge(src, i, 0);
        bool flag = SPFA(src, ++when);
        //for(int i = 0; i <= n; i++)printf("%d  %d\n", i, dis[i]);

        printf(flag ? "lamentable kingdom\n" : "successful conspiracy\n");
    }
    return 0;
}
bool SPFA(int s, int when)
{
    memset(dis, 127, sizeof(dis));
    memset(times, 0, sizeof(times));
    dis[s] = 0;
    visit[s] = when;
    int S_top = 0;
    S[++S_top] = s;
    while(S_top) {
        int u = S[S_top--];
        visit[u] = -1;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if(dis[v] > dis[u] + edge[i].value) {
                dis[v] = dis[u] + edge[i].value;
                if(visit[v] != when) {
                    visit[v] = when;
                    S[++S_top] = v;
                    if(++times[v] > n) return false;
                }
            }
        }
    }
    return true;
}
