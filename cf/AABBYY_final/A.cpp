#include <stdio.h>
#include <map>
#include <limits.h>
using namespace std;
#define     MAXN    300005
map<long long, int> rec;
long long a[MAXN], sum[MAXN];
int n;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%I64d", &a[i]);
        if(a[i] <= 0) sum[i] = sum[i-1];
        else sum[i] = sum[i-1]  + a[i];
        if(!rec[a[i]]) rec[a[i]] = i;
    }
    long long ans = -(LONG_MAX-10);
    int ansi, ansj;
    for(int i = n; i > 0; i--) if(rec[a[i]] != i) {
        int pre = rec[a[i]];
        long long tmp = sum[i-1] - sum[pre] + a[i] * 2;
        if(ans < tmp) {
            ansi = pre;
            ansj = i;
            ans = tmp;
        }
    }
    int tmp = 0;
    for(int i = ansi+1; i < ansj; i++) if(a[i] < 0) tmp++;
//    if(a[ansi] <= 0) ans += a[ansi] * 2;
    printf("%I64d %d\n", ans, n - (ansj + 1 - ansi) + tmp);
    for(int i = 1; i < ansi; i++) printf("%d ", i);
    for(int i = ansi+1; i < ansj; i++) if(a[i] < 0) printf("%d ", i);
    for(int i = ansj+1; i <= n; i++) printf("%d ", i);
    printf("\n");
    return 0;
}
