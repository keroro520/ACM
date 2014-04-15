/*
    2-SAT   输出解
    hdu 1814
    hdu上的是要求输出字典序最小，但这里这个代码是输出任意解的，正确性未知，因为hit oj登陆不上来提交。
    http://www.cnblogs.com/kuangbin/archive/2012/10/05/2712622.html

    等瑕下次在这里提交。。http://acm.hit.edu.cn/hoj/problem/view?id=1917
*/
#include <deque>
#include <stack>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    8002*2
#define     L(x)    (2*x-1)
#define     R(x)    (2*x)
#define     debug   printf("!\n")
void Tarjan(int now);
bool solve();
void topsort();
void init();

stack<int> S;
deque<int> q1, q2;
vector<int> v[MAXN], rv[MAXN];
int dfn[MAXN], low[MAXN], belong[MAXN], color[MAXN], indegree[MAXN];
bool in_stack[MAXN];
int n, Index, top;

int hash(int x) { return (x & 1) ? x + 1 : x - 1; }
int main()
{
    int x, y, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            v[x].push_back(hash(y));
            v[y].push_back(hash(x));
        }
        if(!solve()) {
            printf("NIE\n");
            continue;
        }

        for(int N = 2*n, i = 1; i <= N; i++)
            for(int Size = v[i].size(), j = 0; j < Size; j++) {
                int tmp = v[i][j];
                if(belong[tmp] == belong[i]) continue;
                rv[belong[tmp]].push_back(belong[i]);
                indegree[belong[i]]++;
        }
        for(int i = 0; i < top; i++) if(indegree[i] == 0) q1.push_back(i);
        topsort();
        for(int i = 0; i < top; i++) if(color[i] == 'R')
            for(int N = 2*n, j = 1; j <= N; j++) if(belong[j] == i) printf("%d\n", j);
    }
    return 0;
}

void topsort()
{
    while(!q1.empty()) {
        int x = q1.front();
        q1.pop_front();
        if(color[x] != 0) continue;     //可能吗？有没有可能color[x] == 'B' ??
        color[x] = 'R';
        indegree[x] = -1;
        for(int N = 2*n, i = 1; i <= N; i++) if(belong[i] == x) {
            int gid = belong[hash(i)];
            q2.push_back(gid);
            while(!q2.empty()) {
                int y = q2.front();
                q2.pop_front();
                if(color[y] == 'B') continue;       //因为有可能tmp有多个indegree，这里其实就是判重
                color[y] = 'B';
                for(int Size = rv[y].size(), i = 0; i < Size; i++) {
                    int tmp = rv[y][i];
                    q2.push_back(tmp);
                }
            }
        }

        for(int Size = rv[x].size(), i = 0; i < Size; i++) {
            int tmp = rv[x][i];
            indegree[tmp]--;
            if(indegree[tmp] == 0) q1.push_back(tmp);
        }
    }
}

bool solve()
{
    for(int i = 1, N = 2*n; i <= N; i++) if(dfn[i] == -1) Tarjan(i);
    for(int i = 1; i <= n; i++) if(belong[L(i)] == belong[R(i)]) return false;
    return true;
}
void init()
{
    while(!S.empty()) S.pop();
    q1.clear();  q2.clear();
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
    dfn[now] = low[now] = Index++;
    in_stack[now] = true;
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
        int tmp;
        do {
            tmp = S.top();
            S.pop();
            in_stack[tmp] = false;
            belong[tmp] = top;
        } while(tmp != now);
        top++;
    }
}
