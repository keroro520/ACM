#include <map>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#define MAXN 2505
#define low(x)   ((x) & (-x))
typedef long long ll;
int n;
ll c[MAXN];
map<string , int > M;
ll Sum(int pos)
{
  ll sum = 0;
  while(pos) {
    sum += c[pos];
    pos -= low(pos);
  }
  return sum;
}
void Update(int pos, int val)
{
  while(pos <= n) {
    c[pos] += val;
    pos += low(pos);
  }
}
int main()
{
  string str;
  while(cin >> n) {
    memset(c, 0, sizeof(c));
    ll ans = 0;
    M.clear();
    for(int i = 1; i <= n; i++) {
      cin >> str ;
      M[ str ] = i;
    }

    for(int i = 1; i <= n; i++) {
      cin >> str;
      ans += Sum( M[str] );
      Update( M[str], 1 );
    }
    ll TT = (ll)n*(ll)(n-1)/2;
    cout << ans << "/" << TT << endl;
  }
  return 0;
}
