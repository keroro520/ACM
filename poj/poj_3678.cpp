/*
    2-SAT  有同组元素连边  基础题
*/
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
#define     MAXN    2002
int n, m, order;
int low[MAXN], dfn[MAXN];
bool in_stack[MAXN];
vector<int> v[MAXN];
stack<int> S;

void Tarjan(int now)
{
    in_stack[now] = true;
    low[now] = dfn[now] = order++;
    S.push(now);
    for(int Size = v[now].size(), i = 0; i < Size; i++){
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
            low[tmp] = low[now];
        } while(tmp != now);
    }
}
int hash(int x) { return x + n; }
void init() 
{
    order = 1;
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(in_stack, false, sizeof(in_stack));
    for(int i = 0; i < hash(n); i++) v[i].clear();
    while(!S.empty()) S.pop();
}
void build(int x, int y, int c, string op)
{
    if(op == "AND" && c == 0) {
        v[hash(y)].push_back(x);
        v[hash(x)].push_back(y);
    } else if(op == "AND" && c == 1) {
        v[x].push_back(hash(x));
        v[y].push_back(hash(y));
    } else if(op == "OR"  && c == 0) {
        v[hash(x)].push_back(x);
        v[hash(y)].push_back(y);
    } else if(op == "OR"  && c == 1) {
        v[x].push_back(hash(y));
        v[y].push_back(hash(x));
    } else if(op == "XOR" && c == 0) {
        v[x].push_back(y);
        v[y].push_back(x);
        v[hash(x)].push_back(hash(y));
        v[hash(y)].push_back(hash(x));
    } else if(op == "XOR" && c == 1) {
        v[x].push_back(hash(y));
        v[hash(y)].push_back(x);
        v[hash(x)].push_back(y);
        v[y].push_back(hash(x));
    }
}
void output()
{
    for(int i = 0; i < n; i++) if(low[i] == low[hash(i)]) {
        printf("NO\n");
        return ;
    }
    printf("YES\n");
}
int main()
{
    int x, y, c;
    string op;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &c);
            cin >> op;
            build(x,y,c,op);    
        }
        for(int i = 0; i < hash(n); i++) 
            if(dfn[i] == -1) Tarjan(i);
        output();
    //for(int i = 0; i < n; i++) printf("%d\t%d\n", low[i], low[hash(i)]);
    }
    return 0;
}
