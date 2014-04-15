/*
***kuangbin强调：
    1 KM算法用来解决最大权匹配问题： 在一个二分图内，左顶点为X，右顶点为Y，现对于每组左右连接XiYj有权wij，求一种匹配使得所有wij的和最大

    2 也就是最大权匹配一定是完备匹配。如果两边的点数相等则是完美匹配

    3 如果点数不相等，其实可以虚拟一些点，使得点数相等，也成为了完美匹配

***注意几点：
    *1 对于任一条边(i,j)，A[i]+B[j]>=w[i,j]始终成立.
    *2 (A[i]+B[j])是从大试到小的，所以第一次匹配到的结果才是最优匹配.
    *3 我们求当前相等子图的完备匹配失败了，是因为对于某个X顶点，我们找不到一条从它出发的交错路。这时我们获得了一棵交错树，它的叶子结点全部是X顶点。现在我们把交错树中X顶点的顶标全都减小某个值d，Y顶点的顶标全都增加同一个值d，那么我们会发现：
        1）两端都在交错树中的边(i,j)，A[ i ]+B[j]的值没有变化。也就是说，它原来属于相等子图，现在仍属于相等子图
        2）两端都不在交错树中的边(i,j)，A[ i ]和B[j]都没有变化。也就是说，它原来属于（或不属于）相等子图，现在仍属于（或不属于）相等子图
        3）X端不在交错树中，Y端在交错树中的边(i,j)，它的A[ i ]+B[j]的值有所增大。它原来不属于相等子图，现在仍不属于相等子图
        4）X端在交错树中，Y端不在交错树中的边(i,j)，它的A[ i ]+B[j]的值有所减小。也就说，它原来不属于相等子图，现在可能进入了相等子图，因而使相等子图得到了扩大



***KM的相关定理:

    设 G(V,E) 为二部图， G'(V,E') 为二部图的子图。如果对于 G' 中的任何边<x,y> 满足， L(x)+ L(y)== Wx,y，我们称 G'(V,E') 为 G(V,E) 的等价子图或相等子图（是G的生成子图）.
    若由二分图中所有满足A[i]+B[j]=w[i,j]的边(i,j)构成的子图（称做相等子图）有完备匹配，那么这个完备匹配就是二分图的最大权匹配。


***情况：
        KM算法是求最大权完备匹配，如果要求最小权完备匹配怎么办？方法很简单，只需将所有的边权值取其相反数，求最大权完备匹配，匹配的值再取相反数即可。
        KM算法的运行要求是必须存在一个完备匹配，如果求一个最大权匹配(不一定完备)该如何办？依然很简单，把不存在的边权值赋为0。

        KM算法求得的最大权匹配是边权值和最大，如果我想要边权之积最大，又怎样转化？还是不难办到，每条边权取自然对数，然后求最大和权匹配，求得的结果a再算出e^a就是最大积匹配。至于精度问题则没有更好的办法了。


*/
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define     MAXN    210
const int big = 300005;
int link[MAXN], g[MAXN][MAXN];
bool visitx[MAXN], visity[MAXN];
int X[MAXN], Y[MAXN];
int N, rs, slack;

bool find(int u)
{
    visitx[u] = true;
    for(int i = 1; i <= N; i++) if(!visity[i]) {
        int rest = X[u] + Y[i] - g[u][i];           //判断有没有边不是直接查表，而是看X[u] + Y[i] == g[u][i] 
        if(rest == 0) {
            visity[i] = true;
            if(link[i] == -1 || find(link[i])) {
                link[i] = u;
                return true;
            }
        } else slack = min(slack, rest);
    }
    return false;
}
void KM()
{
    memset(X, 0, sizeof(X));
    memset(Y, 0, sizeof(Y));
    for(int i = 1; i <= N; i++) 
        for(int j = 1; j <= N; j++)
            X[i] = max(X[i], g[i][j]);

    for(int i = 1; i <= N; i++) {
        while(true) {
            memset(visitx, false, sizeof(visitx));
            memset(visity, false, sizeof(visity));
            slack = INT_MAX;
            if(find(i)) break;
            else {                                  //如果找不到增广路就更新顶标
                for(int j = 1; j <= N; j++) {
                    if(visitx[j]) X[j] -= slack;
                    if(visity[j]) Y[j] += slack;
                }
            }
        }
    }
}

int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        memset(link, -1, sizeof(link));
        memset(g, 0, sizeof(g));        //没有边的话就设为无穷小，这是必要的.  这里无穷小就算是0
        scanf("%d%d", &N, &rs);
        for(int i = 1; i <= rs; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            c = big - c;
            g[a][b] = max(g[a][b], c);
        }
        KM();
        int ans = 0;
        for(int i = 1; i <= N; i++) {
            ans += big - g[link[i]][i];
        }
        cout << ans << endl;
    }
    return 0;
}
