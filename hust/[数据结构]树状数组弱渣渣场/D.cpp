/*
    二维树状数组

    区间修改，询问单点
    TODO : 到底“区间修改，询问单点” 和 “修改单点，询问区间” 有什么本质上的区别？ poj_2155 与 poj_1195

    心得：先记录“区间修改，询问单点”的理解。
          Update()和一般的树状数组的顺序倒了过来，因为Updtae(x,y,add)是指在[0,0,x,y]这个区间都加上add，所以我们就相当于标记区间一样，在[0,0,x,y]的“关键点”上加上add。为什么标记的时候是向下的顺序？理解了二维树状的构造就能大概理解了。
          二维树状数组的构造:http://fqq11679.blog.hexun.com/21722866_d.html

          Query ()和一般的树状数组的顺序倒了过来，Query(x, y)就是查包含(x,y)这个点的所有区间的add之和。区间修改的时候是在区间上标记，则询问单点的时候就是向上询问包含(x,y)的区间标记之和。


          那一般的“单点修改，区间求和”呢？这种情况是标记点，询问的时候向下询问，即向下把该区间的点的值都加起来，又称前缀和。
          细节上面还没考虑，现在的水平还没办法思考细节，只能感性上理解。
*/
#include <stdio.h>
#include <string.h>
#define     debug       printf("!\n")
#define     low(x)      ((x) & (-(x)))
#define     MAXN        1005
int  c[MAXN][MAXN];
int n;
void Update(int x, int y, int val)
{
    for(int i = x; i > 0; i -= low(i))
        for(int j = y; j > 0; j -= low(j)) 
            c[i][j] += val;
}
int  Query(int x, int y)
{
    int result = 0;
    for(int i = x; i <= n; i += low(i)) 
        for(int j = y; j <= n; j += low(j))
            result += c[i][j];
    return result & 1;
}
int main()
{
    int cases, x1,x2,y1,y2,query;
    char op[5];
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);
        memset(c, false, sizeof(c));
        while(query--) {
            scanf("%s", op);
            if(op[0] == 'Q') {
                scanf("%d%d", &x1, &y1);
                printf("%d\n", Query(x1, y1));
            } else {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                Update(x1-1, y1-1, 1);      //TODO
                Update(x2, y2, 1);
                Update(x1-1, y2, -1);
                Update(x2, y1-1, -1);
            }
        }
        if(cases) printf("\n");
    }
    return 0;
}
