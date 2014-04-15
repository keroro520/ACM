/*
    :w
*/
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
#define     MAXN    10001
stack <int, vector<int> > S;
vector<int> v[MAXN];
bool in_stack[MAXN];
int dfn[MAXN], low[MAXN];
int n, m, ans;
int index;

void init()
{
    int x, y;
    for(int i = 1; i <= n; i++) {
        v[i].clear();
        dfn[i] = i;
        in_stack[i] = false;
    }
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
    }
}

void Tarjan(int now)
{
    S.push(now);
    in_stack[now] = true;
    dfn[now] = low[now] = index++;
    for(vector<int> :: iterator it = v[now].begin(); it != v[now].end(); it++)
        if(in_stack[*it]) 
            low[now] = min(low[now], dfn[*it]); // ???
        else {
            Tarjan(*it);
            if(ans) return ;
            low[now] = min(low[now], low[*it]);
        }

    if(dfn[now] == low[now]) {
        while(true) {
            ans++;
            if(now == S.top()) break;
            S.pop();
        }
    }
}

int main()
{
    while(scanf("%d%d", &n, &m) && (m+n)) {
        init();

        while(!S.empty()) S.pop();
        ans = 0;
        index = 0;
        Tarjan(1);
        printf(ans == n ? "Yes\n" : "No\n");
    }
    return 0;
}
