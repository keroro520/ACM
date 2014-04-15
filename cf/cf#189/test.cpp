#include <stdio.h>
#define     MAXn    100005
#define     INF     999999999
#define     debug   printf("!\n");
int f[MAXn][64], a[MAXn];
int ans , n;

void init()
{   
    for(int i = 1; i <= n; i++) f[i][0] = i;
    for(int j = 1; (j<<1) <= n+1; j++) 
        for(int i = 0; i + (j<<1) - 1 <= n; i++) {
            if(a[f[i][j-1]] > a[f[i+(1<<(j-1))][j-1]])
                f[i][j] = f[i][j-1];
            else f[i][j] = f[i+(1<<(j-1))][j-1];
        }
}
int Query(int x, int y)
{
    int k, l = y - x + 1;
    for(k = 0; (1<<k) <= l; k++);
    k--;
    if(a[f[x][k]] > a[f[y-(1<<k)+1][k]]) return f[x][k];
    else return f[y-(1<<k)+1][k]; 
}
void dfs(int left, int right, int floors)
{
    if(left + 1 >= right) return;
    if(ans < floors) ans = floors;
    while(Query(left, right) == left) left++;

    while(left + 1 < right) {
        int mid = Query(left, right);
        if(mid == right)
        dfs(mid, right, floors+1);
        right = mid;
    }
}

int main()
{
    scanf("%d", &n);
    a[0] = a[n+1] = INF;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    init();
    for(int i = 1; i <= n; i++) printf("%d\n", Query(1, i));
    debug;
    ans = 0;
    dfs(1, n, 0);
    printf("%d\n", ans);
    return 0;
}
