/*
    线段树  扩点 扩线  区间覆盖  好题  

    题意：给出n条平行于Y轴的线段(y', y'', x)，然后3条一组，问有多少组可见线段组。“可见”的定义为，两条线段能由一条水平先连接但不交于其它的线段。“可见线段组”的定义为该组内的3条线段两两可见。


    心得：之前看poj_3225，死活看不懂，跳过了。做这道题，它们的离散化方法是一样的：线段 = 一个闭区间 + 两个端点。而线段树是只存点的，为了解决这个问题我们可以把这个闭区间也化成一个点，这样就可以存入线段树里了。而线段 * 2这一方法正好可以实现这一点。如下图，
        区间[0,2]离散化后就变成这么些点:
        真实的线段:          [0], (0,1), [1], (1,2), [2] ...
        化为线段树里对应的点: 0     1     2     3     4  ...
        

        当然也可以用poj_2528这样的方法来做，不过就是要处理的东西多些，麻烦些。poj_2528的解法是应对区间过大时防止MLE/TLE的解法，跟这道题不一样，这道题的重点是同化区间和点，poj_2528的重点是缩短区间的长度。
        *** 偶数点代表点，奇数代表线段，遇到有线段类的题目（用线段树做）经常要考虑乘以2，表示浮点的线段 ***

    思路：
    
    下面摘抄自大牛们的blog:
    "能明显的感觉到是区间覆盖问题了。但是有一个细节问题，就是中间的水平线不一定经过整点，所以即使这个区间的所有点都被覆盖，也不能说其就不能穿过一条线，于是，可以将所有线段的长度扩大至2倍，这样就解决了这个问题。"
    "从左到右，一次对每条线段，先进行查询，看左边能看见多少条线段，然后进行覆盖，因为很明显，如果一条线段能看见另一条线段，那么这个关系必然是相互的，所以对每条线段，只需要往左看就行了"
    "注意：如 样例 中 ，0 2 2,3 4 2这两条线段，可以看到 2 3之间是没有被覆盖的，但是在线段树中我们看不到这条线段，因为 变成 浮点数了，不能处理，那么我们可以将 坐标 x2，这样就变成 4 6，中间就多出一个点 5 了，就可以判断了。。
    偶数点代表点，奇数代表线段，遇到有线段类的题目（用线段树做）经常要考虑乘以2，表示浮点的线段。。。poj  3225这题类似"
    "注意:由于线段包括端点,如果这条直线y=c刚好穿过某条线段的端点,则情况会变得有些麻烦.可以采用这种方法来做:将上下纵坐标乘2,横坐标不变,改变原来[y,y+1)的节点存储方式,变为[y,y]式,这样,就可以简单地处理端点问题,并且它对于所有情况都有很好的效果.自己画个图就明白了."
*/
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN        8005
#define     MAX_HIGH        8000 * 2
#define     debug       printf("!\n")
#define     MID(x,y)    (((x)+(y))>>1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

struct Line {
    int x, y1, y2;
} line[MAXN];
struct Seg_tree_Node {
    int l, r, label;
} f[MAX_HIGH * 4];
bool path[MAXN][MAXN];
vector<int> vis[MAXN];
int n;

void init()
{
    memset(path, false, sizeof(path));
    for(int i = 1; i <= n; i++) vis[i].clear();
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].label = 0;
    if(l == r) return ; 
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
}
inline bool cmp(const Line & a, const Line & b)
{
    return a.x < b.x;
}
void Query(int u, int l, int r, int now)
{
    if(f[u].label == 0) return;
    else if(f[u].label != -1) {
        if(path[now][f[u].label]) return ;
        path[now][f[u].label] = true;
        vis[now].push_back(f[u].label);
        return ;
    }
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Query(L(u), l, r, now);
    else if(mid < l) Query(R(u), l, r, now);
    else {
        Query(L(u), l, mid, now);
        Query(R(u), mid+1, r, now);
    }
}
void push_down(int u)
{
    f[L(u)].label = f[R(u)].label = f[u].label;
    f[u].label = -1;
}
void Update(int u, int l, int r, int now)
{
    if(l == f[u].l && f[u].r == r) {
        f[u].label = now;
        return;
    }
    if(f[u].label > 0) push_down(u);
    f[u].label = -1;
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, now);
    else if(mid < l) Update(R(u), l, r, now);
    else {
        Update(L(u), l, mid, now);
        Update(R(u), mid+1, r, now);
    }
}
int calc()
{
    int ans = 0;
    for(int x = 1; x <= n; x++)
        for(int Size1 = vis[x].size(), i = 0; i < Size1; i++) {
            int y = vis[x][i];
            for(int Size2 = vis[y].size(), j = 0; j < Size2; j++) {
                int z = vis[y][j];
                if(path[x][z]) ans++;
            }
        }
//    for(int i = 1; i <= n; i++) {
//        printf("# %d : ", i);
//        for(int j = 0; j < vis[i].size(); j++) printf("%d  ", vis[i][j]);
//        printf("\n");
//    }
    return ans;   
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        init();
        build(1, 0, MAX_HIGH);
        for(int i = 1; i <= n; i++) {
            scanf("%d%d%d", &line[i].y1, &line[i].y2, &line[i].x);
            line[i].y1 <<= 1;
            line[i].y2 <<= 1;
        }
        sort(line+1, line+n+1, cmp);
        for(int i = 1; i <= n; i++) {
            Query(1, line[i].y1, line[i].y2, i);
            Update(1, line[i].y1, line[i].y2, i);
        }
        printf("%d\n", calc());
    }
    return 0;
}
