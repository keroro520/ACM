/*
  中国剩余定理CRT  扩展欧几里得求最小正整数解
  题意：中国剩余定理模板题，求解一般同余方程组(C≡ai mod mi不一定两两互质)，输入顺序为ai, mi

  中国剩余定理：
    假设C ≡ a1 (mod m1)，C ≡ a2 (mod m2)

    令C = m1*x1 + a1，则m1*x1 ≡ a2-a1(mod m2)，d = gcd(m1, m2)
    由斐蜀定理知，若d不能整除(a2-a1)，则方程组无解
    用扩展欧几里得可以求出m1*y1 + m2*y2 = d的任一解y1， 对应到m1*x1 + m2*x2 = a2-a1的解x1
    就可以表示为x1 = y1*(a2-a1)/d，C1 = m1*x1 + a1

    接下来我们要求最小正整数解C0。
    我们知道，原方程m1*x1 ≡ a2-a1(mod m2)的任意解C有C ≡ C1 mod m2/d    //不会证
    C = C1 + (m2/d)*x，所以，最小正整数解C0 = [C1 % (m2/d) + m2/d] % (m2/d)

    接下来是不断合并上面两个方程C ≡ a1 (mod m1)，C ≡ a2 (mod m2)并继续迭代下去，一直到最后
    合并：原二方程可合并为C ≡ C0 (mod LCM(m1,m2))
    //这里的C0是前面方程的最小公共解，我们还要继续迭代到只剩一个方程，找到所有方程的公共最
    小解

    下面摘一段“为什么上面两条方程就可以被C’ ≡ C (mod LCM(m1,m2))代替”的证明，目前看不懂~~
    "
      http://scturtle.is-programmer.com/posts/19363.html
      题意有:C=A1+X1*B1=A2+X2*B2
      因为B是lcm(B1,B2)所以有:
      B=Y1*B1=Y2*B2
      又C`=C+Z*B,把C带入得:
      C`=A1+(X1+Z*Y1)*B1=A2+(X2+Z*Y2)*B2
      所以C`就符合最初的两个式子了吧,不清楚为何是最小的
    "
*/
#include <stdio.h>
#define LCM(a1, a2, d)  ( a1/d * a2 )
typedef long long ll;
ll EGCD(ll a, ll b, ll &x, ll &y)
{
  if(b == 0) {
    x = 1, y = 0;
    return a;
  }
  ll d = EGCD(b, a%b, x, y);
  ll t = x;  x = y, y = t - a/b*y;
  return d;
}
void CRT(ll &m1, ll &a1, ll m2, ll a2, ll x, ll d)  //引用！  x是m1*x + m2*y = d的任意解，在外面由扩展欧几里得求出来，d是gcd(m1,m2)
{
  ll C, m, t;
  t = m2 / d;   //
  x = (a2-a1)/d * x;    //x1 = x0*(a1-a2)/d，x0是x*m1 + y*m2 = a1-a2的任意解
  x = (x % t + t) % t;  //这样就能保证x1是最小正整数解   ????????????????

  C = x*m1 + a1;        //合并C ≡ a1 (mod m1), C ≡ a2 (mod m2)成 C' ≡ C (mod LCM(m1,m2))
  m = LCM(m1, m2, d);   //因为x是前两式最小解，所以C = x*m1 + a1
                        //??????????? 为啥能合并???
  a1 = C, m1 = m;
}

int main()
{
  int n;
  while(scanf("%d", &n) != EOF) {
    ll a1, a2, m1, m2, x, y;   bool flag = true;
    scanf("%I64d %I64d", &m1, &a1);

    for(int i = 1; i < n; i++) {
      scanf("%I64d %I64d", &m2, &a2);       if(!flag) continue;

      ll d = EGCD(m1, m2, x, y);
      if((a2 - a1) % d != 0) { flag = false; continue; }

      CRT(m1, a1, m2, a2, x, y, d);
    }
    printf("%I64d\n", flag ? a1 : -1);
  }
  return 0;
}
