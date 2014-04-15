/*
  STL使用 数据结构
  一道一眼题因为排序方向搞错了WA死...早早就写完了，还比neko的简洁好多，就因为sort方向=_=
*/
#include <algorithm>
#include <stdio.h>
#include <map>
#include <queue>
#include <functional>
using namespace std;
#define MAXN 8005
int n, K, Index = 0;
map<int, int> M;
priority_queue<int> Q[MAXN], ok;
int sz[MAXN];
int main()
{
   // freopen("in.txt","r",stdin);
    int x, y;
    scanf("%d%d", &n, &K);

    for(int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        if(!M[x]) M[x] = ++Index;
        Q[ M[x] ].push( y );
    }
    if(Index < K) {
        puts("0 0");
        return 0;
    }
    for(int i = 1; i <= Index; i++) sz[i] = Q[ i ].size();
    sort(sz+1, sz+1+Index, greater<int>() );
    int len = sz[K];

    for(int i = 1; i <= Index; i++) if(Q[ i ].size() >= len) {
        int sum = 0;
        for(int j = 0; j < len; j++) {
            sum += Q[i].top();
            Q[i].pop();
        }
        ok.push( sum );
    }
    int sum = 0;
    for(int i = 0; i < K; i++) {
        sum += ok.top();
        ok.pop();
    }
    printf("%d %d\n", len, sum);
    return 0;
}
