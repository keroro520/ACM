#include <stdio.h>

int main()
{
    int n, shots, wire, number;
    int a[101];

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &shots);
    while(shots--) {
        scanf("%d%d", &wire, &number);
        if(wire > 1) a[wire-1] += number - 1;
        if(wire < n) a[wire+1] += a[wire] - number;
        a[wire] = 0;
    }
    for(int i = 1; i <= n; i++) printf("%d\n", a[i]);
    return 0;
}
