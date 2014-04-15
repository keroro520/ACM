#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    100005
int a[MAXN];
int n;
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a, a+n);
    int ans = 0;
    int i;
    for(i = n-1; i >= 0 && a[i] == 4; i--) ans++;
    int j = 0;
    for(i; i >= 0 && a[i] == 3; i--) {
        ans++;
        if(a[j] == 1) j++;
    }
    int sum = 0;
    for(i; i >= j; i--) sum += a[i];
    ans += sum / 4 + (sum % 4 != 0);
    printf("%d\n", ans);
    return 0;
}
