#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    int cases;
    string s;
    map<char, int> pos, dis;
    
    cin >> cases;
    while(cases--) {
        pos['l'] = pos['o'] = pos['v'] = pos['e'] = -1;
        dis['l'] = dis['o'] = dis['v'] = -1;
        dis['e'] = 999999;
        cin >> s;

        for(int i = 0, len = s.length(); i < len; i++) {
            if(s[i] == 'l') pos['l'] = i;
            else if(s[i] == 'o' && pos['l'] != -1) {
                pos['o'] = i;
                dis['o'] = i - pos['l'] + 1;
            } else if(s[i] == 'v' && pos['o'] != -1) {
                pos['v'] = i;
                dis['v'] = i - pos['o'] + dis['o'];
            } else if(s[i] == 'e' && pos['v'] != -1 && i - pos['v']  + dis['v'] < dis['e']) {
                pos['e'] = i;
                dis['e'] = i - pos['v'] + dis['v'];
            }
        }
        cout << ((pos['e'] == -1) ? -1 : pos['e'] - dis['e'] + 2) << endl;
   }
   return 0;
}

