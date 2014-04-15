#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define     MAXN    1000005
int n;
int f[MAXN+100];
int main()
{
    int x;
    for(int i = 1; i <= MAXN; i++) f[i] = (INT_MAX);
    scanf("%d", &n);
    f[0] = 0;
    for(int  i = 1; i <= MAXN; i++) {
        int  x = i;
        while(x) {
            int r = x % 10;
            x /= 10;
            if(r == 0) continue;
            f[i] = min(f[i-r]+1, f[i]);
        }
    }
    printf("%d\n", f[n]);
    return 0;
}
