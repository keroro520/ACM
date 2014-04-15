#include <vector>
#include <stack>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    8001*2
#define     debug   printf("!\n")
int low[MAXN], dfn[MAXN], belong[MAXN], color[MAXN], indegree[MAXN];
bool in_stack[MAXN];
stack<int> S;
deque<int> Q;
vector<int> v[MAXN], rv[MAXN], ansv;

int N, n, top, Index;
void Tarjan(int now);
void init();
void topsort();



inline hash(int x) { return n + x; }
inline abs (int x) { return x < 0 ? -x : x ; } 
int main()
{
    int Cas = 1, cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &m, &n);
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &a[i].x, &a[i].y);
            if(abs(a[i].x) == abs(a[i].y)) continue;
            exist[abs(a[i].x)].push_back(i);
            exist[abs(a[i].y)].push_back(i);
        }
        
        build();

        for(int N = 2*n, i = 1; i <= N; i++) if(low[i] == -1) Tarjan(i);
        bool flag ;
        for(int i = 1; i <= n; i++) if(belong[i] == belong(hash(i))) {
            flag = false;
            break;
        }
        if(flag == false) {
            printf("Case %d: No\n", Cas++);
            continue;
        } else {
            printf("Case %d: Yes\n", Cas++);
        }

        for(int x = 1; x <= N; x++)
            for(int Size = v[x].size(), j = 0; j < Size; j++) {
                int y = v[x][j];
                if(belong[x] == belong[y]) continue;
                rv[belong[y]].push_back(belong[x]);
                indegree[belong[y]]++;
            }

        topsort();
        for(int N = 2*n, i = 1; i <= N; i++) if(color[belong[i]] == 'R') printf("%d\n", i);
    }
    return 0;
}

void build()
{
    for(int i = 1; i <= n; i++)
        for(int Size = exist[i].size(), j = 0; j < Size; j++)
            for(int k = j+1; k < Size; k++) {
                int u  = exist[i][j], v = exist[i][k];
                if(abs(a[u].x) == abs(a[v].x)) {
                    if(a[u].x == a[v].x) {
                        add_edge(u, v);
                        add_edge(v, u);
                    } else {
                        add_edge(u, hash(v));
                        add_edge(v, hash(u));
                    }
                } else {
                    if(a[u].x == a[v].y) {
                        add_edge(u, hash(v));
                        add_edge(hash(v), u);
                    } else {
                        add_edge(u, v);
                        add_edge(hash(v), hash(u));
                    }
                }
            }
}
void Tarjan(int now)
{
    in_stack[now] = true;
    low[now] = dfn[now] = Index++;
    S.push(now);
    for(int k = head[now]; k != -1; k = edge[k].next) {
        int tmp = edge[k].v;
        if(in_stack[tmp]) low[now] = min(low[now], low[tmp]);
        else if(dfn[tmp] == -1) {
            Tarjan(tmp);
            low[now] = min(low[now], low[tmp]);
        }
    }
    if(dfn[now] == low[now]) {
        int tmp ;
        do {
            tmp = S.top();
            S.pop();
            in_stack[tmp] = false;
            belong[tmp] = top;
        } while(tmp != now);
        top++;
    }
}

void init()
{
    while(!S.empty()) S.pop();
    Q.clear();
    ansv.clear();
    for(int i = 1; i <= n; i++) exist[i].clear();
    for(int i = 0; i < top; i++) rv[i].clear();
    memset(head, -1, sizeof(head));
    memset(color, 0, sizeof(color));
    memset(belong, -1, sizeof(belong));
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(in_stack, false, sizeof(in_stack));
    memset(indegree, 0, sizeof(indegree));
    Index   = 0;
    top     = 0;
    edge_num = 0;
}

