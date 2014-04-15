/*
http://acm.hit.edu.cn/judge/show.php?Contestid=0&Proid=1917
*/
#include <string.h>
#include <stdio.h>
#include <deque>
#include <vector>
#include <stack>
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
int  hash(int x) { return (x & 1) ? x + 1 : x - 1; }

int main()
{
    int m, x, y;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            v[x].push_back(hash(y));
            v[y].push_back(hash(x));
        }
        N = 2 * n;
        for(int i = 1; i <= N; i++) if(dfn[i] == -1) Tarjan(i);
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

        for(int x = 1; x <= N; x++)
            for(int Size = v[x].size(), j = 0; j < Size; j++) {
                int y = v[x][j];
                if(belong[x] == belong[y]) continue;
                rv[belong[y]].push_back(belong[x]);
                indegree[belong[y]]++;
            }

        topsort();
        for(int i = 1; i <= N; i++) if(color[belong[i]] == 'R') printf("%d\n", i);
    }
    return 0;
}

void init()
{
    while(!S.empty()) S.pop();
    Q.clear();
    ansv.clear();
    for(int i = 0; i < top; i++) rv[i].clear();
    for(int N = 2*n, i = 0; i <= N; i++) v[i].clear();
    memset(color, 0, sizeof(color));
    memset(belong, -1, sizeof(belong));
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(in_stack, false, sizeof(in_stack));
    memset(indegree, 0, sizeof(indegree));
    Index   = 0;
    top     = 0;
}

void Tarjan(int now)
{
    in_stack[now] = true;
    low[now] = dfn[now] = Index++;
    S.push(now);
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
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


void del(int x)
{
    color[x] = 'B';
    for(int Size = rv[x].size(), i = 0; i < Size; i++) if(color[rv[x][i]] == 0) del(rv[x][i]);
}
void topsort()
{
    for(int i = 1; i <= N; i++) if(indegree[i] == 0) Q.push_back(i);
    while(!Q.empty()) {
        int x = Q.front();
        Q.pop_front();
        ansv.push_back(x);
        for(int Size = rv[x].size(), i = 0; i < Size; i++) {
            int y = rv[x][i];
            if(color[y] != 0) continue;
            if(--indegree[y] == 0) Q.push_back(y);
        }
    }
    for(int Size = ansv.size(), i = 0; i < Size; i++) {
        int x = ansv[i];
        if(color[x] == 0) {
            color[x] = 'R';
            for(int j = 1; j <= N; j++) if(belong[j] == x && color[belong[hash(j)]] == 0) {
                del(belong[hash(j)]);
            }
        }
    }
}
