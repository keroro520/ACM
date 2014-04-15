/*
    简单DP  单调队列
    两端最长上升序列
*/
//lightoj 1421
#include <stdio.h>
#include <algorithm>
using namespace std;
#define         MAXN        100005
#define         MID(l,r)    (((l)+(r)) >> 1)
int Q[MAXN], a[MAXN], f[MAXN], g[MAXN];
int n, top;
int Find(int x)
{
    int l = 0, r = top-1, mid, ans = top;
    while(l <= r) {
        mid = MID(l, r);
        if(x <= Q[mid]) ans = mid, r = mid-1;
        else l = mid + 1;
    }
    return ans;
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        top = 0;
        for(int i = 0; i < n; i++) {
            int j = Find(a[i]);
            if(j == top) Q[top++] = a[i];
            else Q[j] = a[i];
            f[i] = j;
        }
        top = 0;
        for(int i = n-1; i >= 0; i--) {
            int j = Find(a[i]);
            if(j == top) Q[top++] = a[i];
            else Q[j] = a[i];
            g[i] = j;
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int mm = min(f[i], g[i]);
            ans = max(ans, 1 + mm*2);
        }
        printf("Case %d: %d\n", ++Cas, ans);
    }
    return 0;
}
