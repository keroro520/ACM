/*
  判断n!是否能够被m整除
  计算方法是把m进行质因数分解，看下m的每一个质因数是否能够在n!中找到；
  n!中间包含了多少个x(x是任意的一个数，不过一般情况下我们都只讨论x为质数)，这种问题的答案
  是：n/x+n/(x^2)+n/(x^3).....[一直加到x的乘方不超过n]，这个定理的证明也非常的简单，这里就
  不再赘述了.根据以上观点，就可以分别计算m的每一个质因数是否被完全包含，如果有一个没有被包
  含，那么就不能被整除！

  算n!包含多少个x 可以用优美的递归 : F(n,x) = n/x + F(n/x, x)

  ask:
        为什么素数表只要开到46340?   sqrt( 2^31 )
        从因子大到小检查能加速?      a little
  problem link : http://acm.hust.edu.cn/vjudge/problem/viewProblem.action?id=21255
*/
#include <stdio.h>
#include <math.h>
typedef long long ll;
struct Factor {
  int n, p;
} fac[50000];
int fac_num, prime_num;
int p[50000];
bool boo[50005];
void init()
{
  for(int i = 2; i < 50000; i++) if(!boo[i]) {
    p[prime_num++] = i;
    int j = i+i;
    while(j < 50000) {
      boo[j] = true;
      j += i;
    }
  }
}
void divide(ll n)
{
  fac_num = 0;
  for(int i = 0; p[i] <= n && i < prime_num; i++)
    if(n % p[i] == 0) {
      fac[fac_num].p = p[i], fac[fac_num].n = 0;
      while(n % p[i] == 0) {
        fac[fac_num].n ++;
        n /= p[i];
      }
      fac_num++;
    }
  if(n > 1) fac[fac_num].p = n, fac[fac_num++].n = 1;
}
int calc(ll n, int x)
{
  if(n == 0) return 0;
  return n/x + calc(n/x, x);
}
bool judge(ll n)
{
 // for(int i = 0; i < fac_num; i++) printf("!%d\n", fac[i].p);
  for(int i = fac_num-1; i >= 0; i--) { //从大到小能加速?
  //  int cnt = 0;  ll j = fac[i].p;
  //  while(n >= j) {
  //    cnt += n/j;
  //    j *= fac[i].p;
  //  }
  //  if(cnt < fac[i].n) return false;
    if(calc(n, fac[i].p) < fac[i].n) return false;  //递归算，慢一点点，但是优美
  }
  return true;
}
int main()
{
  ll n, m;
  init();
  while(scanf("%lld %lld", &n, &m) != EOF) {
    printf("%d", m);
    if(m <= n) printf(" divides %d!\n", n);
    else {
      divide(m);
      printf(" %s %d!\n", judge(n) ? "divides" : "does not divide", n);
    }
  }
  return 0;
}
