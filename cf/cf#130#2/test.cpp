#include <string>
#include <iostream>
using namespace std;

bool dfs(string s)
{
    int len = s.length();
    if(len <= 2) return true;
    if(len >= 4 && (s[len-1] == s[len-3] || s[len-2] == s[len-4])) {
        string tmps = s.substr(0, len-2);
        tmps[len-3] = s[len-1];
        tmps[len-4] = s[len-2];
        if(dfs(tmps)) return true;
    }
    if(len >= 8 && (s[len-1] == s[len-7] || s[len-2] == s[len-8])) {
        string tmps = s.substr(0, len-2);
        tmps[len-7] = s[len-1];
        tmps[len-8] = s[len-2];
        if(dfs(tmps)) return true;
    }
    return false;
}
int main()
{
    int n;
    string s;
    cin >> n;
    getline(cin, s);
    getline(cin, s);
    string ss;
    int top = 0;
    for(int i = 0; i < s.size(); i++)
        if(s[i] != ' ') ss += s[i];

    if(dfs(ss)) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
