/**
  数论 Lucas定理扩展应用  二进制
  题意： C(n,0),C(n,1),C(n,2)...C(n,n)这些数里面有多少个数是奇数

  思路：如果C(n,m)是奇数，则C(n,m) mod 2 == 1
        这里就是用到了Lucas定理了：Lucas(n,m,p)定义为C(n,m) mod P
        Lucas(n,m,p) = C(n%p,m%p) * Lucas(n/p,m/p,p)
        分析一下会发现，若Lucas(n,m,p) == 0，则说明m,n存在某一二进制位mi = 1, ni = 0(mi表
        示m的二进制第i位)；反之若Lucas(n,m,p) == 1，则需要n & m == m
        那现在我们就是要找n & m == m的m, 0 <= m <= n
        易知m的个数就是2^x，x是n的二进制表示上的 1 的个数

        学到了__builtin_popcount() 统计二进制表示上1的个数
**/
#include <stdio.h>
int main()
{
  int n;
  while(scanf("%d", &n) != EOF) {
    int x = __builtin_popcount(n);
    printf("%d\n", (1 << x));
  }
  return 0;
}
