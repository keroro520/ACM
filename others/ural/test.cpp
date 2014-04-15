#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;
#define     MAXN    200
#define     MOD     1000000007
bool visit[MAXN], exist[MAXN], boo[MAXN][MAXN];
int father[MAXN], rank[MAXN];
vector<int> v[MAXN];

long long P(int n, int m)
{
    long long t = 1;
    for(long long i = n - m + 1; i <= n; i++)
        t = t * i % MOD;
    return t;
}
int find(int x) { return x == father[x] ? x : father[x] = find(father[x]); }
void Union(int x, int y) {
    int fx = find(x), fy = find(y);
    if(rank[fx] > rank[fy]) {
        father[fx] = fy;
        rank[fy] += rank[fx];
        rank[fx] = 0;
    } else {
        father[fy] = fx;
        rank[fx] += rank[fy];
        rank[fy] = 0;
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int j;
        scanf("%d", &j);
        if(boo[i][j]) continue;
        else boo[i][j] = boo[j][i] = true;
        v[i].push_back(j);
        v[j].push_back(i);
    }

    for(int i = 1; i <= n; i++) if(v[i].size() > 2) { printf("0\n"); return 0; }

    for(int i = 1; i <= n; i++) father[i] = i;
    for(int i = 1; i <= n; i++)
        for(int Size = v[i].size(), k = 0; k < Size; k++) {
            int j = v[i][k];
            if(!visit[j]) {
                visit[j] = true;
                Union(i, j);
            }
        }
    
    int sum = 0;
    for(int i = 1; i <= n; i++) if(!exist[find(i)] && rank[father[i]] > 1) {
        sum++, 
        exist[father[i]] = true;
    }
    printf("!! %d\n", sum);
    long long ans;
    if(n <= 2) ans = 1;
    else ans = P((long long)sum, (long long)sum);
    printf("%lld\n", ans*2%MOD);
    return 0;
}
