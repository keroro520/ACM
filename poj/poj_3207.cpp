/*
    2-SAT   判定问题

    题意：给出一个圆上的若干点对，要求用线把这些点对连接起来，线可以在完全在圆里面或完全在圆外面，问有没有可能使得所有线段不交叉，相交与点不算交叉

    思路：要是告诉是2-SAT就好做了...-_-||
        构图是以线段为元素来构图，若i,j交叉，即矛盾，则
            x <-> y'
            x'<-> x
            就是双向图啦。
            跟之前的几道题不同的就是它建的是双向边。
*/
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>
#include <stdio.h>
using namespace std;
#define     MAXM    2000

class Line {
    public :
    int s, t;
    void make() {if(s > t) swap(s, t);}
} line[MAXM];
vector<int> v[MAXM];
stack<int> S;
int n, m, order;
int dfn[MAXM], low[MAXM];
bool in_stack[MAXM];

void Tarjan(int x)
{
    in_stack[x] = true;
    dfn[x] = low[x] = order++;
    S.push(x);
    for(int Size = v[x].size(), i = 0; i < Size; i++) {
        int tmp = v[x][i];
        if(in_stack[tmp]) low[x] = min(low[x], low[tmp]);
        else if(dfn[tmp] == -1) {
            Tarjan(tmp);
            low[x] = min(low[x], low[tmp]);
        }
    }
    if(dfn[x] == low[x]) {
        int tmp;
        do {
            tmp = S.top();
            S.pop();
            low[tmp] = low[x];
            in_stack[tmp] = false;
        } while(tmp != x);
    }
}
bool interact(Line a, Line b)
{
    return ((a.s < b.s && b.s < a.t) ^ (a.s < b.t && b.t < a.t)) ;
}
void init()
{
    order = 1;
    memset(low, -1, sizeof(low));
    memset(dfn, -1, sizeof(dfn));
}
int hash(int x) { return x + m; }
int main()
{
    scanf("%d%d", &n, &m);
    init();
    for(int i = 0; i < m; i++) 
        scanf("%d%d", &line[i].s, &line[i].t), line[i].make();
    for(int i = 0; i < m; i++)
        for(int j = i+1; j < m; j++)
            if(interact(line[i], line[j])) {
                v[i].push_back(hash(j));
                v[j].push_back(hash(i));
                v[hash(i)].push_back(j);
                v[hash(j)].push_back(i);
            }
    for(int i = 0; i < hash(m); i++) if(dfn[i] == -1) Tarjan(i);
    bool flag = true;
    for(int i = 0; i < m && flag; i++)
        if(low[i] == low[hash(i)]) flag = false;
    printf(flag ? "panda is telling the truth...\n" : "the evil panda is lying again\n");
    return 0;
}
/*
    http://poj.org/problem?id=3207
*/
