#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#define MAXN 300005
typedef long long ll;
int num[100], a[MAXN];
int n, K;
char s[100];
int main()
{
  while(scanf("%d%d", &n, &K) != EOF) {
    ll  ans = 0;
    memset(num, 0, sizeof(num));
    for(int i = 0; i < K; i++) {
      scanf("%s", s);
      int len = strlen(s);
      ans += num[len];
      num[len]++;
      a[i] = len;
    }
    for(int i = K; i < n; i++) {
      scanf("%s", s);
      if(i-K-1 >= 0) num[a[i-K-1]]--;
      int len = strlen(s);
      ans += num[len];
      num[len]++;
      a[i] = len;
    }
    cout << ans << endl;
  }
  return 0;
}
