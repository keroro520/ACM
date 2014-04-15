/*
    二分图带权匹配   拆点    好题

    题意：m家工厂，n个玩具订单，An*m矩阵描述j号工厂生产i号订单的话所需时间，同一时间内一工厂只能生产一个订单的玩具，问加工完所有玩具所话费的时间的最小平均值（话费之间包括等待时间---如果有两个订单在同一家工厂里生产的话，第二个等第一个订单做完所花费的时间）

    思路：做专题的时候看到拆点，于是自然想到把m个工厂拆成m*n个点，但是因为题目要算等待时间，所以就不知道怎么建图。

          看题解知道，若有t1,t2,t3号玩具订单要依次在f号工厂做，则所花费的时间 = t1 + (t1+t2) + (t1+t2+t3)，而巧妙就巧妙在这里，***这个式子可以再变换成 3*t1 + 2*t2 + t3  ***
          到这里换个思维建图，把订单执行的顺序反过来思考，这里用exec_time[f]来表示f上总花费时间：若t3订单最后一个执行，则exec_time[fac]里面只包括一个t3。若t2是倒数第二个执行，则exec_time[f]包括2*t2 ... 扩展开，订单t在工厂f作为倒数第k个执行，则花费时间k*t[i][f]
          这是一个很重要也很妙的一点，抓住题目只要求“平均值”，也就是总和，对于工厂f，t1 + (t1+t2) + (t1+t2+t3)和3*t1 + 2*t2 + t3是相等的，就是要求我们打破常规思维，***为什么我们一定要把某订单的执行时间看成一个整体呢？*** 题目只要求总时间和，常规思维的话要考虑“该订单前面有谁”，而现在把时间总和的计算公式变成了第二种形式后，我们就只要考虑“改订单是第几个执行”，有种DP里通过变换获得了无后效性。
          太棒了，简单的变换反映了思维角度的变换，使得我们要考虑的问题变得简单了，只要考虑“我在第几”而非“前面是谁”。




          建图：还是把工厂拆成n*m个点, X部某点i, Y部某个点j，边权i-->j没有实际意义，所以我无法描述他们的意义，只能还是要上面的式子来说明，edge[i-->j] = k * t[i][f], 其中k表i为倒数第k个在f工厂执行。
                由于拆点后对于同一订单，k*t[i][f] > (k-1)*t[i][f] > ... > 1*t[i][f]，所以能保证最优匹配一定是最小总和。


    不由得再赞叹一下，有时为了实现我们的目标，没必要硬要每个模型都有实际意义，可能只要它有数学意义就足够了，而这个数学意义平常比较难想，得画到纸上才Aha, insight.  

    二分图多重匹配类型题把匈牙利算法扩展到多对一
    这道题把KM算法扩展到能加上`顺序`元素
          
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    2505
#define     MAXM    2505*50
struct Edge { int v, value, next; } edge[MAXM];
int LX[MAXN], LY[MAXN], head[MAXN], link[MAXN], a[MAXN][MAXN];
bool visitx[MAXN], visity[MAXN];
int n, m, M, slack, edge_num;

bool find(int u)
{
    visitx[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visity[v]) continue;
        int rest = LX[u] + LY[v] - edge[k].value;
        if(rest == 0) {
            visity[v] = true;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
       } else slack = min(slack, rest);
   }
   return false;
}
void KM()
{
    memset(LY, 0, sizeof(int) * (M+1));
    memset(LX, 128, sizeof(int)* (n+1));        //边权取反来求最大值，所以LX要取无穷小
    for(int i = 0; i < n; i++) 
        for(int k = head[i]; k != -1; k = edge[k].next)
            LX[i] = max(LX[i], edge[k].value);

    for(int i = 0; i < n; i++) {
        while(true) {
            slack = INT_MAX;
            memset(visitx, false, sizeof(bool)*(n+1));
            memset(visity, false, sizeof(bool)*(M+1));
            if(find(i)) break;
            for(int j = 0; j < n; j++) if(visitx[j]) LX[j] -= slack;
            for(int j = 0; j < M; j++) if(visity[j]) LY[j] += slack;
        }
    }
}
void add_edge(int u, int v, int value)
{
    Edge tmp = {v, value, head[u]};
    edge[edge_num] = tmp;
    head[u] = edge_num;
    edge_num++;
}
void init()
{
    edge_num = 0;
    memset(link, -1, sizeof(link));
    memset(head, -1, sizeof(head));
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; k < n; k++)
                    //add_edge(i, j*n+k, -a[i][j]*(1+k));
                    add_edge(i, k*m+j, -a[i][j]*(k+1)); //拆点
        
        M = n*m;        //Y部点
        KM();
        long long ans = 0;
        for(int i = 0; i < M; i++) if(link[i] != -1) {
            ans += a[link[i]][i%m] * (i/m+1);
            //ans += a[link[i]][i/n] * (i%n+1);
        }
        printf("%lld\n", ans);        //ps: 输出double/float最好都用%f而不是%lf, %f才是标准，%lf只是编译器提供的便利
    }
    return 0;
}
