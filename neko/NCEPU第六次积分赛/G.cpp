#include <stdio.h>
#define     MAXN    1000000
#define     N       1000000
int n, top = 0;
bool boo[1000005], yes[1000005];
int primes[1000000];
int main()
{
    for(int i = 2; i < N/2; i++) if(!boo[i]) {
        int j = i; 
        while(j < N) {
            boo[j] = true;
            j += i;
        }
        primes[top++] = i;
        for(j = 0; j < top; j++) 
            if(primes[j] * i > MAXN) break;
            else yes[primes[j] * i] = true;
    }
    while(scanf("%d", &n) != EOF) printf(yes[n] ? "Yes\n" : "No\n");
    return 0;
}
