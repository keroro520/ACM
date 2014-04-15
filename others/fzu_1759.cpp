/*
  指数循环节  欧拉函数  A^B mod C
  题意：计算A^B mod C ,  (1<=A,C<=1000000000,1<=B<=10^1000000).

  思路：指数循环节: A^x mod C = A^(x mod φ(C) + φ(C)) mod C
        证明在这儿 http://hi.baidu.com/aekdycoin/item/e493adc9a7c0870bad092fd9

  第一次写欧拉函数~
*/
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
/*
void eular( N )    //求出了N内所有数的欧拉函数值
{
    prime[0] = prime[1] = 0;
    for(int i = 2; i <= N; i++)
        prime[i] = 1;
    for(int i = 2; i + i <= N; i++)
        if(prime[i])
            for(int j = i * i; j <= N; j += i)
                prime[j] = 0;
    //这段求出了N内的所有素数
    phi = (int*)malloc((N + 1) * sizeof(int));
    for(int i = 1; i <= N; i++)
        phi[i] = i;
    for(int i = 2; i <= N; i++)
        if(prime[i])
            for(int j = i; j <= N; j += i)//此处注意先/i再*（i-1)，否则范围较大时会溢出
                    phi[j] = phi[j] / i * (i - 1);
}
*/
ll euler(ll n)      //求单个数的欧拉函数
{
  ll phi = n;
  if(n == 1) return 0;
  for(ll i = 2; i * i <= n; i++)
    if(n % i == 0) {
      phi = phi/i * (i-1);
      while(n%i == 0) n /= i;  
    }

  if(n > 1) phi = phi/n * (n-1);
  return phi;
}
ll bigNumber_mod(string &s, ll C)  //大数取模
{
  ll tmp = 0;
  int i = 0, len = s.length();
  while(i < len) {
    tmp = tmp * 10 + s[i]-'0';
    tmp %= C;
    i++;
  }
  return tmp;
}
ll SQR(ll x, ll MOD) { return x * x % MOD ; }
ll fast_power(ll A, ll B, ll MOD)
{
  if(B == 0) return 1;
  if(B & 1) return A * SQR(fast_power(A, B/2, MOD), MOD) % MOD;
  return SQR(fast_power(A, B/2, MOD), MOD);
}
int main()
{
  ll A, B, C, phi;  string str;
  while(cin >> A >> str >> C) {
    phi = euler( C );
    B = phi + bigNumber_mod(str, phi);
    A = A % C;
    ll ans = fast_power(A, B, C);
    cout << ans << endl;
  }
  return 0;
}
