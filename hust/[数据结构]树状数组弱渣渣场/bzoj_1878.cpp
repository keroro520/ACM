/*
    树状数组  区间维护  区间查询  离线查询   经典题

    题意：数组大小为N,  有Q个询问：不断查询区间[L, R]内的不同数字的个数。

    思路：离线存所有询问，按左端点为第一关键字，右端点为第二关键字排序。
          初始化：对于每个数字x第一次出现的位置i，记b[i] = 1，其余的b设为0.

          这样，回答[1, r]时可直接输出sum(b[1],b[2],...,b[r])即可。
          那左端点往后移呢，l = 1, 2,..n，我们就得想办法维护b[]数组。
          方法是，左端点l移到l+1时，b[l]--, b[next[a[l]]]++,   next[i]记录数组里面下一个与a[i]相同的元素位置。我们的目的是为了保证当前以[l+1, oo]这个区间里出现的数字x，只有一个b[i] = 1, a[i] = x.
          这样对于区间[l,r]，我们只要输出sum(b[1],..b[r])即可，因为sum(b[1],...b[l-1])等于0，这是我们在每次左端点移动的时候b[l]--的结果。
          经典树状数组维护区间。


    用pair存询问，直接可以用sort，不用写cmp，可能pair有默认的cmp了吧。

    我看的题解：http://www.dxmtb.com/blog/diff/         (评论里说得比较清晰)
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     low(x)      ((x) & (-(x)))
#define     MAXN        50005
#define     MAXNUM      1000000
#define     MAXM        200000
int c[MAXN], a[MAXN], head[MAXNUM+100], next[MAXN];
int ans[MAXM];
bool used[MAXNUM+100];
int n;

void Update(int pos, int add)
{
    while(pos <= n) {
        c[pos] += add;
        pos += low(pos);
    }
}
int Query(int x)
{
    int sum = 0;
    while(x) {
        sum += c[x];
        x -= low(x);
    }
    return sum;
}
int main()
{
    int x, y, query;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = n; i > 0 ; i--) {
        if(head[a[i]] == -1) {
            head[a[i]] = i;
            next[i] = -1;
        } else next[i] = head[a[i]], head[a[i]] = i;
    }
    map<int, bool> used;
    for(int i = 1; i <= n; i++) if(!used[a[i]]) {
        used[a[i]] = true;
        Update(i, 1);
    }
    scanf("%d", &query);
    vector< pair< pair<int, int>, int> > quetion(query);
    int m = query;
    while(query--) {
        scanf("%d%d", &x, &y);
        quetion[query].first.first  = x;
        quetion[query].first.second = y;
        quetion[query].second = query;
    }
    sort(quetion.begin(), quetion.end());
    query = 0;
    for(int i = 1; i <= n; i++) {
        while(query < m && quetion[query].first.first == i) {
            ans[quetion[query].second] = Query(quetion[query].first.second);
            query++;
        }
        Update(i, -1);
        if(next[i] != -1) Update(next[i], 1);
    }
    for(int i = m-1; i >= 0; i--) printf("%d\n", ans[i]);
    return 0;
}
