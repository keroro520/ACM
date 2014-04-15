/*
  合并堆  追逐法  好题
  题意：给5个规模为n(n <= 200)的堆，判断能否从这5个堆里各取一个数字，使这5个数和为0

  思路：首先问题如果变成(1)“两个有序堆，判断能否各取一个数，使两个数和为0”，我们可以用追逐法来
        求：一个指针指向堆1的头，一个指针指向堆2的尾，然后向里收敛。
        如果是无序堆呢？当然是可以nlogn排一遍序。不过Neko给了一个hash法比较更好：扫一遍n
        把堆1里的数据hash起来，再扫一遍堆2，在hash_table里找是否存在相应的数即可

        那如果是(2)“3个有序堆，判断能否各取一个数，使两个数和为0”呢？我们可以枚举第一个堆的
        数，然后问题就变成了问题(1)了

        回到原问题，5个堆。我们可以把5个堆变成我们已知的问题(1)(2)：前两个堆的和作为一个堆，
        后两个堆的和作为一个堆，这样我们就回到问题(2)了。其实这个思想就是“把多个堆合并成一个
        的思想”

        扩展开来，有n个堆呢？我们可以把n个堆合并成3堆，前两堆数目为n/3向上取整，最后要枚举的
        那一堆n/3向下取整

        说完堆合并，说说追逐法。
        我感觉追逐法就是不断收敛的过程。比如我把问题改成“从两堆里各取两个数，和在区间[l,r]”
        是可以用追逐法来完成的，但是如果是乘法，即积为一个定值或一个区间，是不能用追逐法的
        ，因为乘法不具有收敛性质。  哦对了，这里所说的追逐法是“一个从头开始，一个从尾巴开始”
        的追逐，不是“一个在前跑，一个在后追”。
*/

#include <algorithm>
#include <stdio.h>
using namespace std;
typedef long long ll;
#define MAXN 205
ll a[MAXN][MAXN], p0[MAXN*MAXN], p1[MAXN*MAXN];
int n, pe0, pe1;
void calc(ll *a, ll *b, ll *res, int &m)  //合并堆
{
  int idx = 0;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) res[idx++] = a[i] + b[j];
  sort(res, res+idx);
  m = 0;
  for(int i = 1; i < idx; i++) if(res[i] != res[i-1]) res[m++] = res[i];
}
int main()
{
  int cases;
  scanf("%d", &cases);
  while(cases--) {
    scanf("%d", &n);
    for(int i = 0; i < 5; i++)
      for(int j = 0; j < n; j++) scanf("%I64d", &a[i][j]);
    calc(a[0], a[1], p0, pe0);
    calc(a[2], a[3], p1, pe1);
    bool flag = false;
    for(int i = 0; i < n && !flag; i++) {
      ll &x = a[4][i];
      int s1 = 0, s2 = pe1-1;
      while(s1 < pe0 && s2 >= 0) {      //追逐法
        if(p0[s1] + p1[s2] + x == 0) { flag = true; break; }
        if(p0[s1] + p1[s2] + x >  0) s2--;
        else s1++;
      }
    }
    puts(flag ? "Yes" : "No");
  }
  return 0;
}
