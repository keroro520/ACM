/*
    简单概率DP

    第一到概率DP，其实没 什么DP思想在里面，就是neko教的解closed-form而已。。
*/
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

int gcd(int a, int b) 
{
    return b == 0 ? a : gcd(b, a % b);
}
void output(int fenzi, int fenmu)
{
    int tmp = gcd(max(fenzi, fenmu), min(fenzi, fenmu));
    printf("%d/%d\n", fenzi/tmp, fenmu/tmp);
}
int main()
{
    int cases, Cas = 0, n, x;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        int p = 0;
        double sum = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            p += (x > 0);
            sum += fabs(x * 1.0);
        }
        printf("Case %d: ", ++Cas);
        if(p == 0) printf("inf\n");
        else output((int)sum, p);
    }
    return 0;
}
