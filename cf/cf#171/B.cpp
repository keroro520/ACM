/*
    简单题      two point
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    100005
int a[MAXN];
int n, T;
int main()
{
    scanf("%d%d", &n, &T);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int time = 0, j = n-1, ans = 0;
    for(int i = n-1; i >= 0; i--) {
        if(a[i] > T) {
            j = i-1;
            time = 0;
            continue;
        } else if(time+a[i] > T) {
            time += a[i];
            while(time > T) {
                time -= a[j];
                j--;
            }
        } else {
            time += a[i];
        }
        ans = max(ans, 1 + j - i);
    }
    printf("%d\n", ans);
    return 0;
}
