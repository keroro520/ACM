#include <string.h>
#include <iostream>
#include <string>
using namespace std;
#define     debug       cout << "!" << endl

int S[1<<17];
bool used[1 << 17];
int top;
string s;
bool check(int x)
{
    string tmp;
    int len = s.length();
    for(int i = 0; i < len; i++) if(x & (1 << i)) {
        tmp = tmp + s[i];
    }
    string rs(tmp.length(), '_');
    for(int len = tmp.length(), i = 0; i < len; i++) rs[i] = tmp[len - 1 - i];
    return tmp == rs;

    //for(int i = 0; i < len; i++) if(x & (1 << i)) cout << rs[i];
    //cout << " # " << endl;
    //for(int i = 0; i < len; i++) if(x & (1 << i)) cout << s[i] ;
    //cout << " $ " << endl;
    //for(int i = 0; i < len; i++) if(x & (1 << i)) {
    //    if(s[i] != rs[i]) return false;
    //}
}
void init()
{
    int len = s.length();
    top = 0;
    for(int mm = (1 << len) , i = 0; i < mm ; i++) if(check(i)) S[top++] = i;
    memset(used, false, sizeof(used));
}
bool dfs(int x, int deep)
{
    if(!x) return true;
    if(deep == 0) return false;
    for(int i = 0; i < top; i++) if(!used[i] && (x & S[i]) == S[i]) {
        used[i] = true;
        if(dfs(x ^ S[i], deep-1)) return true;
        used[i] = false;
    }
    return false;
}
int main()
{
    int cases;
    cin >> cases;
    while(cases--) {
        cin >> s;
        int len = s.length();
        init();
        int deep;
        for(deep = 1; ; deep++) if(dfs((1 << len) - 1, deep)) break;
        cout << deep << endl;
    }
    return 0;
}
