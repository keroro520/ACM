#include <stdio.h>
int n;
int boo[2000], boo2[2000];
int num[2000];
int main()
{
    int x, y;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        num[x]++;
        boo[y] = 2;
        if(boo[x] == 0) boo[x] = 1;
        if(x == y) {
            boo2[x]++;
            continue;
        }
    }
    int ans = 0;
    for(int i = 1; i <= 1000; i++)
        if(boo[i] == 1 && boo2[i] < 2) ans += num[i];
    printf("%d\n", ans);
    return 0;
}
