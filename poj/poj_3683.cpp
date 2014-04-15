/*
    2-sat 输出解

    到github里找的代码，当模板用吧    
    **一定要注意判断区间相交呀(inter函数)**  WA了几次!!
*/
#include <string.h>
#include <stdio.h>
#include <deque>
#include <vector>
#include <stack>
using namespace std;
#define     MAXN    1001*2
#define     debug   printf("!\n")
int n, top, Index;
int low[MAXN], dfn[MAXN], belong[MAXN], color[MAXN], indegree[MAXN];
int s[MAXN], t[MAXN], d[MAXN];
bool in_stack[MAXN];
stack<int> S;
deque<int> q1;
vector<int> v[MAXN], rv[MAXN], topo;

void init();
void topsort();
void output(int x, int y);
void Tarjan(int now);
void build();
int  hash(int x) { return x < n ? x + n : x - n; }

int main()
{
    int x, x1, y, y1;
    scanf("%d", &n);
        init();
        for(int i = 0; i < n; i++) {
            scanf("%d:%d%d:%d%d", &x, &x1, &y, &y1, &d[i]);
            s[i] = 60 * x + x1;
            t[i] = 60 * y + y1;
        }
        build();  
        for(int N = 2*n, i = 0; i < N; i++) if(dfn[i] == -1) Tarjan(i);
        bool flag = true;
        for(int i = 0; i < n; i++) if(belong[i] == belong[hash(i)]) {
            flag = false;
            break;
        }
        if(flag == false) {
            printf("NO\n");
            //continue;
        } else printf("YES\n");
        for(int N = 2*n, i = 0; i < N; i++)
            for(int Size = v[i].size(), j = 0; j < Size; j++) {
                int tmp = v[i][j];
                if(belong[i] == belong[tmp]) continue;
                rv[belong[tmp]].push_back(belong[i]);
                indegree[belong[i]]++;
            }
        topsort();
        for(int i = 0; i < n; i++)
            if(color[belong[i]] == 'R') output(s[i], s[i]+d[i]);
            else output(t[i]-d[i], t[i]);
    
    return 0;
}
void del(int u)
{
    color[u] = 'B';
    for(int Size = rv[u].size(), i = 0; i < Size; i++) {
        int v = rv[u][i];
        if(color[v] == 0) {
            del(v);
        }
    }
}
void topsort()
{
    for(int i = 0; i < top; i++)
        if(indegree[i] == 0) q1.push_back(i);

    while(!q1.empty()) {
        int now = q1.front();
        q1.pop_front();
        topo.push_back(now);
        for(int Size = rv[now].size(), i = 0; i < Size; i++) {
            int tmp = rv[now][i];
            if(--indegree[tmp] == 0) q1.push_back(tmp);
        }
    }

    for(int Size = topo.size(), i = 0; i < Size; i++) {
        int tmp = topo[i];
        if(color[tmp] == 0) {
            color[tmp] = 'R';
            for(int N = 2*n, j = 0; j < N; j++) 
                if(belong[j] == tmp && color[belong[hash(j)]] == 0) {
                    del(belong[hash(j)]);
                }
        }
    }
}
void init()
{
    while(!S.empty()) S.pop();
    q1.clear();
    topo.clear();
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

bool inter(int a, int b, int c, int d)
{
//    return (a <= c && c < b) || (a <= d && d < b);    //WA
    return (a <= c && c < b) || (c <= a && a < d);
}
void outputTime(int x) { printf("%02d:%02d", x/60, x%60); }
void output(int x, int y)
{
    outputTime(x);
    printf(" ");
    outputTime(y);
    printf("\n");
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
void build()
{
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++) {
            if(inter(s[i], s[i]+d[i], s[j], s[j]+d[j])) {
                v[i].push_back(hash(j));
                v[j].push_back(hash(i));
            }
            if(inter(s[i], s[i]+d[i], t[j]-d[j], t[j])) {
                v[i].push_back(j);
                v[hash(j)].push_back(hash(i));
            }
            if(inter(t[i]-d[i], t[i], s[j], s[j]+d[j])) {
                v[hash(i)].push_back(hash(j));
                v[j].push_back(i);
            }
            if(inter(t[i]-d[i], t[i], t[j]-d[j], t[j])) {
                v[hash(i)].push_back(j);
                v[hash(j)].push_back(i);
            }
        }
}
