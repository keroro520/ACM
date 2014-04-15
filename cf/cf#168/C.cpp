/*
    思路题

    题意：给一个序列无重复元素{Ai}，问最多能取出多少个元素组成一个集合，使得该集合最大。

    思路：我开始也是用set做，但是是sort之后从小到大搞，但是这里k和ai都比较大，比较好的方法是从大到小搞，前者用x*k，后者用x/k，就防止了溢出...所以前者会因为溢出而WA.
*/
#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
#define         debug   printf("!\n")
#define         MAXN    100005
set<int> S;
int a[MAXN];
int n;

void Insert(int x)
{
    S.insert(x);
}
set<int> :: iterator Find(int x)
{
    return S.find(x);
}
void Delete(set<int> :: iterator it)
{
    S.erase(it);
}
int main()
{
    int k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        Insert(a[i]);
    }
    sort(a, a+n);
    int ans = 0;
    for(int i = n-1; i >= 0; i--) {
        set<int> :: iterator it = Find(a[i]);
        if(it == S.end()) continue;
        ans++;
        if(a[i] % k != 0) continue;
        it = Find(a[i]/k);
        if(it != S.end()) Delete(it);
    }
    printf("%d\n", ans);
    return 0;
}
