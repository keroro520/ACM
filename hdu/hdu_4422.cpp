/*
    简单题

    有坑.
*/
#include <stdio.h>
#define     KILO    1024
#define     N       5
#define     debug   printf("!\n")
int n, sum, ans, tt;
int a[6];

int calc(int x)
{
    return x - (x-1)/KILO * KILO;
}
inline int max(int x, int y) { return x > y ? x : y ; }
void dfs(int many, int now)
{
    if(many == 3) {
        if(tt % KILO == 0)
            ans = max(calc(sum-tt), ans);
        return ;
    }
    if(now >= n ) return ;//|| many + n - now < 3) return ;

    tt += a[now];
    dfs(many+1, now+1);
    tt -= a[now];
    dfs(many, now+1);
}
int calc_when_n_is_4()
{
    int ans = 0;
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++) 
            ans = max(calc(a[i]+a[j]), ans);
    return ans;
}

int main()
{
    while(scanf("%d", &n) != EOF) {
        sum = tt  = 0;
        ans = -1;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        if(n <= 3) {
            printf("1024\n");
            continue;
        }
        dfs(0, 0);
        if(n == 4) {
            if(ans != -1) ans = KILO;
            else ans = calc_when_n_is_4();
        }
        if(ans == -1) ans = 0;
        printf("%d\n", ans);
   }
   return 0;
}
/*
    The Little Girl who Picks Mushrooms
    http://acm.hdu.edu.cn/showproblem.php?pid=4422
*/
