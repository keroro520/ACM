#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
struct Rec {
    long long x1,x2,y1,y2;
} a[10];

int main()
{
    int n;
    cin >> n;
    long long sum = 0;
    long long bx = 99999999, by = 99999999, tx = -1, ty = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i].x1>> a[i].y1>> a[i].x2>> a[i].y2 ;
        sum += (a[i].x2-a[i].x1) * (a[i].y2-a[i].y1);
        bx = min(bx, a[i].x1);
        by = min(by, a[i].y1);
        tx = max(tx, a[i].x2);
        ty = max(ty, a[i].y2);
    }
    //printf("%lld    %lld\n", sum, (tx-bx)*(ty-by));
    cout << ((tx-bx)*(ty-by) == sum  && (tx-bx == ty - by)? "YES" : "NO") << endl;
    return 0;
}
