/*
    期望DP  概率DP  
    题意：一个bug仅属于一个系统和一个分类，现有n个系统和s个分类，一天可以找出一个bug，问找到的bug覆盖所有系统和分类所期望的天数。

    思路：可以把该题建成一个有向图：状态(i,j)表已找出的bug覆盖i个系统j个分类，e(i,j)在图里作为一个节点，在数学上表示(i,j)状态到(n,s)的期望，所以e(n,s) = 0, 目标是求e(0,0)；概率关系看作有向边，易知这是个有自环的图。
          因为想用递推直接搞，而递推的条件是图无环，我们可以通过一些数学上的方法把自环消掉。直接上公式了。
          E(T) = c + Σ(p*E(S))      无环图,c表示一步的代价，p表示S->T的概率
          (1-p')E(T) = c + Σ(p*E(S))    有自环图，p'表示自己到自己的概率


          我是直接上递归的，当然DP的比较快。
          e(i,j) = p(i,j)*e(i,j) + p(i+1,j)*e(i+1,j) + p(i,j+1)*e(i,j+1) + p(i+1,j+1)*e(i+1,j+1)
*/
#include <stdio.h>
#define     MAXN    1005
#define     ZERO    1e-7
int n, s;
double e[MAXN][MAXN];

double calc(int i, int j)
{
    if(e[i][j] + 1 > ZERO) return e[i][j];
    e[i][j] = 1;
    if(i + 1 <= n && j + 1 <= s) e[i][j] += calc(i+1, j+1) * ((1-i*1.0/n)*(1-j*1.0/s));
    if(i + 1 <= n) e[i][j] += calc(i+1, j) * ((1-i*1.0/n)*(j*1.0/s));
    if(j + 1 <= s) e[i][j] += calc(i, j+1) * ((i*1.0/n)*(1-j*1.0/s));
    e[i][j] /= (1 - 1.0*i/n*j*1.0/s);
    return e[i][j];
}
int main()
{
    scanf("%d%d", &n, &s);
    for(int i = 0; i <= n; i++) for(int j = 0; j <= s; j++) e[i][j] = -1;
    e[n][s] = 0;
    printf("%.4f\n", calc(0, 0));
    return 0;
}
