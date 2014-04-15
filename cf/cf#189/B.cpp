#include <vector>
#include <deque>
#include <stdio.h>
using namespace std;
#define     MAXN        105

struct Interval { int x, y; } a[MAXN];
vector<int> v[MAXN];
int visit[MAXN];
int n, top, when;
bool path[MAXN][MAXN];
void Insert(int x, int y)
{
    Interval tmp = {x, y};
    a[top] = tmp;
    for(int i = 0; i < top; i++) {
        if((a[i].x < tmp.x && tmp.x < a[i].y) || (a[i].x < tmp.y && tmp.y < a[i].y)) {
            v[top].push_back(i);
            path[top][i] = true;
        }
        if((tmp.x < a[i].x && a[i].x < tmp.y) || (tmp.x < a[i].y && a[i].y < tmp.y)) {
            v[i].push_back(top);
            path[i][top] = true;
        }
    }
    top++;
}
bool Query(int l, int r)
{
    when++;
    deque<int> Q;
    Q.push_back(l);
    visit[l] = when;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        for(int Size = v[u].size(), i = 0; i < Size; i++) {
            int t = v[u][i];
            if(visit[t] == when) continue;
            visit[t] = when;
            if(t == r || path[t][r]) {
                path[l][r] = true;
                return true;
            }
            path[l][t] = true;
            Q.push_back(t);
        }
    }
    return false;
}
int main()
{
    int cases, op, x, y;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d%d", &op, &x, &y);
        x--, y--;
        if(op == 1) {
            Insert(x, y);
        } else {
            if(path[x][y]) printf("YES\n");
            else printf(Query(x, y) ? "YES\n" : "NO\n");
        }
    }
    return 0;
}
