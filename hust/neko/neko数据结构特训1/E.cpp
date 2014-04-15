/*
    树状数组  简单题

    思路：一开始我的思路是c[x]存前面出现过的比x小的数字。可是试了一下不知道怎么计算。
          于是换成了c[x]存前面以 x结尾的递增序列数，这样我们Query()就可以直接求和了，那Update()的value = Query(x-1) + 1，即以x结尾的递增序列总共有 Query(x-1) + 1 + Query(x) .

*/
//lightoj 1085
#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;
#define     low(x)      ((x) & (-(x)))
#define     MAXN        100005
#define     MOD         (1000000007LL)
long long c[MAXN];
struct Node {
    int id, num;
} a[MAXN];
map<int, int> Map;
int n, Index;
long long Query(int pos)
{
    long long sum = 0;
    while(pos) {
        sum += c[pos];
        pos -= low(pos);
    }
    return sum;
}
void Update(int pos, long long value)
{
    while(pos <= Index) {                   //这里写n WA了一次。因为我离散化之后有可能Index = n + 1   !!!
        c[pos] = (c[pos] + value) % MOD;
        pos += low(pos);
    }
}
bool cmp_num(const Node & a, const Node & b)
{
    return a.num < b.num;
}
bool cmp_id(const Node & a, const Node & b)
{
    return a.id < b.id;
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        Map.clear();
        memset(c, 0, sizeof(c));
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i].num);
            a[i].id = i;
        }
        sort(a, a+n, cmp_num);
        Map[a[0].num] = 1;
        Index = 2;
        for(int i = 1; i < n; i++) if(a[i].num != a[i-1].num) {
            Map[a[i].num] = Index++;
        }
        sort(a, a+n, cmp_id);
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            long long tmp = Query(Map[a[i].num] - 1);
            ans = (ans + tmp + 1) % MOD;
            //printf("# %lld\n", tmp);
            Update(Map[a[i].num], tmp+1);
        }
        printf("Case %d: %lld\n", ++Cas, ans);
    }
    return 0;
}
