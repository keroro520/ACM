#include <string>
#include <iostream>
using namespace std;

int main()
{
    string s, query;
    int n, cases, score;
    cin >> cases;
    while(cases--) {
        int ans = 0;
        cin >> s;
        cin >> n;
        while(n--) {
            cin >> query >> score;
            ans += (s.find(query) == -1) ? 0 : score;
        }
        if(ans <= -6) cout << "gg";
        else if(-5 <= ans && ans <= -1) cout << "g";
        else if(ans == 0) cout << "gs";
        else if(1 <= ans && ans <= 5) cout << "s";
        else cout << "ss";
   }
}
