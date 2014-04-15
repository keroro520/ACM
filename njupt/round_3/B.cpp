#include <string.h>
#include <string>
#include <iostream>
using namespace std;
#define     MAXN    1000
int f[MAXN][MAXN];
string s[2];
int main()
{
    while(cin >> s[0] >> s[1]) {
        int ans = 0;
        memset(f, 0, sizeof(f));
        f[0][0] = (s[0][0] == s[1][0]);
        for(int len1 = s[1].length(), i = 1; i < len1; i++) f[0][i] = max(f[0][i-1], (int)(s[0][0] == s[1][i]));
        for(int len0 = s[0].length(), i = 1; i < len0; i++) f[i][0] = max(f[i-1][0], (int)(s[1][0] == s[0][i]));
        for(int len0 = s[0].length(), i = 1; i < len0; i++)
            for(int len1 = s[1].length(), j = 1; j < len1; j++) {
                if(s[0][i] == s[1][j]) f[i][j] = f[i-1][j-1] + 1;
                else f[i][j] = max(max(f[i-1][j], f[i][j-1]), f[i-1][j-1]);
                //cout << ans << endl;
            }
//        for(int len0 = s[0].length(), i = 0; i < len0; i++)
//            for(int len1 = s[1].length(), j = 0; j < len1; j++) {
//                cout << i << "  " << j << "  " <<  f[i][j] << endl;
//        }
        cout << (f[s[0].length()-1][s[1].length()-1]) << endl;
    }
    return 0;
}
