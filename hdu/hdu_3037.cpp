/*
  数论  Lucas定理 + 扩展欧几里得(模逆) + 组合数学

  题意：给出N, M, P, 求C(N+M, M) mod P.  1 <= n,m <= 1000000000,1 < p < 100000, P保证是素数

  思路：Lucas定理: Lucas(N, M, P) 定义为C(N, M) % P, P一定要是素数
                则:Lucas(N, M, P) = C(N%P, M%P) * Lucas(N/P, M/P, P);

  证明摘：Lucas 定理：A、B是非负整数，p是质数。AB写成p进制：A=a[n]a[n-1]...a[0]，B=b[n]b[n-1]...b[0]。
则组合数C(A,B)与C(a[n],b[n])*C(a[n-1],b[n-1])*...*C(a[0],b[0])  modp同
即：Lucas(n,m,p)=c(n%p,m%p)*Lucas(n/p,m/p,p)
首先我们注意到 n=(ak...a2,a1,a0)p  =  (ak...a2,a1)p * p + a0
                                                       =  [n/p]*p+a0

                                                    且m=[m/p]+b0

只要我们更够证明 C(n,m)=C([n/p],[m/p]) * C(a0,b0)  (mod p)
剩下的工作由归纳法即可完成

我们知道对任意质数p:   (1+x)^p  == 1+(x^p)  (mod p)
注意!这里一定要是质数  ................(为什么)

对 模p 而言

 上式左右两边的x^m的系数对模p而言一定同余(为什么),其中左边的x^m的系数是 C(n,m) 而由于a0和b0都小于p
右边的x^m ( = x^(([m/p]*p)+b0)) 一定是由 x^([m/p]*p) 和 x^b0 相乘而得 (即发生于 i=[m/p] , j=b0 时) 因此我们就有了

C(n,m)=C([n/p],[m/p]) * C(a0,b0)  (mod p)
*/
#include <stdio.h>
#define MAXP 100005
typedef long long ll;
ll A[MAXP];
void init_fac(ll P)
{
  A[0] = 1;
  for(int i = 1; i <= P; i++) A[i] = A[i-1] * i % P;
}

void Egcd(ll a, ll b, ll &x, ll &y)
{
  if(b == 0) {
    x = 1, y = 0;
    return ;
  }
  Egcd(b, a%b, x, y);
  ll t = x;  x = y, y = t - a/b*y;
}
ll mod_inv(ll a, ll P)
{
  ll x, y;
  Egcd(a, P, x, y);
  return (x % P + P) % P;
}
ll C(ll N, ll M, ll P)
{
  if(N < M) return 0;
  return A[N] * mod_inv(A[M], P) % P * mod_inv(A[N-M], P) % P;
}
ll Lucas(ll N, ll M, ll P)
{
  if(M == 0) return 1;
  return C(N % P, M % P, P) * Lucas(N/P, M/P, P) % P;
}
int main()
{
  ll N, M, P;  int cases;

  scanf("%d", &cases);
  while(cases--) {
    scanf("%I64d %I64d %I64d", &N, &M, &P);
    init_fac(P);
    printf("%I64d\n", Lucas(N+M, M, P));
  }
  return 0;
}
