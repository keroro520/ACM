/*
    2-SAT  输出字典序最小解

    输出解的方法是暴力dfs，看的这儿的：http://blog.csdn.net/sprithy_dream/article/details/8116640
    他是直接上来就dfs，然后dfs无果则说明无解，我是先Tarjan判环，同一组元素在同一个环内的话则无解，结果不难想应该是他比我的快。
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    8005*2
#define     MAXM    20005*2

struct Node { int v, next; } edge[MAXM];
int n, ans_top, S_top, Index, round, edge_num;
int belong[MAXN], low[MAXN], dfn[MAXN], S[MAXN];
bool in_stack[MAXN];
int color[MAXN];
int head[MAXN];
int ans[MAXN];

int hash(int x) { return (x & 1) ? x + 1 : x - 1; }
int min(int x, int y) { return x < y ? x : y ; }
void init()
{
    round = Index = 0;
    S_top = 0;
    edge_num = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(color, 0, sizeof(color));
    memset(in_stack, false, sizeof(in_stack));
}

void add_edge(int u, int v)
{
    Node tmp = {v, -1};
    edge[edge_num] = tmp;
    edge[edge_num].next = head[u];
    head[u] = edge_num;
    edge_num++;
}
void Tarjan(int u)
{
    in_stack[u] = true;
    dfn[u] = low[u] = Index++;
    S[++S_top] = u;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(in_stack[v]) low[u] = min(low[u], low[v]);
        else if(low[v] == -1) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int tmp;
        do {
            tmp = S[S_top--];
            belong[tmp] = round;       
            in_stack[tmp] = false;
        } while(tmp != u);
        round++;
    }
}
bool dfs(int u)
{
    if(color[u] != 0) return color[u] == 1;
    color[u] = 1;
    color[hash(u)] = -1;
    ans[ans_top++] = u;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(!dfs(v)) return false;
    }
    return true;
}

int main()
{
    int m, u, v;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            add_edge(u, hash(v));
            add_edge(v, hash(u));
        }
        for(int i = 1; i <= 2*n; i++) if(low[i] == -1) Tarjan(i);
        bool flag = true;
        for(int i = 1; i <= n; i++) 
            if(belong[i*2-1] == belong[i*2]) {
                flag = false;
                break;
            }
        if(flag == false) {
            printf("NIE\n");
            continue;
        }
        for(int i = 1; i <= n; i++) if(color[2*i-1] == 0) {
            ans_top = 0;
            if(!dfs(2*i-1)) {
                for(int j = 0; j < ans_top; j++) color[ans[j]] = color[hash(ans[j])]= 0;
                ans_top = 0;
                dfs(2*i);
            }
        }
        for(int i = 1; i <= 2*n; i++) if(color[i] == 1) printf("%d\n", i);
    }
    return 0;
}
