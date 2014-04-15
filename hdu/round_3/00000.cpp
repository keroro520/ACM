#include <stdio.h>


int gcd(int a, int b)
{
    return (b == 0 ? a : gcd(b, a%b));
}

bool check(int a, int b)
{
    return gcd(b, a) == 1;
}

int main()
{
    int cases, n;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        int a, b;
        if(n & 1) a = n/2, b = n - a;
        else a = b = n/2;
        while(true) {
            if(check(a, b)) {
                printf("%lld\n", (long long)a*(long long)b);
                break;
            }
            a--, b++;
        }
    }
    return 0;
}
