#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    300005
int a[MAXN], pos[MAXN];
int n;
int solve(int l, int r)
{
    int ans = 1;
    for(int i = l+1; i <= r; i++) {
        ans += (pos[i] < pos[i-1]);
    }
    return ans;
}
int main()
{
    int query, op, l, r;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]] = i;
    scanf("%d", &query);
    while(query--) {
        scanf("%d%d%d", &op, &l, &r);
        if(op == 2) {
            swap(a[l], a[r]);
            pos[a[l]] = l;
            pos[a[r]] = r;
        } else {
            printf("%d\n", solve(l, r));
        }
    }
    return 0;
}
