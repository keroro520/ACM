/*
	区间DP  差值博弈  好题
    题意：给你n个数，A、B两个人从两端取数，每一次可以取连续的一段数，而且每个人都按让自己最优的方案去取数（即取的数的和尽可能大）
    问最后A与B的差值最大是多少

    思路：有一道区间两端取数的初始版本：USACO / A Game  http://www.cnblogs.com/AbandonZHANG/archive/2012/08/03/2620838.html
          初始版本"a game"是每次可以取两端的一个数字，本题是每次可以取两端连续的一段数字。我是看了前者的解析才理解后者的题解的=_=


          先来讲初始版本的：f[i, j]表先手面对这样一个序列可以保证取道的最大值。
                            f[i, j] = sum(i,j) - min{f[i+1, j], f[i, j-1]};    //面对区间[i,j]，我们有两种选择，然后轮到对手，对手也会采取最优策略拿到f[i+1, j]或者f[i, j-1]的值，所以我们只需要使得区间[i,j]被对手拿到最少即可。这有点像“极大极小搜索”的想法，将自己的所得极大化相当于将对手的所得极小化。
                            选了一个后转化成的子问题，第二个人是先选，所以第一个人只能拿到子问题的后选的人的解，即sum[i][j]-f[i][j]。


          本题其实就是扩展一下嘛，可以仿照a game的写出方程，对于一段区间，枚举分隔点，要么取左边，要么取右边，对应于:
                    f[i][j] = max(f[i][j], Sum(i, k) - f[k+1][j]);
                    f[i][j] = max(f[i][j], Sum(k, j) - f[i][k-1]); 

          这是道博弈题，双方都采取最优策略，所以对于区间(l,r)，如果先手A取(l..k)，则就转化成了子问题，就是后手B对于区间(k+1,r)最大为多少，注意，这个时候的区间(k+1,r)，先手是B！所以这就是方程得以成立的巧妙之处哈~  diff = sum(l..k) - f[k+1, r].
          因为对于每个区间，先手是轮换着来的，而f[i,j]表先手能取到的最大值，就很好地适合“先手是轮换着的”.
*/
//lightoj 1031
#include <algorithm>
#include <stdio.h>
using namespace std;
#define         MAXN        105
#define         INF         999999999
#define         Sum(l, r)   (sum[(r)] - sum[((l)-1)])
int sum[MAXN], f[MAXN][MAXN];
int n;
int main()
{
    int Cas = 0, cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &sum[i]),  sum[i] += sum[i-1];
        
        for(int l = 1; l <= n; l++)
            for(int i = 1; i + l - 1 <= n; i++) {
                int j = i + l - 1;
                f[i][j] = Sum(i, j);
                for(int k = i; k <= j; k++) {
                    f[i][j] = max(f[i][j], Sum(i, k) - f[k+1][j]);
                    f[i][j] = max(f[i][j], Sum(k, j) - f[i][k-1]); 
                }
            }
        printf("Case %d: %d\n", ++Cas, f[1][n]);
    }
    return 0;
}
