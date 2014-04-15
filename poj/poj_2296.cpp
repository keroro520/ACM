/*
    2-SAT   中等题

    未AC，因为不知道size为奇数的时候应该怎么办，题目没说。我是在二分的时候要求mid一定为偶数，也正是因为这一点WA了...
    对拍了一下，大概只有这一点了，因为结果都之差1.
*/
#include <stdio.h>
#include <stack>
#include <vector>
#include <string.h>
using namespace std;
#define     MAXN    202

struct Label { int x, y; } label[MAXN];
int dfn[MAXN], low[MAXN];
bool in_stack[MAXN];
stack<int> S;
vector<int> v[MAXN];
int n, order;

void init() ;
void Tarjan(int now);
void build(int standard);
bool solve(int standard);
bool inter_ver(int x1, int x2, int x3, int x4) {
    return (x1 < x3 && x3 < x2) || (x1 < x4 && x4 < x2);
}
bool inter_hor(int y1, int y2, int y3, int y4) {
    return (y1 < y3 && y3 < y2) || (y1 < y4 && y4 < y2);
}
int hash(int x) { return x + n; }

int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) 
            scanf("%d%d", &label[i].x, &label[i].y);
        int left = 0, right = 20000, mid, ans = 0;
        while(left < right) {
            mid = (left + right) >> 1;
            mid += (mid & 1);       //保证mid是偶数@@ 正确性？
            if(solve(mid)) {
                ans = mid;
                left = mid + 1;
            } else right = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
bool solve(int standard)
{
    init();
    build(standard);   
    for(int N = hash(n), i = 0; i < N; i++) if(dfn[i] == -1) Tarjan(i);
    for(int i = 0; i < n; i++) if(low[i] == low[hash(i)]) return false;
    return true;
}
void build(int standard)
{
    int half = (standard >> 1);
    for(int i = 0; i < n; i++) {
        int x1 = label[i].x, y1 = label[i].y;
        for(int j = i+1; j < n; j++) {
            int x2 = label[j].x, y2 = label[j].y;
            if(!inter_ver(x1-half, x1+half, x2-half, x2+half)) 
                continue;  //水平没有相交,continue
            //up - up
            if(inter_hor(y1, y1+standard, y2, y2+standard)) {
                v[i].push_back(hash(j));
                v[j].push_back(hash(i));
            }
            //up - down
            if(inter_hor(y1, y1+standard, y2-standard, y2)) {
                v[i].push_back(j);
                v[hash(j)].push_back(hash(i));
            }
            //down - up
            if(inter_hor(y1-standard, y1, y2, y2+standard)) {
                v[hash(i)].push_back(hash(j));
                v[j].push_back(i);
            }
            //down - down
            if(inter_hor(y1-standard, y1, y2-standard, y2)) {
                v[hash(i)].push_back(j);
                v[hash(j)].push_back(i);
            }
        }
    }
}
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
void init() 
{
    order = 1;
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(in_stack, false, sizeof(in_stack));
    for(int i = 0; i < hash(n); i++) v[i].clear();
    while(!S.empty()) S.pop();
}
