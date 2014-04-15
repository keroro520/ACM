/*
    DP
    题意: 有若干个字符串，求一个最长的环，且顺序必须满足给定顺序，即后面的串只能接在前面的串的后边.

    刚开始理解错题意了, 没注意到`顺序必须满足给定顺序，即后面的串只能接在前面的串的后边.`....dfs悲剧..
                                 
    题目给出的list是按时间先后给出的, 所以list里后辈肯定在前辈后面, 这就构成了DP的无后效性.
*/
#include <string>
#include <iostream>
using namespace std;
#define N 26
int f[N][N];
int max(int x, int y) { return x > y? x : y ; }
int main()
{
    int head, tail, len, n;
    string s;
    cin >> n;
    while(n--) {
        cin >> s;
        len  = s.length();
        head = s[0] - 'a';
        tail = s[len - 1] - 'a';
        for(int i = 0; i < N; i++) if(f[i][head])
            f[i][tail] = max(f[i][tail], f[i][head] + len);
        f[head][tail] = max(f[head][tail], len);
    }
    int ans = 0;
    for(int i = 0; i < N; i++) if(ans < f[i][i]) ans = f[i][i];
    cout << ans << endl;
    return 0;
}
