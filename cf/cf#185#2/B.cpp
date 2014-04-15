#include <stdio.h>
int main()
{
    double a,b,c,d;
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
    double q = (1-a/b) * (1-c/d);
    double a1 = 1.0;
    double ans = a1 / (1-q);
    printf("%.12lf\n", ans*(a/b));
    return 0;
}
