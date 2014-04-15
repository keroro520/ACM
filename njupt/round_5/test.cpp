#include <stdio.h>

int main()
{
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &N);
        long long sum = 0;
        sum += N/10 + (N % 10 >= 5);
        int tmp = 10;
        while(N >= tmp) {
            sum += tmp/10
        }
    
    }
    return 0;
}
