#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define     MAXN    105105
int a[MAXN];
int N, n, m, D;

long long  work(int mid)
{
    long long sum = 0;
    for(int i = 0; i < mid; i++) sum += (a[mid] - a[i]) / D;
    for(int i = mid+1; i < N; i++) sum += (a[i] - a[mid]) / D;
    return sum;
}
int main()
{
    scanf("%d%d%d", &n, &m, &D);
    N = n*m;
    for(int i = 0; i < N; i++) scanf("%d", &a[i]);
    sort(a, a+N);
    long long ans = 0;
    for(int i = 0; i < N-1; i++) 
        if((a[i+1] - a[i]) % D != 0) {
            ans = -1;
            break;
        }
    if(ans == -1) {
        printf("-1\n");
        return 0;
    }
    if((N & 1) == 1) {
        ans = work(N/2);// || work(N/2+1);
    } else ans = min(work(N/2), work((N-1)/2));
    
    cout << ans << endl;
    return 0;
}
