/*
  �ж�n!�Ƿ��ܹ���m����
  ���㷽���ǰ�m�����������ֽ⣬����m��ÿһ���������Ƿ��ܹ���n!���ҵ���
  n!�м�����˶��ٸ�x(x�������һ����������һ����������Ƕ�ֻ����xΪ����)����������Ĵ�
  �ǣ�n/x+n/(x^2)+n/(x^3).....[һֱ�ӵ�x�ĳ˷�������n]����������֤��Ҳ�ǳ��ļ򵥣������
  ����׸����.�������Ϲ۵㣬�Ϳ��Էֱ����m��ÿһ���������Ƿ���ȫ�����������һ��û�б���
  ������ô�Ͳ��ܱ�������

  ��n!�������ٸ�x �����������ĵݹ� : F(n,x) = n/x + F(n/x, x)

  ask:
        Ϊʲô������ֻҪ����46340?   sqrt( 2^31 )
        �����Ӵ�С����ܼ���?      a little
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
  for(int i = fac_num-1; i >= 0; i--) { //�Ӵ�С�ܼ���?
  //  int cnt = 0;  ll j = fac[i].p;
  //  while(n >= j) {
  //    cnt += n/j;
  //    j *= fac[i].p;
  //  }
  //  if(cnt < fac[i].n) return false;
    if(calc(n, fac[i].p) < fac[i].n) return false;  //�ݹ��㣬��һ��㣬��������
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
