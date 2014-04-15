/*
   2-SAT  由于INF定得小了WA了两次 
   

   思路:二分法枚举
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stack>
#include <vector>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    202
#define     INF     0.00001
struct Node {
    int x, y;
} a[MAXN];
stack<int> S;
vector<int> v[MAXN];
int dfn[MAXN], low[MAXN];
bool in_stack[MAXN];
int n, Index;

bool ok(double left, double right) { return right - left < INF; }
double square(int x) { return x * x * 1.0; }
double dis(int i, int j) { return sqrt(square(a[i].x - a[j].x) + square(a[i].y - a[j].y)); }
int hash(int x) { return x + n; }
void Tarjan(int now);
bool solve(double standard);
void init();

int main()
{
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++) 
            scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[hash(i)].x, &a[hash(i)].y);
        double left = 0, right = 40000.0, mid, ans;
        while(!ok(left, right)) {
            mid = (right + left) / 2;
            if(solve(mid)) {
                ans = mid;
                left = mid;
            } else {
                right = mid;
            }
        }
        printf("%.2lf\n", mid/2);
    }
    return 0;
}
bool solve(double standard)
{
    init();
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++) {
            double dis1 = dis(i,j);
            double dis2 = dis(i,hash(j));
            double dis3 = dis(hash(i),j);
            double dis4 = dis(hash(i),hash(j));
            if(dis1 < standard && dis2 < standard && dis3 < standard && dis4 < standard) return false;
            if(dis1 < standard) {
                v[i].push_back(hash(j));
                v[j].push_back(hash(i));
            }
            if(dis2 < standard) {
                v[i].push_back(j);
                v[hash(j)].push_back(hash(i));
            }
            if(dis3 < standard) {
                v[j].push_back(i);
                v[hash(i)].push_back(hash(j));
            }
            if(dis4 < standard) {
                v[hash(i)].push_back(j);
                v[hash(j)].push_back(i);
            }
        }

    for(int N = hash(n), i = 0; i < N; i++) if(dfn[i] == -1) Tarjan(i);
    for(int i = 0; i < n; i++) if(low[i] == low[hash(i)]) return false;
    return true;
}
void init()
{
    Index = 1;
    while(!S.empty())  S.pop();
    memset(low, -1, sizeof(low));
    memset(dfn, -1, sizeof(dfn));
    memset(in_stack, false, sizeof(in_stack));
    for(int N = hash(n), i = 0; i < N; i++) v[i].clear();
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
        int tmp;
        do {
            tmp = S.top();
            S.pop();
            low[tmp] = low[now];
            in_stack[tmp] = false;
        } while(tmp !=  now);
    }
}
