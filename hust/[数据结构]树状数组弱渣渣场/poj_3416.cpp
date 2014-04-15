/*
    树状数组   离线查询   两个树状数组

    题意：给出n个点的座标。不断定座标系，询问一三象限点数与二四象限点数的差。

    思路：再写一遍套路：按右端点离线排序询问，从左往右扫序列，遇到i == query[i].r 则算出 答案。
          总数不边，只需要算出一三象限的点数即可。
          贮存询问，按x座标升序排好。为了方便，我把一般点和询问点都放一块儿，用一个label区分。所以这里升序排好的数组包括一般点和询问点。
          建立两个树状数组c_L[]表y轴右边的点，c_R[]表y轴左边的点。初始时把所有点都加进c_R[]里面。
          开始扫，这里是直接根据点从左往右扫。遇到一般点，直接扔到c_L[]里，并从c_R[]里删除；遇到询问点，根据c_L[]算出第三座标的点数，根据c_R[]算出第一座标的点数。
          因为题目说一般点不会有在轴上的情况，所以还是比较好处理的。

          我做的时候还给y座标离散化了。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN    50005
#define     MAXX    500005
#define     NORMAL  (0)
#define     QUERY   (1)
#define     ABS(x)  ((x) > 0 ? (x) : (-(x)))
#define     low(x)  ((x) & (-(x)))

class Point {
    public :
    int x, y, id;
    bool label;
} a[MAXN + MAXN];
int ans[MAXN], c_l[MAXX], c_r[MAXX];
int y_map[MAXX];        //原本用map，超时，改为数组就过了
int n, m, Index;

bool cmp_x(const Point & a, const Point & b) {
    return a.x < b.x;
}
bool cmp_y(const Point & a, const Point & b) {
    return a.y < b.y;
}
void Update(int * c, int pos, int add)
{
    while(pos <= Index) {
        c[pos] += add;
        pos += low(pos);
    }
}
int Query(int * c, int pos)
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
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &a[i].x, &a[i].y);
            a[i].label = NORMAL;
        }
        for(int i = n; i < m+n; i++) {
            scanf("%d%d", &a[i].x, &a[i].y);
            a[i].label = QUERY;
            a[i].id = i - n;
        }
        memset(y_map, 0, sizeof(y_map));
        sort(a, a+n+m, cmp_y);
        Index = 2;
        y_map[a[0].y] = 1;
        for(int i = 1; i < n+m; i++) if(a[i].y != a[i-1].y) y_map[a[i].y] = Index++;        //离散化
        sort(a, a+n+m, cmp_x);
        memset(c_l, 0, sizeof(c_l));
        memset(c_r, 0, sizeof(c_r));
        int tot = 0;
        for(int i = 0; i < n+m; i++) if(a[i].label == NORMAL) Update(c_r, y_map[a[i].y], 1);    //初始把所有点加进c_L[]里
        for(int i = 0; i < n+m; i++) {
            if(a[i].label == NORMAL) {
                tot++;
                Update(c_l, y_map[a[i].y], 1), Update(c_r, y_map[a[i].y], -1);      //因为点不在轴上，所以还是比较好处理的。
            } else {
                int tmp = Query(c_l, y_map[a[i].y]) + (n - tot) - Query(c_r, y_map[a[i].y]);    //一三象限的点数
                ans[a[i].id] = tmp - (n - tmp);
            }
        }
        for(int i = 0; i < m; i++) printf("%d\n", ABS(ans[i]));
        if(cases) printf("\n");
    }
    return 0;
}
