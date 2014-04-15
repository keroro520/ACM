/*
    中国剩余定理 模板题
    题意：求等式 （x+d）= p mod 23 = e mod 28 = i mod 33 成立的最小的x，x > 0

    对于m1，m2，…，mk是两两互质的情况，还有一种更加一般性的解法。
    x=a1(mod m1);
    x=a2(mod m2)
    ···
    x=ak(mod mk)
    该方程组在小于等于M = m1 * m2 * ··· * mk的整数中有唯一解。
    记Mi = M / mi;因为gcd(Mi,mi)=1，故有两整数pi，qi满足Mi*pi + mi*qi=1，如果记ei = Mi*pi，那么ei = 0(mod mj)，当j != i 时；ei = 1(mod mj)，j = i 时。
    这时很明显，e1*a1 + e2*a2 + ··· + ek*ak就是方程的一个解，加减M的任意整数倍后就可以得到所有可行的解了。
*/
#include <stdio.h>

int m[5] = {23,28,33,23*28*33}, a[5], d;
void EGCD(int a, int b, int &x, int &y)
{
  if(b == 0) {
    x = 1 , y = 0;
    return ;
  }
  EGCD(b, a%b, x, y);
  int t = x; x = y, y = t - a/b*y;
}
int CRT()
{
  int C = 0, M = m[3];
  //for(int i = 0; i < 3; i++) M *= m[i];
  for(int i = 0; i < 3; i++) {
    int Mi = M/m[i], x, y, ei;
    EGCD( Mi, m[i], x, y );
    ei = Mi*x*a[i];
    C = (C + ei) % M;
  }
  return C;
}
int main()
{
  int Cas = 0;
  while( scanf("%d%d%d%d", &a[0], &a[1], &a[2], &d) ) {
    if(a[0] == -1 && a[1] == -1 && a[2] == -1 && d == -1) break;

    int C = CRT() - d;
    C = C % m[3];         //要最小正整数解吧
    if(C <= 0) C += m[3];
    printf("Case %d: the next triple peak occurs in %d days.\n", ++Cas, C);
  }
  return 0;
}
