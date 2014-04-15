#include <stdio.h>
#define     MAXN    105
int a[MAXN][MAXN];
int K;
int main()
{
    scanf("%d", &K);
    int ans, sum = 0;
    bool flag = false;
    a[1][2] = a[2][1] = 1;
    for(int i = 3; i && !flag; i++) {
        int j;
        for(j = 1; j <= i - 2; j++) {
            sum += j;
            if(sum >= K) {
                flag = true;
                break;
            }
        }
        if(!flag) {
            for(int k = 1; k <= i; k++) a[i][k] = a[k][i] = 1;
        } else {
            for(int k = 1; k <= j; k++) a[i][k] = a[k][i] = 1;
            a[i][j+1] = a[j+1][i] = 1;
            ans = i;
        }
    }
    printf("%d\n", ans);
    for(int i = 1; i <= ans; i++) {
        for(int j = 1; j <= ans; j++) {
            if(i == j)printf("0");
            else printf("%d", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
