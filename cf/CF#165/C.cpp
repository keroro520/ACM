/*
  status上那些人的代码好简单...
*/
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;
#define MAXN 100005
typedef long long ll;
struct Box {
  ll k, size;
  bool operator < (const Box &b) const {
    return size < b.size;
  }
} box[MAXN];
int n;
int main()
{
  cin >> n;
  for(int i = 0; i < n; i++) cin >> box[i].size >> box[i].k ;

  sort(box, box+n);
  for(int i = 0; i < n-1; i++) {
    box[i+1].k = max(box[i+1].k,
                     (ll)ceil(1.0*box[i].k / pow(4.0, (box[i+1].size-box[i].size)*1.0)));
  }
  //求ans要注意，因为k<1时，log(k, 4) < 0; k == 1时, log(k, 4) == 0, 所以k == 1时会完蛋，
  //所以机智的我加了个max(1, ..)...好吧，这是看数据的时候发现的错误.
  ll ans = max((ll)ceil(log((box[n-1].k)*1.0)/log(4.0)), 1LL) + box[n-1].size;
  cout << ans << endl;
  return 0;
}
