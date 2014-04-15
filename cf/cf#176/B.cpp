#include <iostream>
using namespace std;

#define     SUM(x)      (((x)*((x)+1))>>1)
int main()
{
    long long n, K;
    cin >> n >> K;
//    if(n == 1 ) {
//        cout << 0 << endl;
//        return 0;
//    }
    if(SUM(K) < n + K - 1) {
        cout << -1 << endl;
        return 0;
    }
    long long left = 0, right = K, mid, ans = 0;
    while(left <= right) {
        mid = (left + right) >> 1;
        if(mid * K - SUM(mid-1) >= n + mid - 1)
            ans = mid, right = mid-1;
        else left = mid + 1;
    }
    cout << ans << endl;
    return 0;
}
