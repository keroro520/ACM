/*
理解好这道题的树状数组所代表的含义是解题的关键，可是网上的题解都没点出其树状数组的含义（难道是大家都觉得太简单了吗=_=），然后我看题解都看不会，这两天切了几道简单的同类型题，有所收获。    反正我第一次想通这类树状数组的含义时是挺orz的...下面记录是建立在对树状数组的Update/Query过程已经有一个感性的理解的条件之上的。


    Update(p, value) 的含义不是更新[1,p]这段区间的最大gcd值
    相应地，c[p]的含义不是[1,p]这段区间的最大gcd值，Query(p)不是表示查询[1,p]这段区间的最大gcd值.

    这几乎是“树状数组+离线询问”这类题目的共性了，这道题中的c[p]表示区间[1..p, i..∞]的最大gcd，即左端点为1到p，右端点为i到无穷大（其中i表示扫描到的当前位置，具体的还得看实现）。相应地Update(pos, value)在含义上应理解为更新[pos, i..∞]的最大gcd值（想一想，为什么）；要理解Update()为什么要赋予如此含义，还得理解好Query()的含义，这里Query(p)的返回值应为“[p, i]的最大gcd”。
     基本上所有解法都是上述定义，不过可以有不同种实现方法。我最近就发现我做过的几道题把它们的Update/Query的方向倒过来，再改改插入/删除的操作，同样可以AC~这个看个人喜好。
      
    
     树状数组+离线的大致套路：按右端点离线排序询问，从左往右扫序列，根据Update/Query的方向进行相应更新，遇到i == query[i].r 则算出 答案。c[p]表示区间[1..p, i..∞]或者[p, i..∞]的和/最值，即左端点为1到p，右端点为i到无穷大。pre[0]是堆拉圾的地方.


本题的解法网上已有很多，不赘述了，其实只要理解好树状数组的含义，再看题解，是很简单的。
*/
#include <algorithm>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;
#define         MAXN        50005
#define         N           50000
#define         low(x)      ((x) & (-(x)))

int a[MAXN], c[MAXN], ans[MAXN], pre[MAXN];
struct Quetion {
    int l, r, id;
} que[MAXN];
vector<int> factor[MAXN];
int n, query;

void get_factor()
{
    for(int i = 1; i <= N; i++)
        for(int j = i; j <= N; j += i)
            factor[j].push_back(i);
}
bool cmp(const Quetion & a, const Quetion & b) {
    return a.r < b.r;
}
void init()
{
    memset(c, 0, sizeof(c));
    memset(pre, 0, sizeof(pre));
}
void Update(int pos, int value)
{
    while(pos) {                    //TODO   注意方向！！！
        c[pos] = max(c[pos], value);
        pos -= low(pos);
    }
}
int Query(int pos)
{
    int value = 0;
    while(pos <= n) {               //TODO   注意方向！！！
        value = max(value, c[pos]);
        pos += low(pos);
    }
    return value;
}
int main()
{
    int cases;
    get_factor();
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        init();
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &query);
        for(int i = 0; i < query; i++) {
            scanf("%d%d", &que[i].l, &que[i].r);
            que[i].id = i;
        }
        sort(que, que+query, cmp);
        int j = 0;
        for(int i = 1; i <= n; i++) {
            int & x = a[i];
            for(int Size = factor[x].size(), k = 0; k < Size; k++) {
                int fac = factor[x][k];
                if(pre[fac] != 0) {
                    Update(pre[fac], fac);
                }
                pre[fac] = i;
            }
            while(j < query && que[j].r == i) {
                ans[que[j].id] = Query(que[j].l);
                j++;
            }
        }
        for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
