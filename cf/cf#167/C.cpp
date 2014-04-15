/*
    构造题

    题意：题意挺难懂的。http://blog.csdn.net/xindoo/article/details/8927545

*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    100005
long long a[MAXN];
int n;
int main()
{
    int m, w, h;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%I64d", &a[i]);
    scanf("%d", &m);
    long long L = 0;
    while(m--) {
        scanf("%d%d", &w, &h);
        L = max(L, a[w-1]);
        printf("%I64d\n", L);
        L += h;
    }
    return 0;
}
