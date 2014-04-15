#include <iostream>
#include <string>
using namespace std;
#define     MOD     1000000007
long long Bit[105];
int n;

void init() 
{
    Bit[0] = 1;
    for(int i = 1; i < n; i++) {
        Bit[i] = (Bit[i-1] << 1) % MOD;
    }
}

int main()
{
    string s;
    cin >> s;
    n = s.length();
    long long ans = 0;
    init();
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            ans += Bit[i]*Bit[n-i-1]%MOD*Bit[n-i-1]%MOD;
            ans %= MOD;
        }
    }
    cout << ans % MOD << endl;
    return 0;
}
