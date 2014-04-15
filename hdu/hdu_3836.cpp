/*
    Tarjan缩点...其它略
*/
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
#define     MAXN    20001

int n, top, index;
int belong[MAXN], indegree[MAXN], outdegree[MAXN], low[MAXN], dfn[MAXN];
bool visit[MAXN], in_stack[MAXN];
vector<int> v[MAXN];
stack<int, vector<int> > S;
int  calc()
{
    for(int i = 1; i <= n; i++)
        for(int Size = v[i].size(), j = 0; j < Size; j++) {
            int tmp = v[i][j];
            if(belong[i] == belong[tmp]) continue;
            indegree [belong[tmp]]++;
            outdegree[belong[i]]++;
        }
    int notindegree = 0, notoutdegree = 0;
    for(int i = 0; i < top; i++) {
        notindegree  += (indegree[i]  == 0);
        notoutdegree += (outdegree[i] == 0);
    }
    return notindegree > notoutdegree ? notindegree : notoutdegree;
}

void Tarjan(int now)
{
    visit[now] = true;
    in_stack[now] = true;
    S.push(now);
    dfn[now] = low[now] = index++;  //dnf数组是可以免掉的, 不过为了清晰~~
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
        if (!visit[tmp]){ 
            Tarjan(tmp);
            low[now] = min(low[now], low[tmp]);
        } else if(in_stack[tmp]) {
            low[now] = min(low[now], low[tmp]); //
        }
    }

    if(dfn[now] == low[now]) {      //若now是root节点   用递推思维去思考~
        int tmp;
        do {
            tmp = S.top();
            S.pop();
            in_stack[tmp] = false;
            belong[tmp] = top;      //其实low[]已经可以担任其职了, 不过这里更明了而已
        } while(tmp != now);
        top++;
    }
}
void init()
{
    index = 0;
    top = 0;
    while(!S.empty()) S.pop();
    for(int i = 0; i <=n; i++) {
        v[i].clear();
        in_stack[i] = false;
        visit[i] = false;
        dfn[i] = 0;
        low[i] = 0;
        belong[i] = 0;
        indegree[i] = 0;
        outdegree[i] = 0;
    }
}

int main()
{
    int m, x, y;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            v[x].push_back(y);
        }
        for(int i = 1; i <= n; i++) 
            if(!visit[i]) Tarjan(i);

        top == 1 ? printf("0\n") : printf("%d\n", calc());
    }
    return 0;
}
