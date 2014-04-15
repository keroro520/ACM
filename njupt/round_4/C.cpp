/*
    心痛呀！！！！数组开小了。。WA了N次，比赛的时候也没发现！！！可是平常我都是MAXN = N+5的呀！！！为什么这次脑抽了没有加5！！！！
    5555555555555555555555555


*/
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <stack>
#define     MAXN    105
#define     MAXM    100*100
using namespace std;

int low[MAXN], dfn[MAXN], head[MAXN], belong[MAXN];
struct Edge { int v, next;} edge[MAXM * 2];
stack<int> S;
int n, edge_num, Order, Index, ans = 0, anso;
bool in_stack[MAXN], visit[MAXM*2];
void init()
{
    edge_num = 0;
    Order = 1;
    Index = 1;
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
    for(int k = head[u]; k != -1; k = edge[k].next) if(!visit[k]){
        visit[k] = visit[k ^ 1] = true;
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
        int tmp = 0;
        Order++;
        do {
            x = S.top();
            S.pop();
            in_stack[x] = false;
            belong[x] = Order;
            tmp++;
        } while(x != u);
        if(tmp > 2) ans++, anso = Order;
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
        add_edge(y, x);
    }
    Tarjan(1);
    //printf("## %d\n", ans);
    if(ans != 1) {
        puts("NO");
        return 0;
    }
    bool flag = true;
    for(int i = 1; i <= n; i++) if(belong[i] == anso) {
        int tmp = 0;
        for(int k = head[i]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(belong[v] == anso) tmp++;
        }
        if(tmp != 2) {flag = false; break;}
    }
    for(int i = 1; i <= n; i++) if(dfn[i] == 0) flag = false;
    puts(flag ? "FHTAGN!" : "NO");
    return 0;
}
