/*  
    树状数组应用  两个树状数组  好题

    题意：n个牛站一排，已知它们的声调v[i]和座标x[i]。两只牛i,j想沟通的话，它们必须用同一个声调max(v[i], v[j])，沟通起来耗费的能量为max(v[i], v[j]) * dis(x[i], x[j]). 问这n*(n-1)/2对的牛都交流，总共要耗费多少能量。注意，同一只牛和不同牛交流所用的声调不一定都相同。

    思路：按声调排序，从小到大一个一个插入树状数组，插入牛i之前，先计算之前插入的牛相对于当前牛i的总距离dis，因为当前声调最高的是牛i，所以总ans += dis * v[i].
          然后就自己卡在如何处理相对距离上了，不知道怎么处理。
          看了Discuss后才知道可以用两个树状数组来解决这个问题。再开另一个依然以座标为下标，但元素值表示“出现的次数”的树状数组...表述不太好，就是说Query(x)返回的是当前座标区间[1,x]中的牛的数目，这样就解决了之前卡住的相对距离的问题了。

          
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define         MAXN        20005
#define         MAXX        20005
#define         low(x)      (x & (-(x)))
pair<int , int> cow[MAXN];
long long c[MAXX], num[MAXX];
int n;
long long Query(int pos, long long * c)
{
    long long sum = 0;
    while(pos) {
        sum += c[pos];
        pos -= low(pos);
    }
    return sum;
}
void Update(int pos, int add, long long * c)
{
    while(pos <= 20000) {
        c[pos] += add;
        pos += low(pos);
    }
}
int main()
{
    long long tot = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d%d", &cow[i].first, &cow[i].second);
    sort(cow, cow+n);
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        long long tmp = Query(cow[i].second, c);        //[1,x] 的总距离
        int        m  = Query(cow[i].second, num);      //[1,x] 出现的牛的数目
        ans += (cow[i].second * m - tmp) * cow[i].first + ((tot - tmp) - (cow[i].second * (i - m))) * cow[i].first;//根据相对距离算结果
        Update(cow[i].second, cow[i].second, c);
        Update(cow[i].second, 1, num);
        tot += cow[i].second;
    }
    printf("%I64d\n", ans);
    return 0;
}
