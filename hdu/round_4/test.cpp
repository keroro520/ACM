#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN        100005
#define     MAXM        100005

int head[MAXN], a[MAXN], result[MAXN];
int n, edge_num;
bool vis[MAXN], boo[MAXN];
struct Edge {
    int l, r, id, next;
} edge[MAXM];
bool cmp(const Edge & a, const Edge & b) {
    if(a.r != b.r) return a.r < b.r;
    else return a.l < b.l;
}
void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head)); 
}
void add_que(int l, int r, int id)
{
    edge[edge_num].r = r;
    edge[edge_num].l = l;
    edge[edge_num].id = id;
    edge[edge_num].next = head[r];
    head[r] = edge_num++;
}
void output(int r, int l, int ans)
{
    for(int k = head[r]; k != -1; k = edge[k].next) {
        int tmp = edge[k].l;
        if(l == tmp) result[edge[k].id] = ans;
        if(tmp > l ) { head[r] = k; break; }
    }
}
int main()
{
    int cases, query, l, r;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);

        init();
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        memset(boo, false, sizeof(boo));
        for(int i = 0; i < query; i++) {
            scanf("%d%d", &l, &r);
            add_que(l, r, i);
            boo[r] = true;
        }
        sort(edge, edge+edge_num, cmp);
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= n; i++) {
            vis[a[i]] = true;
            output(i, i, 1);
            int ans = 1;
            for(int j = i+1; j <= n; j++) {
                if(!(vis[a[j]-1] || vis[a[j]+1])) ans++;
                if(boo[j]) output(j, i, ans);
                vis[a[j]] = true;
            }
            vis[a[i]] = false;
        }
        for(int i = 0; i < query; i++) printf("%d\n", result[i]);
    }
    return 0;
}
