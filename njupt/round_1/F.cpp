#include <algorithm>
#include <limits.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#define         INF         (INT_MAX-2)
#define         MAXN        105
int n;
long long a[MAXN];
long long f[MAXN];
long long price[MAXN][MAXN];
int main()
{
    long long L1, L2, L3, C1, C2, C3;
    int s,t;
    cin >> L1 >> L2 >> L3 >> C1 >> C2 >> C3;
    cin >> n >> s >> t;
    s--, t--;
    if(t < s) swap(s, t);
    for(int i = 1; i < n; i++) cin >> a[i];
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++) {
            long long d = a[i] - a[j];
            if(d <= L1) price[i][j] = price[j][i] = C1;
            else if(L1 < d && d <= L2) price[i][j] = price[j][i] = C2;
            else if(L2 < d && d <= L3) price[i][j] = price[j][i] = C3;
            else price[j][i] = price[i][j] = INF;
        }
    for(int i = 0; i < n; i++) f[i] = INF;
    f[s] = 0;
    for(int i = s+1; i <= t; i++)
        for(int j = i-1; j >= s && price[j][i] != INF; j--) 
            f[i] = min(f[i], f[j] + price[j][i]);
    cout << f[t] << endl;
    return 0;
}
