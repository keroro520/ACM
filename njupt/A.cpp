#include <stdio.h>

int main()
{
    int cases, l ,m;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &l, &m);
        printf("%d\n", m + (m - l));
    }
    return 0;
}
