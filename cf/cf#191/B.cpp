#include <stdio.h>
#define     MAXN    10000005
bool boo[MAXN];
int prime[MAXN];
int n;
int main()
{
    int top = 0;
    for(int i = 2; i < MAXN; i++) {
        if(boo[i]) continue;
        prime[top++] = i;
        int j = i;
        while(j < MAXN) {
            boo[j] = true;
            j += i;
        }
    }
    scanf("%d", &n);
    for(int i = 0; i < n; i++) printf("%d ", prime[i]);
    printf("\n");
    return 0;
}
