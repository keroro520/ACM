/*
    区间DP  好题
    题意：跟经典的关路灯一样

    思路：因为这题之前做了hdu_4283，“悟”除了区间DP的状态f[i,j]要保证满足局部独立性，然后做这题的时候一眼定义了f[i,j]表示关掉区间[i,j]的路灯花费最少的电费，而且严格控制是[i,j]这个区间，跟外面的灯无关。   然后接下来就不知道怎么转移了...因为历时时间无法计算也无法记录。
          然后还是看了题解。发现又是自己的f[i,j]状态的含义定义不合适...=_=

          正解的f[i,j]状态定义为，关掉[i,j]这个区间的灯时，全局已经累积了多少电费。
          这个状态的定义对“历时”比较好解决，如果当前人类关掉i灯后走向j灯，则全局电费增量为dis(i,j) * sum_of_rest_lights_power，就是距离乘上剩下的灯的功率和。
          状态方程就好解决了，略.


    摘抄：先说下本题的模型，送餐的顺序是一个从x位置开始的从1...n的一个全排列，我们要做的是找一个全排列它的总坑爹值最小。 
		  from http://blog.csdn.net/woshi250hua/article/details/7768744
*/
// zoj 3469
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    1005
#define     INF     1100000000
#define     bug(x)  printf("# %d\n", x)
int f[2][MAXN][MAXN], sum[MAXN];
class Person {
    public :
    int x, b;
    Person() { }
    Person(int x, int b) : x(x), b(b) { }
} a[MAXN];
int n;

bool cmp(const Person & a, const Person & b) {
    return a.x < b.x;
}
int Sum(int l, int r)
{
    return sum[r] - sum[l-1];
}
int work(int s)
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) f[0][i][j] = f[1][i][j] = INF;
    f[0][s][s] = f[1][s][s] = 0;
    for(int i = s; i > 0; i--)
        for(int j = s; j <= n; j++) if(i != j) {        //TODO
            int tmp = (Sum(1, i-1) + Sum(j+1, n));
            f[0][i][j] = min(f[0][i][j], f[0][i+1][j] + (a[i+1].x - a[i].x) * (tmp + a[i].b));
            f[0][i][j] = min(f[0][i][j], f[1][i+1][j] + (a[j].x - a[i].x) * (tmp + a[i].b));
            f[1][i][j] = min(f[1][i][j], f[0][i][j-1] + (a[j].x - a[i].x) * (tmp + a[j].b));
            f[1][i][j] = min(f[1][i][j], f[1][i][j-1] + (a[j].x - a[j-1].x) * (tmp + a[j].b));
        }
    return min(f[0][1][n], f[1][1][n]);
}
int main()
{
    int V, X;
    while(scanf("%d%d%d", &n, &V, &X) != EOF) {     //V分钟跑1m，那就以V为单位
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].x, &a[i].b);
            //a[i].x *= V;
        }
        //X *= V;
        a[++n] = Person(X, 0);
        sort(a+1, a+n+1, cmp);
        for(int i = 1; i <= n; i++) sum[i] = sum[i-1] + a[i].b; 
        for(int i = 1; i <= n; i++) if(a[i].x == X && a[i].b == 0) {
            printf("%d\n", V * work(i));            //留到后面乘，之前在前面乘因为溢出WA了两次
            break;
        }
    }
    return 0;
}
