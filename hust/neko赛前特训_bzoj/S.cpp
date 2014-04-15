  //简单题，用笔演算一下就有思路了
  #include <stdio.h>
  #include <string.h>
  #include <algorithm>
  #include <functional>
  using namespace std;
  #define MAXN 1005
  int head[MAXN], a[MAXN], p[MAXN];
  int n, K;
  int main()
  {
    scanf("%d%d", &n, &K);
    for(int i = 1; i <= K; i++) scanf("%d", &a[i]);
    sort(a+1, a+K+1, greater<int>() );

    int i = 1, j = n, ans = 0;
    while(i <= j) {
      p[i] = p[j] = i;
      i++, j--;
      if(i > K) i = K;
    }
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; i++)
      if(head[p[i]] == -1) head[p[i]] = i;
      else ans += a[p[i]] * (i - head[p[i]]) , head[p[i]] = i;
    printf("%d\n", ans);
  }
