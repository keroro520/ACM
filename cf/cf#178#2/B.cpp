/* dfs 超时 */
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     N   102
#define     INF 99999999
int sum[N];
int n, ans, ver, hor;
struct Book { int t, w; } book[N];
bool cmp(Book a, Book b) { return a.w > b.w; }

void dfs(int now)
{
    if(ver + sum[n] - sum[now-1] < hor) return ;
    if(ver >= ans || hor >= ans) return ;
    if(now == n+1) {
        if(ver >= hor) ans = ver;
        return ;
    }
    ver += book[now].t;
    dfs(now+1);
    ver -= book[now].t;

    hor += book[now].w;
    dfs(now+1);
    hor -= book[now].w;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &book[i].t, &book[i].w);
    }
    sort(book+1, book+n+1,cmp);
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + book[i].t;
    }
    ans = INF;
    ver = hor = 0;
    dfs(0);
    printf("%d\n", ans);
    return 0;
}
