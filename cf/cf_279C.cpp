/*
    在VJ上搜“趣”，结果搜到个水场...这是其中一道...
*/
#include <stdio.h>
#define MAXN 100005
int n;
int dec[MAXN], inc[MAXN], a[MAXN];
int main()
{
  int l , r, query;
  scanf("%d%d", &n, &query);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);

  a[0] = 1000000000 + 10; dec[0] = 1;
  for(int i = 1; i <= n; i++)
    if(a[i] <= a[i-1]) dec[i] = dec[i-1];
    else dec[i] = i;
  a[0] = -1; inc[0] = 1;
  for(int i = 1; i <= n; i++)
    if(a[i] >= a[i-1]) inc[i] = inc[i-1];
    else inc[i] = i;
  while(query--) {
    scanf("%d%d", &l, &r);
    if(dec[r] <= l || inc[dec[r]] <= l) puts("Yes");
    else puts("No");
  }
  return 0;
}
