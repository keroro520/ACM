/*
    强连通

    题意：奶牛互相之间有爱慕关系，找到被其它奶牛都喜欢的奶牛的数目

    思路：缩点后，若只有一个点，则答案为n
                  若有多于1个点出度为0，则答案为0
                  否则答案为出度为0的的那个连通块的原点个数
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stack>
using namespace std;
#define     MAXN        10005

struct Edge { int v, next; } edge[50005];
int edge_num, Order, Index, n;
int head[MAXN], low[MAXN], dfn[MAXN], belong[MAXN], out_deg[MAXN];
bool in_stack[MAXN];
stack<int> S;

void init()
{
    edge_num = 0;
    Order = Index = 1;
    memset(head, -1, sizeof(head));
}

void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}

void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
    S.push(u);
    in_stack[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int x;
        do {
            x = S.top();
            S.pop();
            in_stack[x] = false;
            belong[x] = Order;
        } while(x != u);
        Order++;
    }
}
int main()
{
    int x, y, m;
    scanf("%d%d", &n, &m);
    init();
    while(m--) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
    for(int i = 1; i <= n; i++)
        for(int k = head[i]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(belong[i] == belong[v]) continue;
            out_deg[belong[i]]++;
        }
    if(Order == 2) {
        printf("%d\n", n);
        return 0;
    }
    int out_zero = 0;
    for(int i = 1; i < Order; i++) out_zero += (0 == out_deg[i]);
    if(out_zero > 1) {
        printf("0\n");
        return 0;
    }
    int label = 0;
    for(int i = 1; i < Order && !label; i++) if(out_deg[i] == 0) label = i;
    int sum = 0;
    for(int i = 1; i<= n; i++) sum += (belong[i] == label);
    printf("%d\n", sum);
    return 0;
}
