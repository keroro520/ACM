#include <stdio.h>

int main()
{
    int a,b,n;
    scanf("%d%d%d", &a, &b, &n);
    if(a % b == 0) {
        printf("%d", a);
        for(int i = 0; i < n; i++) printf("0");
        printf("\n");
        return 0;
    } 
    for(int i = 0; i < 10; i++) 
        if((a * 10 + i) % b == 0) {
            printf("%d", a*10+i);
            for(int i = 0; i < n-1; i++) printf("0");
            printf("\n");
            return 0;
        }
    printf("-1\n");
    return 0;
}
