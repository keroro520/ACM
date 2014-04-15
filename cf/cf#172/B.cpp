/*
    WA  不想做了

    大体思路是枚举b，算出a，就是细节神马的比较麻烦，不想弄。
*/
#include <stdio.h>
#include <math.h>

int main()
{
    int x,y,n;
    scanf("%d%d%d", &x, &y, &n);
    int demo, nume;
    double ans = 9999999.99999;
    for(int b = 1; b <= n; b++) {
        int a = (int)round(fabs(b * x*1.0 / y-0.000001));
        double tmp = fabs((b*x-a*y)*1.0/b*y);
        if(tmp < ans) {
            ans = tmp;
            demo = b;
            nume = a;
        }
    }
    printf("%d/%d\n", nume, demo);
    return 0;
}
