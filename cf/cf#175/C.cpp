#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     ABS(x)      ((x) > 0 ? (x) : (-(x)))
long long a[3*100005];

int main()
{
    long long  n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    long long ans = 0;
    sort(a+1, a+n+1);
    for(long long i = 1; i <= n; i++) {
        ans += (long long)ABS(a[i] - i);
    }
    cout << ans << endl;
    return 0;
}
