#include <stdio.h>
#define     MAXN    78500       //这里开大会ME
int prime[MAXN];
bool boo[1000005];
int N, top, result_top;
int main()
{
    scanf("%d", &N);
    for(int i = 3; i <= N; i++) if(!boo[i]) {
        prime[top++] = i;
        int j = i+i;
        while(j <= N) {
            boo[j] = true;
            j += i;
        }
    }
    for(int i = 0; i < top && prime[i] + 2 <= N; i++) if(!boo[prime[i] + 2]) {
        result_top++;
    }
    printf("%d\n", result_top);
    for(int i = 0; i < top && prime[i] + 2 <= N; i++) if(!boo[prime[i] + 2]) {
        printf("%d %d\n", 2, prime[i]);
    }
    return 0;
}
