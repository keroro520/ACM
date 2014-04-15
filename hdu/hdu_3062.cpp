#include <vector>
#include <stack>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    1001*2
#define     debug   printf("!\n")
vector<int> v[MAXN];
stack<int, vector<int> > S;
int dfn[MAXN], low[MAXN], belong[MAXN];
bool visit[MAXN], in_stack[MAXN];
int n, m, round, order;

void Tarjan(int now)
{
    visit[now] = in_stack[now] = true;
    S.push(now);
    dfn[now] = low[now] = order++;
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
        if(in_stack[tmp])
            low[now] = min(low[now], low[tmp]);     //dfn[tmp]也可以
        else if(!visit[tmp]) {
            Tarjan(tmp);
            low[now] = min(low[now], low[tmp]);
        }
    }
    if(low[now] == dfn[now]) {      //belong是不是可以用low来代替?
        int tmp;
        do {
            tmp = S.top();
            S.pop();
            in_stack[tmp] = false;
            belong[tmp] = round;
        } while(tmp != now);
        round++;
    }
}

void init()
{
    round = 0;
    order = 0;
    while(!S.empty()) S.pop();
    for(int i = 0; i < 2*n; i++) {
        v[i].clear();
        visit[i] = false;
        in_stack[i] = false;
    }
}
int main()
{
    int a1,a2,c1,c2;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d%d", &a1, &a2, &c1, &c2);
            v[(a1<<1) + c1].push_back( ((a2<<1) | 1) - c2 );
            v[(a2<<1) + c2].push_back( ((a1<<1) | 1) - c1 );
        }
        
        for(int i = 0; i < n*2; i++) if(!visit[i]) Tarjan(i);
        bool flag = true;
        for(int i = 0; i < n; i++) 
            //if(belong[i<<1] == belong[(i<<1)+1]) {    low和belong都可以
            if(low[i<<1] == low[(i<<1)+1]) {
                flag = false;
                break;
            }
            
        printf(flag ? "YES\n" : "NO\n");
    }
    return 0;
}
