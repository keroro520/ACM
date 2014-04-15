/*
  ʵ����
  Ҫ��n <= 1000, m <= 1000�㻹�ܹ���
  ��ʵ������ݷ�Χ����Ϊ�˿�Ԥ������~ ��Ϊn <= 100, m <= 10000���Ա�����������Ӷ�m*n*100
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define MAXN 105
#define MAXM 10005*2
typedef long long ll;
int a[MAXN][MAXM], pre[MAXN][MAXM], after[MAXN][MAXM];
int n, m, M;
ll calc(int col)
{
  ll sum = 0;
  for(int i = 0; i < n; i++)
    sum += min(abs((ll)col-(ll)after[i][col]), abs((ll)col-(ll)pre[i][col]));
  return sum;
}
int main()
{
  scanf("%d%d", &n, &m);
  M = m * 2;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) scanf("%1d", &a[i][j]);
    for(int j = m; j < M; j++) a[i][j] = a[i][j-m];
    int p = -999999999;
    for(int j = 0; j < M; j++)
      if(a[i][j] == 1) {
        pre[i][j] = j;
        p = j;
      } else pre[i][j] = p;
    int q = -999999999;
    for(int j = M-1; j >= 0; j--)
      if(a[i][j] == 1) {
        after[i][j] = j;
        q = j;
      } else after[i][j] = q;
  }

  ll ans = 999999999;
  for(int j = 0; j < M; j++)
      ans = min(ans, calc(j));
  if(ans == 999999999) ans =  -1 ;
  printf("%I64d\n", ans);
  return 0;
}
