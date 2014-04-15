#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define         debug       printf("!\n")
#define         MAXN        100005
#define         low(x)      ((x) & (-(x)))
int first[MAXN], last[MAXN], pre[MAXN], next[MAXN], pos[MAXN], num[MAXN];
int head[MAXN], c[MAXN], a[MAXN], ans[MAXN], _index[MAXN], in[MAXN], out[MAXN];
struct Quetion {
    int l, r, id; 
} que[MAXN];
struct Edge {
    int v, next;
} edge[MAXN*2];

int K, n, query, Index, edge_num;

void get_next(int K)
{
    memset(pre,  0, sizeof(pre));
    memset(next, 0, sizeof(next));
    memset(num , 0, sizeof(num));
    memset(last, 0, sizeof(last));
    memset(first,0, sizeof(first));
    for(int i = 1; i <= n; i++) {
        int x = a[_index[i]];
        if(first[x] == 0) first[x] = i;
        num[i] = num[last[x]] + 1;
        next[last[x]] = i;
        last[x] = i;
        if(num[i] >= K) pre[i] = first[x], first[x] = next[first[x]];
    }
}
bool cmp(const Quetion & a, const Quetion & b) {
    return a.r < b.r;
}
void build(int u)
{
    _index[Index] = u;
    in[u] = out[u] = Index++;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(!in[v]) {
            build(v);
            out[u] = out[v];
        }
    }
}
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void init()
{
    edge_num = 0;
    Index = 1;
    memset(head, -1, sizeof(head));
    memset(c,     0, sizeof(c));
    memset(in,    0, sizeof(in));
}
void Update(int pos, int add)
{
    while(pos) {
        c[pos] += add;
        pos -= low(pos);
    }
}
int Query(int pos, int end)
{
    int sum = 0;
    while(pos <= end) {
        sum += c[pos];
        pos += low(pos);
    }
    return sum;
}
int main()
{
    int cases, Cas = 0, x, y;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &K);
        init();
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for(int i = 1; i <  n; i++) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }
        build(1);
        get_next(K);
        scanf("%d", &query);
        for(int i = 0; i < query; i++) {
            scanf("%d", &x);
            que[i].l = in[x], que[i].r = out[x];
            que[i].id = i;
        }
        sort(que, que+query, cmp);
        int j = 0;
        for(int i = 1; i <= n; i++) {
            int x = a[_index[i]];
            if(pre[i]) {
                Update(pre[i], 1), Update(pre[pos[x]], -1);
                //printf("%d : (pre[pos[x]] = %d ) : ", i, pre[pos[x]]);
                //for(int h = 1;  h <= n; h++) printf("%d  ", c[h]);
                //printf("\n");
            }
            pos[x] = i;
            while(j < query && que[j].r == i) {
               ans[que[j].id] = Query(que[j].l, i);
               j++;
            }
        }
        printf("Case #%d:\n", ++Cas);
        for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
