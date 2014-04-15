/*
  一道看起来很NB实际上很水的水题
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
int len[5];
char str[5][100];
int calc(int a, int b, int c)
{
  int l = min(len[a], len[b]), idx = 0, idx2 = 0, ans = 0;
  for( ; idx < l && str[a][idx] == str[b][idx]; idx++) ;
  ans += len[a] - idx + len[b] - idx;

  for( ; idx2 < idx && idx2 < len[c] && str[c][idx2] == str[b][idx2]; idx2++) ;
  ans += len[c] - idx2 + idx - idx2;

  return ans;
}
int main()
{
  for(int i = 0 ; i < 3; i++) {
    scanf("%d %s", &len[i], str[i]);
  }
  int ans = len[0] + len[1] + len[2];
  ans = min(ans, min(calc(0, 1, 2), min(calc(1, 2, 0), calc(0, 2, 1))));
  printf("%d\n", ans);
  return 0;
}
