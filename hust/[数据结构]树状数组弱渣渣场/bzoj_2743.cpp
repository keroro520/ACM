/*
    树状数组  离线查询 好题

    题意：给一序列{A}, 1 <= a[i] <= C. m个询问(l,r)，回答这个区间[l,r]出现了至少两次的数字。

    思路：“HH的项链”加强版。
          预处理:
              离线存询问，按右端点排序。
              记pre[i]为第i朵花前面，与i同色的最靠近i的花的位置。若不存在则pre[i]=0.
          从左往右扫序列{A}，扫到i时，把树状数组中pre[pre[i]]+1 ~ pre[i]这一段上的元素+1:Update(pre[pre[i]]+1, 1), Update(pre[i]+1, -1);
          然后询问以i为右端点的询问中，左端点在树状数组中的值即可:Query(que[j].l);
          注意，回答的答案是区间[1, l]的和，注意这一点会比较好地理解为什么那样Update()


    套路：存询问，按右端点排序，从左往右扫序列，遇到i == query[i].right就回答。
          看题解好久才懂...=_=
*/
//bzoj 2743   heoi 2012
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN        2000005
#define     low(x)      ((x) & (-(x)))
int n, m, C;
int ans[MAXN], pre[MAXN], a[MAXN], c[MAXN], head[MAXN];
struct Quetion {
    int l, r, id;
} que[2000005];

bool cmp(const Quetion & a, const Quetion & b) {
    if(a.r != b.r) return a.r < b.r;
    else return a.l < b.l;      //其实l没必要排序
}
void Update(int pos, int add)
{
    while(pos <= n) {       //误会成C，WA了
        c[pos] += add;
        pos += low(pos);
    }
}
int  Query(int pos)
{
    int sum = 0;
    while(pos) {
        sum += c[pos];
        pos -= low(pos);
    }
    return sum;
}
int main()
{
    scanf("%d%d%d", &n, &C, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pre[i] = head[a[i]];
        head[a[i]] = i;
    }
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que, que+m, cmp);
    int j = 0;
    for(int i = 1; i <= n; i++) {
        Update(pre[pre[i]]+1, 1), Update(pre[i]+1, -1);
        while(j < m && que[j].r == i) {
            ans[que[j].id] =  Query(que[j].l);     // 
            j++;
        }
    }
    for(int i = 0; i < m; i++) printf("%d\n", ans[i]);
    return 0;
}
