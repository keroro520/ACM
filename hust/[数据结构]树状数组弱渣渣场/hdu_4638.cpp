/*
    树状数组 + 离线查询

    题意：给一个1-n的排列，问区间[l, r]里有多少段连续的数字。

    思路：自己想了很久都没想出怎么维护...=_=   
          看了大牛的一句话“我们可以维护一个数组数组或者线段树，对于每加进去的一个数num[i]，对 i 点加1，如果 i 点前存在num[i]-1和num[i]+1”恍然大悟...遂写，AC。
          Update/Query的方向依然是跟一般线段树的方向反着的，我觉得这个方向比较好理解，所以就比较喜欢，虽说运行时间上比顺着慢...
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define         debug       printf("!\n")
#define         MAXN        100005
#define         low(x)      ((x) & (-(x)))

int a[MAXN], pos[MAXN], ans[MAXN], c[MAXN];
int n, query;
struct Quetion {
    int l, r, id;
} que[MAXN];
bool cmp(const Quetion & a, const Quetion & b) {
    return a.r < b.r;
}
void init()
{
    pos[0] = pos[n+1] = n+1;
    memset(c, 0, sizeof(c));
}
void Update(int pos, int add)
{
    while(pos) {
        c[pos] += add;
        pos -= low(pos);
    }
}
int Query(int pos)
{
    int sum = 0;
    while(pos <= n) {
        sum += c[pos];
        pos += low(pos);
    }
    return sum;
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            pos[a[i]] = i;
        }
        for(int i = 0; i < query; i++) {
            scanf("%d%d", &que[i].l, &que[i].r);
            que[i].id = i;
        }
        sort(que, que+query, cmp);
        int j = 0;
        for(int i = 1; i <= n; i++) {
            int x = a[i];
            Update(i, 1);
            if(pos[x-1] < i) Update(pos[x-1], -1);
            if(pos[x+1] < i) Update(pos[x+1], -1);
            while(j < query && que[j].r == i) {
                ans[que[j].id] = Query(que[j].l);
                j++;
            }
        }
        for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
