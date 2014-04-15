#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN        100005
int a[MAXN+MAXN+5];
int main()
{
    a[0] = 3;
    for(int i = 1; i < MAXN; i++) a[i] = a[i-1] + 3;
    a[MAXN] = 5;
    for(int i = MAXN+1; i < MAXN+MAXN; i++)  {
        int j = 5;
        do {
            a[i] = a[i-1] + j;
            j += 5;
        } while(a[i] % 3 == 0);
    }
    sort(a, a+MAXN+MAXN);
    int n;
    while(scanf("%d", &n) != EOF) printf("%d\n", a[n-1]);
    return 0;
}
