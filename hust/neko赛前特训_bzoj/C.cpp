/*
	好题  等题解
*/
#include <map>
#include <stdio.h>
#define MAXN 100005
using namespace std;
map<int,int> M;
int n, K, sum[MAXN], a[MAXN], pos;
int main()
{
  scanf("%d%d", &n, &K);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    if(K == a[i]) pos = i;
  }
  int ans = 0;
  for(int i = pos-1; i >= 1; i--) {
    sum[i] = sum[i+1] + (a[i] > K ? 1 : -1);
    if(sum[i] == 0) ans ++;
    if(M[sum[i]]) M[sum[i]]++; else M[sum[i]] = 1;
  }
  for(int i = pos+1; i <= n; i++) {
    sum[i] = sum[i-1] + (a[i] > K ? 1 : -1);
    if(sum[i] == 0) ans ++;
    if(M[-sum[i]]) ans += M[-sum[i]];
  }
  printf("%d\n", ans+1);
  return 0;
}
