/*
    

    RE了多次，把int全都换成了long long就AC了。。看来我还没掌握好C的类型隐式转换.
*/
#include <stdio.h>
#include <math.h>
#define     debug   prlong longf("!\n")

long long myPow(long long k ,long long r)
{
    long long result = 1;
    for(long long i = 0; i < r; i++) result *= k;
    return result;
}
long long solve(long long r, long long k)
{
    return (long long)k * (1 - myPow(k, r)) / (1 - k);
}

int main()
{
    long long n;
    while(scanf("%I64d", &n) != EOF) {
        long long ansR = 1, ansK = n-1;
        for(long long r = 1; r < 45; r++) {
            long long left  = 2;    // r >= 2, 因为ansR = 1了
            long long right = (long long)pow(n, 1.0/r); //@
            long long k = -1;
            while(left <= right) {   
                long long mid = (left+right) / 2; 
                long long result = solve(r, mid);
                if(result == n || result == n-1) {
                    k = mid;
                    break;
                } else if(result > n) {
                    right = mid - 1 ; 
                } else left = mid + 1;
            }

            if(k != -1) { 
                if(ansR * ansK < 0 || ansR * ansK > k * r) {
                    ansR = r;
                    ansK = k;
                }
            }
        }
        printf("%I64d %I64d\n", ansR,ansK);
    }
    return 0;
}
