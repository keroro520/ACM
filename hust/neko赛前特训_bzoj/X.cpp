#include <iostream>
using namespace std;
#define MOD 999911659
typedef long long ll;
ll N, G;
ll calc_P(ll x, ll C)
{
  ll P = 0;
  P = Lucas(N, 1, C);
}
int main()
{
  init();
  cin >> N >> G;  G %= MOD;
  P = calc_P(N, MOD-1);
  return 0;
}
