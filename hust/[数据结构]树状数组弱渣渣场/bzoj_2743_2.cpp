/*
    又把一道树状数组+离线查询的题的Update/Query的顺序搞倒过来，AC了~~hiahia
    不过时间上面慢了好几倍...=_= 这是自然的，因为我改了之后还是按从左往右扫的顺序搞，当然会很慢。有心情再把扫描顺序换一下，时间就应该会回来了.
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN        2000007
#define     N           2000000
#define     low(x)      ((x) & (-(x)))
int pre[MAXN], ans[MAXN], c[MAXN], last[MAXN];
struct Quetion {
    int l, r, id;
} que[MAXN];
int n, query, Index;

bool cmp(const Quetion & a, const Quetion & b) {
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
    while(pos <= Index) {
        sum += c[pos];
        pos += low(pos);
    }
    return sum;
}
int main()
{
    int x;
    scanf("%d%*d%d", &n, &query);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &x);
        pre[i] = last[x];
        last[x] = i;
    }
    for(int i = 0; i < query; i++) {
        scanf("%d%d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que, que+query, cmp);
    int j = 0;
    for(int i = 1; i <= n; i++) {
        Index = i;
        Update(pre[i], 1); 
        Update(pre[pre[i]], -1);
        while(j < query && que[j].r == i) {
            ans[que[j].id] = Query(que[j].l);
            j++;
        }
    }
    for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
    return 0;
}
