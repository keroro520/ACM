/*
  中国剩余定理
  题意：给A,B,C,k，求最小非负数t，使得(A + C*t) = B mod 2^k

  思路: (A + C*t)= B mod 2^k
        C*t ≡ B - A(mod 2^k)
        C*x + (2^k)*y = B-A;     (只面熟ax+by=n形式=_=)

        欧几里得求ax+by=d的x0
        ax+by=n的任一解x1 = x0*(n/d)
        任意解x  = x1 + b/d*i
        最小解x_ = (x1 % (b/d) + b/d) % (b/d)
*/

#include <stdio.h>
typedef long long ll;
ll EGCD(ll a, ll b, ll &x, ll &y)
{
  if(b == 0) {
    x = 1, y = 0;
    return a;
  }
  ll d = EGCD(b, a%b, x, y);
  ll t = x; x = y, y = t - a/b*y;
  return d;
}
int main()
{
  ll A, B, C, m, n, d, x, y, t;
  while(scanf("%I64d %I64d %I64d %I64d", &A, &B, &C, &m), A||B||C||m) {
    m = (1LL << m);
    n = B - A;
    d = EGCD(C, m, x, y);
    if(n % d != 0) { puts("FOREVER"); continue; }

    t = m/d;
    x = x*(n/d);      //x0是C*x + m*y = d的解, x才是C*x+(2^k)*y = B-A的解
    x = (x % t + t) % t;
    printf("%I64d\n", x);
  }
  return 0;
}
