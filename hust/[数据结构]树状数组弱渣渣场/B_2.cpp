#include <stdio.h>
#define     MAXN        15005
#define     MAXX        32005
int c[MAXX+100], ans[MAXN+100], n;

int low(int x)
{
    return x & (x ^ (x - 1));
}
void Update(int x)
{
    if(x == 0) { c[0]++; return ; }
    while(x <= MAXX) {              //
        c[x]++;
        x += low(x);
    }
}
int Query(int x)
{   
    int sum = c[0];
    while(x) {
        sum += c[x];
        x -= low(x);
    }
    return sum;
}
  
int main()
{
    int x, y;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        ans[Query(x)]++;
        Update(x);
    } 
    for(int i = 0; i < n; i++) printf("%d\n", ans[i]);
    return 0;
}
