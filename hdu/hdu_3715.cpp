/*
    2-SAT  二分求最佳

    给出一个递归表达式， 问最多能递归到第几层？

    思路： 构图：x表0, x'表1
                 c = 0, 则矛盾式子为a=0,b=0，所以可以连边a->b',b->a'
                 c = 1,   矛盾式为a=1,b=0或a=0,b=1,可以连边a'->b',b->a,a->b,b'->a
                 c = 2,   矛盾式为a=1,b=1,可以连a'->b,b'->a


           求最优：如果用线性地i=1~m来扫的话会超时，就用二分法。
*/
#include <vector>
#include <stack>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    5001
#define     MAXM    10002
int a[MAXM], b[MAXM], c[MAXM], dfn[MAXN], low[MAXN], belong[MAXN];
bool in_stack[MAXN];
stack<int> S;
vector<int> v[MAXN];
int n, m, order;

int hash(int x) { return x + n; }
void build(int mid)
{
    for(int i = 0; i <= mid; i++) {
        if(c[i] == 0) {
            v[a[i]].push_back(hash(b[i]));
            v[b[i]].push_back(hash(a[i]));    //@要搞成双向边吗?
        } else if(c[i] == 1) {
            v[a[i]].push_back(b[i]);
            v[hash(b[i])].push_back(hash(a[i]));
            v[b[i]].push_back(a[i]);
            v[hash(a[i])].push_back(hash(b[i]));
        } else {
            v[hash(a[i])].push_back(b[i]);
            v[hash(b[i])].push_back(a[i]);
        }
    }
}
void init()
{
    order = 1;
    for(int i = 0, N = hash(n); i < N; i++) v[i].clear();
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(belong, -1, sizeof(belong));
    memset(in_stack, false, sizeof(in_stack));
}
void Tarjan(int now)
{
    in_stack[now] = true;
    low[now] = dfn[now] = order++;
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
            low[tmp] = low[now];        //!!! 忘了这一步WA了好久好久！！！！
        } while(tmp != now);
    }
}

bool solve(int mid)
{
    init();
    build(mid);
    for(int N = hash(n), i = 0; i < N; i++) 
        if(low[i] == -1) Tarjan(i);
    {
        int i ;
        //for(i = 0; i <= mid; i++) 我觉得这句和下一句是一样的
            //if(low[a[i]] == low[hash(a[i])] || low[b[i]] == low[hash(b[i])]) break;
        for(int i = 0; i < n; i++)
            if(low[i] == low[hash(i)]) return false;
        return true;
    }
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++)
            scanf("%d%d%d", &a[i], &b[i], &c[i]);
        int left = 0, right = m, mid, ans = 0;
        while(left <= right) {
            mid = (left+right) >> 1;
            if(solve(mid)) {
                ans = mid;
                left = mid + 1;
            } else right = mid-1;
        }
        if(ans >= m) ans = m; else ans++;
        printf("%d\n", ans);
    }
    return 0;
}
/*
2-sat 基本是有三类题型，一种只判定解是否存在，一种判定+二分答案求最佳，一种判定解并输出其中一组解。
*/
