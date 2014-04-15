#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    100005
#define     INF     99999999
int n, top;
int a[MAXN],result[MAXN];
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d",&a[i]);

    result[0] = INF;
    top = 0;
    int ans = 0;
    for(int i = n-1; i > -1; i--) {
        if(a[i] <= result[top]) {
            top++;
            result[top] = a[i];
            continue;
        }
        
        int sum = 0;
        while(a[i] > result[top]) {
            top--;
            sum++;
        }
        if(ans < sum) ans = sum;
        result[++top] = a[i];
        printf("!  %d  %d  top : %d\n", a[i], ans,top);
    }
    printf("%d\n", ans);
    return 0;
}
