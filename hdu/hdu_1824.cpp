/*
    2-SAT

    构图: 其实可以把一个队的非队长的两个队员看成一个, 所以p[x] = y就够了
*/
#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;
#define     MAXN    (1001*3)
#define     MAXM    5001
#define     debug   printf("!\n")
int n, m, order;
stack<int, vector<int> > S;
vector<int> v[MAXN];
int e[MAXM][2], low[MAXN], dfn[MAXN], p[MAXN];
bool visit[MAXN], in_stack[MAXN];

void Tarjan(int now)
{
    visit[now] = in_stack[now] = true;
    low[now] = dfn[now] = order++;
    S.push(now);
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
        if(in_stack[tmp])
            low[now] = min(low[now], low[tmp]);
        else if(!visit[tmp]) {
            Tarjan(tmp);
            low[now] = min(low[now], low[tmp]);
        }
    }

    if(low[now] == dfn[now]) {
        int tmp;
        do {
            tmp = S.top();
            S.pop();
            in_stack[tmp] = false;
        } while(tmp != now);
    }
}

void init()
{
    order = 0;
    while(!S.empty()) S.pop();
    for(int i = 0; i < 3*n; i++) {
        v[i].clear();
        visit[i] = false;
        in_stack[i] = false;
    }
}

int main()
{
    int x, y, z;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d", &x, &y, &z);
            p[x] = y;
            p[y] = p[z] = x;
            v[y].push_back(z);
            v[z].push_back(y);
            e[i][0] = x;
            e[i][1] = y;
        }

        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            v[x].push_back(p[y]);
            v[y].push_back(p[x]);
        }

        for(int i = 0; i < 3*n; i++) {
            if(!visit[i]) Tarjan(i);
        }
        bool flag = true;
        for(int i = 0; i < n; i++) 
            if(low[e[i][0]] == low[e[i][1]]) {
                flag = false;
                break;
            }
        puts(flag ? "yes" : "no");
    }
    return 0;
}   
