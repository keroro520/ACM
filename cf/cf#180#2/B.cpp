#include <string>
#include <iostream>
using namespace std;
string str;
int main()
{
    int t, x1,x2,x, y1, y2, y;

    cin >> t >> x1 >> y1 >> x2 >> y2;
    x = x2 - x1;
    y = y2 - y1;

    cin >> str;
    int ans = -1;
    bool flag1 = false, flag2 = false;
    int e, w, s, n;

    e = w = s = n = 0;
    for(int i = 0; i < t; i++) {
        e += (str[i] == 'E');
        w -= (str[i] == 'W');
        n += (str[i] == 'N');
        s -= (str[i] == 'S');

        if(e == x || w == x) flag1 = true;
        if(s == y || n == y) flag2 = true;

        if(flag1 && flag2) {
            ans = i + 1;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
