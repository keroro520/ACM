/*
:
*/
#include <string>
#include <iostream>
using namespace std;

const string WUB = "WUB";

int main()
{
    string s;
    int pos = 0, new_pos;
    cin >> s;
    while(!s.empty()) {
        new_pos = s.find(WUB, pos);
        if(new_pos == -1) {     //因为这里RE了一次
            cout << s << endl;
            return 0;
        }
        if(new_pos == 0) s = s.substr(3, s.length());
        else {
            cout << s.substr(0, new_pos) << " ";
            s = s.substr(new_pos+3, s.length());
        }
    }
}
