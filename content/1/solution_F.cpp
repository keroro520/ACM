#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN        100005
int a[MAXN], add[MAXN];

int main()
{
    int n, m, l, r, x;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    while(m--) {
       scanf("%d%d%d", &x, &l, &r);
       if(l > r) swap(l, r);
        add[l] += x;
        add[r+1] -= x;
    }
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += add[i];
        a[i] += sum;
    }
    for(int i = 1; i <= n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
