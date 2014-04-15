/*
    序列题
    题意：给出一个序列，若干区间[l,r]，问序列要怎么重新排列，才能让区间和最大，输出最大区间和。

    特殊线段数法      其实名字也不能这么叫，不过我不知道叫什么。。。
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        200005
long long a[MAXN], add[MAXN], sum[MAXN];
long long n;
int main()
{
    int query;
    scanf("%I64d%d", &n, &query);
    for(long long i = 0; i < n; i++) scanf("%I64d", &a[i]);
    while(query--) {
        long long left, right;
        scanf("%I64d%I64d", &left, &right);
        left--, right--;
        add[left]++;
        add[right+1]--;
    }
    long long tmp = 0;
    for(long long i = 0; i < n; i++) {
        tmp += add[i];
        sum[i] += tmp;
    }
    sort(a, a+n);
    sort(sum, sum+n);
    long long ans = 0;
    for(long long i = 0; i < n; i++) {
        ans += a[i] * sum[i];
    }
    printf("%I64d\n", ans);
    return 0;
}
