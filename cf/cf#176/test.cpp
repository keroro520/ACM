/*
    未完，题意有点描述不清。别人的代码很简单，貌似是我理解错题意了。
*/
#include <stdio.h>
#define     ABS(x) ( ((x) > 0) ? (x) : (-(x)) )
int p[1000005], S[1000005];
int main()
{
    int n, T, x;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &x);
        p[x] = -p[x];
    }
    if(n & 1) {
        puts("NO");
        return 0;
    }
    int top = 1;
    S[1] = n;
    for(int i = n-1; i > 0; i--) {
        if(p[i] > 0 && p[i] == -p[S[top]]) top--;
        else S[++top] = i;
    }
    for(int i = 1; i <= top ; i++) {
        if(ABS(p[S[i]]) == ABS(
    }

    puts("YES");
    for(int i = 1; i <= n; i++) printf("%d ", p[i]);
    return 0;
}
