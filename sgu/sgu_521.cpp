/*
    最长路关键点 可行点 单调队列  好题
    题意：平面上若干点（xi,yi),点i能到达点j当且仅当xi < xj, yi < yj
          那这样的话我们会有很多条最长路，现在要输输出所有可行点和关键点。
          可行点定义：某条最长路经过该点
          关键点定义：所有最长路都经过该点

    思路：可行点好求，方法有几种。问题是关键点。
          neko提出关键点其实就是DAG图上的割点，太麻烦，想别的(之后证明这个想法是错的)

          仔细看neko根据样例画的点图，一起想到了”拦截导弹II”，感觉很类似，于是就根据
          这个往下想。
          按x升序，y降序排好序 （好巧妙）
          从左往右来一次严格最长上升子序列dp1，从右往左来一次严格最长下降子序列dp2
          若dp1[i] + dp2[i] == lis + 1说明i点是可行点
          若dp1[i]这个值只出现过一次，那i点是关键点


          想复用LCS过程，看VJ上有个人的方法挺不错，求完第一次LCS后，逆序再取反，再来
          一次LCS就出来dp2了，不过现在的dp2也是逆序的.
          虚拟出个无穷大点做汇点~
          好吧，我二分又写挫了，还是neko帮调的

    扩展：如果场景改为一个有向图呢？可行点和关键点定义相同。
          现在反倒关键点好求了，就是拓扑分层一边，发现某层只有一个点的话就是关键点
          可行点的话~~随便YY吧

          下面贴个neko刚整理的二分xxx code:
template<class Cmp>
int LIS(Cmp cmp) {
  static int m, end[N];
  m = 0;
  forl(i, 0, n) {
    int pos = lower_bound(end, end+m, a[i], cmp)-end;
    end[pos] = a[i], m += pos==m;
  }
  return m;
}

int main() {
  cout << LIS(less<int>()) << endl;
  cout << LIS(less_equal<int>()) << endl;
  cout << LIS(greater<int>()) << endl;
  cout << LIS(greater_equal<int>()) << endl;

*/
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define     INF     999999999
#define     MAXN    100005
struct Node {
    int x, y, idx;
    bool operator < (const Node &b) const {
        if(x != b.x) return x < b.x;
        return y > b.y;
    }
} a[MAXN];
vector<int> ans1, ans2;
int Q[MAXN], dp1[MAXN], used[MAXN], dp2[MAXN];
int top , n;
int Find(int x)   //严格递增!!!! WA了几发都是二分写错了。。。我是若菜
{
    int l = 0, r = top-1, mid;
    while(l <= r) {
        mid = (l + r) / 2;
        if(x > Q[mid]) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}
void DP(int *f)
{
    top = 0;
    for(int i = 1;  i <= n; i++) {
        int j = Find(a[i].y);
        if(j == top) Q[top++] = a[i].y;
        else Q[j] = a[i].y;
        f[i] = j + 1;
        //printf("! (%d %d %d)  %d\n", a[i].x, a[i].y, a[i].idx, f[i]);
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y), a[i].idx = i;
    n++;
    a[n].x = INF, a[n].y = INF, a[n].idx = n;

    sort(a+1, a+n+1);
    DP(dp1); int lis = dp1[n];
    reverse(a+1, a+n+1);
    for(int i = 1; i <= n; i++) a[i].y = -a[i].y;
    DP(dp2);

    reverse(dp2+1, dp2+n+1);
    reverse(a+1, a+n+1);        //还得倒 =_=

    for(int i = 1; i <= n; i++) if(dp1[i] + dp2[i] == lis+1) {
        ans1.push_back( a[i].idx );
        if(used[ dp1[i] ] == 0) used[ dp1[i] ] = a[i].idx;
        else used[ dp1[i] ] = -1;
    }
    for(int i = 0; i <= n; i++) if( used[i] > 0 ) ans2.push_back(used[i]);
    sort(ans1.begin(), ans1.end());
    sort(ans2.begin(), ans2.end());

    printf("%d", ans1.size()-1);
    for(vector<int> :: iterator it = ans1.begin(); it != ans1.end(); it++)
        if(*it != n) printf(" %d", *it);
    puts("");
    printf("%d", ans2.size()-1);
    for(vector<int> :: iterator it = ans2.begin(); it != ans2.end(); it++)
        if(*it != n) printf(" %d", *it);
    return 0;
}