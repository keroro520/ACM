/*
    haha~ 我很奇怪Update/Query的顺序到底受什么影响，有什么必要性。于是拿这道前两天刚做过的题目来开刀，把Update/Query的顺序改一下，竟然还是1A，哈哈~
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define         low(x)      ((x) & (-(x)))
#define         MAXN        50005
#define         MAXM        200005
#define         N           1000005
int a[MAXN], c[N], last[N], pre[MAXN], ans[MAXM];
struct Quetion {
    int l, r, id;
} que[MAXM];
int n, query;

bool cmp(const Quetion & a, const Quetion  b) {
    return a.r < b.r;
}
void Update(int pos, int add)
{
    while(pos) {
        c[pos] += add;
        pos -= low(pos);
    }
}
int Query(int pos) 
{
    int sum = 0;
    while(pos <= N) {
        sum += c[pos];
        pos += low(pos);
    }
    return sum;
}
int main()
{
    
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]), a[i]++;
        pre[i] = last[a[i]];
        last[a[i]] = i;
    }
    scanf("%d", &query);
    for(int i = 0; i < query; i++) {
        scanf("%d%d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que, que+query, cmp);
    int j = 0;
    for(int i = 1; i <= n; i++) {
        Update(pre[i], -1), Update(i, 1);
        while(j < query && que[j].r == i) {
            ans[que[j].id] = Query(que[j].l);
            j++;
        }
    }
    for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
    return 0;
}
