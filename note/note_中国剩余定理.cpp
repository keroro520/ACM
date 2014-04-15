/*
�й�ʣ�ඨ��
    ����C �� a1 (mod m1)��C �� a2 (mod m2)

    ��C = m1*x1 + a1����m1*x1 �� a2-a1(mod m2)��d = gcd(m1, m2)
    �������֪����d��������(a2-a1)���򷽳����޽�
    ����չŷ����ÿ������m1*y1 + m2*y2 = d����һ��y1�� ��Ӧ��m1*x1 + m2*x2 = a2-a1�Ľ�x1
    �Ϳ��Ա�ʾΪx1 = y1*(a2-a1)/d��C1 = m1*x1 + a1

    ����������Ҫ����С��������C0��
    ����֪����ԭ����m1*x1 �� a2-a1(mod m2)�������C��C �� C1 mod m2/d    //����֤
    C = C1 + (m2/d)*x�����ԣ���С��������C0 = [C1 % (m2/d) + m2/d] % (m2/d)

    �������ǲ��Ϻϲ�������������C �� a1 (mod m1)��C �� a2 (mod m2)������������ȥ��һֱ�����
    �ϲ���ԭ�����̿ɺϲ�ΪC �� C0 (mod LCM(m1,m2))
    //�����C0��ǰ�淽�̵���С�����⣬���ǻ�Ҫ����������ֻʣһ�����̣��ҵ����з��̵Ĺ�����
    С��

    ����ժһ�Ρ�Ϊʲô�����������̾Ϳ��Ա�C�� �� C (mod LCM(m1,m2))���桱��֤����Ŀǰ������~~
    "
      http://scturtle.is-programmer.com/posts/19363.html
      ������:C=A1+X1*B1=A2+X2*B2
      ��ΪB��lcm(B1,B2)������:
      B=Y1*B1=Y2*B2
      ��C`=C+Z*B,��C�����:
      C`=A1+(X1+Z*Y1)*B1=A2+(X2+Z*Y2)*B2
      ����C`�ͷ������������ʽ���˰�,�����Ϊ������С��
    "
*/
/*
    ����m1��m2������mk���������ʵ����������һ�ָ���һ���ԵĽⷨ��
    x=a1(mod m1);
    x=a2(mod m2)
    ������
    x=ak(mod mk)
    �÷�������С�ڵ���M = m1 * m2 * ������ * mk����������Ψһ�⡣
    ��Mi = M / mi;��Ϊgcd(Mi,mi)=1������������pi��qi����Mi*pi + mi*qi=1�������ei = Mi*pi��
    ��ôei = 0(mod mj)����j != i ʱ��ei = 1(mod mj)��j = i ʱ��
    ��ʱ�����ԣ�e1*a1 + e2*a2 + ������ + ek*ak���Ƿ��̵�һ���⣬�Ӽ�M��������������Ϳ��Եõ�
    ���п��еĽ��ˡ�
*/


//poj 2891  ���һ��ͬ�෽����(C��ai mod mi��һ����������)������˳��Ϊai, mi
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
void CRT(ll &m1, ll &a1, ll m2, ll a2, ll x, ll d)  //���ã�  x��m1*x + m2*y = d������⣬����������չŷ������������d��gcd(m1,m2)
{
  ll C, m, t;
  t = m2 / d;   //
  x = (a2-a1)/d * x;    //x1 = x0*(a1-a2)/d��x0��x*m1 + y*m2 = a1-a2�������
  x = (x % t + t) % t;  //�������ܱ�֤x1����С��������   ????????????????

  C = x*m1 + a1;        //�ϲ�C �� a1 (mod m1), C �� a2 (mod m2)�� C' �� C (mod LCM(m1,m2))
  m = LCM(m1, m2, d);   //��Ϊx��ǰ��ʽ��С�⣬����C = x*m1 + a1
                        //??????????? Ϊɶ�ܺϲ�???
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


//poj 1006    m1��m2������mk���������� ������һ�ֽⷨ
//���⣺ʹ��ʽ ��x+d��= p mod 23 = e mod 28 = i mod 33 ��������С��x��ע��x����Ϊ0
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
    C = C % m[3];         //Ҫ��С���������
    if(C <= 0) C += m[3];
    printf("Case %d: the next triple peak occurs in %d days.\n", ++Cas, C);
  }
  return 0;
}
