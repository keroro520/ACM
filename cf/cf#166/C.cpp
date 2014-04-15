/*
    简单构造题
    题意：要求把1-n分成k份，使得每一份不构成等差数列，每一份至少3个.

    思路：1 .. n/k          :   1
          n/k+1 .. n/k+k    :   2
          ...

          n     :   k
          n-1   :   k-1
          n-2   :   k-2
          ...

          else :    k
*/
#include <stdio.h>
#define     MAXN    1000005
int a[MAXN];
int n, k;
int main()
{
    scanf("%d%d", &n, &k);
    if(n / k < 3) {
        printf("-1\n");
        return 0;
    }
    int s = 1;
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j < n/k; j++) {
            a[s++] = i;
        }
    }
    for(int i = n; n - i + 1 <= k; i--) a[i] = k - (n-i);
    for(int i = 1; i <= n; i++) if(a[i] == 0) a[i] = k;
    for(int i = 1; i <= n; i++) printf("%d\n", a[i]);
    return 0;
}
