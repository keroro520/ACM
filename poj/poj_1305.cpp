/*
  数论  本原勾股数组
  题意：求解N以内有多少个本原勾股数组

  本原勾股数组 : 满足a^2 + b^2 = c^2且a,b,c的最大公约数为1
  思路：根据下面的叙述实现，枚举s,t,判断一下

		看下面的证明有两点疑惑：
		(1)证明a、b奇偶性不同；
		(2)证c-b与c+b互质？
		解惑：http://hi.baidu.com/lvhuyh/item/5e9aecce861f0a130ad93a9b
		      http://blog.csdn.net/metaphysis/article/details/6995250
  			  http://blog.csdn.net/magicnumber/article/details/6410043


  摘: http://blog.csdn.net/magicnumber/article/details/6410043
  本章主要讨论的是勾股数组，也就是关于满足a^2+b^2=c^2的三元组（a,b,c）的问题。
      其实，对于勾股数组的个数进行讨论并没有多大意义，因为已知a，b，c为勾股数组，那么显然有da，db，dc(d>0)也为勾股数组，因为(da)^2+(db)^2=d^2(a^+b^2)=d^2c^2=(dc)^2。
      因此着重研究的是关于本原勾股数组的问题，本原勾股数组即为a，b，c为勾股数组且满足a，b，c的最大公约数为1。
      对于本原勾股数组，显然a和b奇偶性不同只需要将a=2x+1,b=2y+1,c=2z代入a^2+b^2=c^2即可推出有公约数2。由于a和b奇偶性不同，那么显然c为奇数。
      那么最关心的是如何求出所有的本原勾股数组。
      如果将公式转化一下，得到a^2=c^2-b^2=(c+b)(c-b)，那么显然有，c+b和c-b没有公因子，用反证法证明：
      如果d|(c+b)且d|(c-b)，那么显然有d|((c+b)+(c-b))和d|((c+b)-(c-b))即d|2b且d|2c，因为在定义本原勾股数组的时候已经有了b和c的最大公约数是1的约定(虽然定义是a，b，c最大公约数是1，但是如果gcd(b,c)=d>1，显然有d|c不满足定义)。所以d要么为1，要么为2。但是如果d=2时，那么显然a，b，c均为偶数，不满足定义，那么d只能为1，证明了c+b和c-b没有公因子。
      因此，如果将a^2进行质因数分解，那么会有a=p1^t1*p2^t2*p3^t3...pn^tn，其中指数t1,t2,t3...tn为偶数（因为这样才能保证a^2开根号后为整数），又因为c+b和c-b没有公因数，所以c+b和c-b各取a分解后的其中某一些pk^tk，因此，c+b和c-b均为平方数。那么假设c+b=s^2,c-b=t^2，则有c=(s^2+t^2)/2,b=(s^2-t^2)/2，a=st，因此形如(st,(s^2-t^2)/2,(s^2+t^2)/2)的三元组为本原勾股数组。(其中s和t都是奇数，因为如果s和t中有且只有一个为奇数，那么显然(s^2+t^2)/2不会是整数，而如果两个数都是偶数，那么显然该三元组有公因子2，与本原勾股数组定义矛盾。)
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXN 1000009
int n;
bool vis[MAXN];
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }
bool check(int a, int b, int c)
{
  return a*a+b*b==c*c && gcd(c, gcd(a, b)) == 1;
}
int main()
{
  while(scanf("%d", &n) != EOF) {
    int p = 0, ans = 0, a, b, c;
    memset(vis, false, sizeof(bool)*(n+5));
    for(int oo = 2*(int)(sqrt(n+0.5)), s = 1; s <= oo; s += 2)
      for(int t = 1; t < s; t += 2) {
        int a = s*t, b = (s*s-t*t)/2, c = (s*s+t*t)/2;
        if(c > n) break;
       // if(gcd(s, t) != 1) continue;
        if(check(a,b,c)) {
          ans++;  int k = 1;
          while(c*k <= n) {
            vis[a*k] = vis[b*k] = vis[c*k] = true;
            k++;
          }
        }
      }
    for(int i = 1; i <= n; i++) p += !vis[i];
    printf("%d %d\n", ans, p);
  }
  return 0;
}
