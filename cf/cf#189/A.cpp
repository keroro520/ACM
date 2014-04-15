#include <string>
#include <iostream>
using namespace std;

bool check(int x) {
    return x == 1 || x == 14 || x== 144;
}
int main()
{
    string s;
    cin >> s;
    int len = s.length();
    bool flag = true;
    int pre;
    for(int i = 0; i < len; i++) {
        char ch = s[i];
        if(ch != '1' && ch != '4') {
            flag = false;
            break;
        }
        if(check(pre*10 + ch - '0')) {
            pre = pre * 10 + ch - '0';
        } else {
            pre = ch - '0';
            if(!check(pre)) {
                flag = false;
                break;
            }
        }
    }
    cout << (flag ? "YES" : "NO") << endl;
    return 0;
}
