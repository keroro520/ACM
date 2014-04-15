/*
	数论  组合数学  斯特林数  stirling number

	题意：	n匹马赛跑。问有多少种不同的排名结果。可以有多匹马的排名相同。

	思路：	第二类斯特林数，问题等价于给定i个不同的盒子，把n个不同的球放到这些盒子里，不允许有空盒，求方案数。
	
			于是可以转化为盒子全部相同，再乘i!。也就是把n个不同的球放到k个相同的盒子中，不允许空盒子，求方案数。也就是第二类Stirling数




		    以上为摘抄下方博客。我把全文copy到文件下方了...
			第二步解释一下，把盒子当成全部相同则可以转换成stirling数，然后乘上i! 可以这样理解，就是原来的i个盒子一共有i! 种排列，所以乘上i! 可以相当于给i个盒子恢复了身份。
*/
//http://www.kaixinwenda.com/article-whyorwhnt-8991040.html
//lightoj 1326
#include <stdio.h>
#define		MOD		10056LL
#define		MAXN	1005
#define		N		1001
long long fac[MAXN], stirling[MAXN][MAXN];

void init()
{
	fac[1] = 1;
	for(int i = 2; i < N; i++) fac[i] = (fac[i-1] * i) % MOD;
	for(int p = 1; p < N; p++) {
		stirling[p][0] = 0;
		stirling[p][p] = 1;
		for(int k = 1; k < p; k++) 
			stirling[p][k] = (k * stirling[p-1][k] + stirling[p-1][k-1]) % MOD;
	}
}
int main()
{
	int cases, Cas = 0, n;
	init();
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		long long ans = 0;
		for(int i = 1; i <= n; i++)
			ans = (ans + stirling[n][i] * fac[i]) % MOD;
		printf("Case %d: %lld\n", ++Cas, ans);
	}
	return 0;
}
/*
 斯特林数学习小记 Hdu 3625+ LightOJ 1326
分类： 数学 2013-05-29 12:36 40人阅读
环排列

定义

从n个不同的元素中仅取m（1≤m≤n）个不同的元素按照圆圈排列，这种排列叫做从n个元素里取m个元素的环排列。两个环排列，如果元素间的位置没有改变，就是同一排列。

计算公式

把一个m个元素的环在m个不同的位置拆开记得到m个不同的线排列。由于n个不同元素中任取m个元素的排列方法为P(n,m)种，所以n个不同元素中任取m个元素的环排列方法有P(n,m)/m种。

特别的，n个不同元素的环排列方法有P(n,n)/n=(n-1)！种。


第一类Stirling数 s(p,k)

组合学解释：将p个物体排成k个非空环排列的方法数。

递推公式：s(p,k) = (p-1)*s(p-1,k) + s(p-1,k-1)  ,1<=k<=p-1

边界条件：

s(p,0) = 0  ,p>=1

s(p,p) = 1  ,p>=0

递推关系的说明：考虑第p个物品，p可以单独构成一个非空循环排列，这样前p-1种物品构成k-1个非空循环排列，方法数为s(p-1,k-1)；也可以前p-1种物品构成k个非空循环排列，而第p个物品插入第i个物品的左边，这有(p-1)*s(p-1,k)种方法。



第二类Stirling数 S(p,k)

组合学解释：将p个物体划分成k个非空的不可辨别的（可以理解为盒子没有编号）集合的方法数。

递推公式：S(p,k) = k*S(p-1,k)  + S(p-1,k-1)     ,1<= k <=p-1

边界条件：

S(p,p) = 1 ,p>=0

S(p,0) = 0 ,p>=1

递推关系的说明：考虑第p个物品，p可以单独构成一个非空集合，此时前p-1个物品构成k-1个非空的不可辨别的集合，方法数为S(p-1,k-1)；也可以前p-1种物品构成k个非空的不可辨别的集合，第p个物品放入任意一个中，这样有k*S(p-1,k)种方法。



Hdu 3625 Examining the Rooms

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=3625

题意：给出N个房间，每个房间的钥匙随机放在某个房间内，概率相同。有K次破坏门的机会，其中1号门不能破坏，求能进入所有房间的可能性为多大。

思路：第一类斯特林数，钥匙与门呈环形对应关系。打开一个门之后，环内的所有房间都可以进入。问题转变为N个房间形成1~K个环的可能性有多大。

N个房间N个钥匙线性排列的总数为N！

因为1号门不能破坏，所以s(n,k)-s(n-1,k-1)为实际的构成k个环的方法数，也就是去掉1号独立成环的情况。

[cpp] view plaincopy
#include <iostream>  
#include <cstdio>  
  
const int N=21;  
  
__int64 s[N][N],f[N];  
  
void Init ()  
{  
    int i;  
    for (i=0;i<N;i++)  
        s[i][i]=1;  
    for (i=2;i<N;i++)   //初始化第一类斯特林数  
        for (int j=1;j<i;j++)  
            s[i][j]=((i-1)*s[i-1][j]+s[i-1][j-1]);  
    f[0]=1;  
    for (i=1;i<N;i++)   //阶乘  
        f[i]=f[i-1]*i;  
}  
  
int main ()  
{  
    Init ();  
    int T;  
    scanf("%d",&T);  
    while (T--)  
    {  
        int n,k;  
        scanf("%d%d",&n,&k);  
        __int64 sum=0;  
        for (int i=1;i<=k;i++)  
            sum+=s[n][i]-s[n-1][i-1];  
        printf("%.4lf\n",1.0*sum/f[n]);  
    }  
    return 0;  
}  

LightOJ 1326 Race
题目链接：http://lightoj.com/volume_showproblem.php?problem=1326

题意：n匹马赛跑。问有多少种不同的排名结果。可以有多匹马的排名相同。

思路：第二类斯特林数，问题等价于给定i个不同的盒子，把n个不同的球放到这些盒子里，不允许有空盒，求方案数。

于是可以转化为盒子全部相同，再乘i!。也就是把n个不同的球放到k个相同的盒子中，不允许空盒子，求方案数。也就是第二类Stirling数
[cpp] view plaincopy
#include <cstdio>  
#include <iostream>  
#include <cstring>  
using namespace std;  
  
int s[1010][1010],f[1010];  
  
void Init ()  
{  
    int i;  
    s[1][1]=1;  
    for (i=2;i<=1000;i++)   //初始化第二类斯特林数  
        for (int j=1;j<=i;j++)  
            s[i][j]=(j*s[i-1][j]+s[i-1][j-1])%10056;  
    f[0]=1;  
    for (i=1;i<=1000;i++)   //阶乘  
        f[i]=f[i-1]*i%10056;  
}  
  
int main ()  
{  
    Init ();  
    int T;  
    scanf("%d",&T);  
    for (int Cas=1;Cas<=T;Cas++)  
    {  
        int n,ans=0;  
        scanf("%d",&n);  
        for (int i=1;i<=n;i++)  
            ans=(ans+s[n][i]*f[i])%10056;  
        printf("Case %d: %d\n",Cas,ans);  
    }  
*/
