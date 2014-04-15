/*
    简单题

    这绝对是我在CF上见过的最唬人的题...竟然还是C题！！！
*/
#include <iostream>
#include <string>
using namespace std;
/*
1 0     1 1
0 0     0 0
1 1     0 1
*/
string s[2];
int main()
{
    for(int i = 0;i < 2; i++) cin >> s[i];
    if( s[0].length() != s[1].length() ||
        (s[0].find('1') == -1 && s[1].find('1') != -1) ||
        (s[0].find('1') != -1 && s[1].find('1') == -1)) {
            cout << "NO" << endl;
            return 0;
       }
    cout << "YES" << endl;
    return 0;
}
