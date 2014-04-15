//这样不能记录方案啊...
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 605
#define MAXP 1000006
int n, K, P;
int gum[MAXN], f[2][MAXP];
vector<int> v[MAXN], sv[MAXN];
int main()
{
  freopen("in.txt","r",stdin);
  int c, belong;
  scanf("%d%d%d", &n, &K, &P);
  for(int i = 1; i <= K; i++) scanf("%d", &gum[i]);
  for(int i = 1; i <= n; i++) {
    scanf("%d%d", &c, &belong);
    v[ belong ].push_back( c );
  }

  for(int i = 1; i <= K; i++) sort(v[i].begin(), v[i].end());
  for(int i = 1; i <= K; i++) {
    for(vector<int> :: iterator it = v[i].begin(); it != v[i].end(); it++)
      printf("%d  ", *it);
    puts("");
  }
  int idx = 0;
  for(int i = 1; i <= K; i++) {
    int sum = 0;
    for(int Size = v[i].size(), j = 0; j < Size; j++) {
      sum += v[i][j];
      sv[i].push_back( sum + gum[i] );
    }
  }
  int cur = 0;
  for(int i = 1; i <= K; i++) {
    for(int j = P; j >= 0; j--)
      for(int Size = sv[i].size(), k = 0; k < Size; k++) {
        f[cur][j] = max(f[cur][j], f[1-cur][j]);
        if( j >= sv[i][k] ) {
          f[cur][j] = max(f[cur][j], f[1-cur][j-sv[i][k]] + 1);
        }
      }
    cur = 1 - cur ;
  }
  printf("%d\n", f[1-cur][P]);
  return 0;
}
