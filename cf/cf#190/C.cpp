/*
    思路题  ... 好题

    题意：初始位置为(0,0)，目标位置(a,b)，移动序列为'UDLR'组成的字符串，移动时必须按字符串左到右的顺序操作，和重复这个操作序列多次。问有没有可能到达(a,b)？

    思路：这种题的思路很简单，但比赛时的思路有点点小麻烦，而我一遇上稍微麻烦的题就跪，这个是超级打缺陷！！！ 哎，还是太弱了。

    我找我一份看起来最简洁的代码。它利用了题目的一个性质：如果在第一次执行到操作序列S的第i个操作S[i]时，位置为(x, y)，而执行完一次完整的S后位置为(cx, cy)，则再第二次执行到S[i]时位置应该时(x+cx, y+cy), 第k次是(x+k*cx, y+k*cy)。       这一点我确实没明确地意识到。
*/
#include <string>
#include <iostream>
#include <vector>
using namespace std;
vector<int> vx,vy;

int main()
{
    int a,b;
    string s;
    cin >> a >> b >> s;
    int x = 0, y = 0;
    for(int len = s.length(), i = 0; i < len; i++) {
        vx.push_back(x);
        vy.push_back(y);
        switch (s[i]) {
            case 'U' : y++; break;
            case 'D' : y--; break;
            case 'L' : x--; break;
            case 'R' : x++; break;
        }
    }
    for(int Size = vx.size(), i = 0; i < Size; i++) {
        int dx = vx[i], dy = vy[i];
        int k = 0;
        if(x != 0) k = (a-dx) / x;
        else if(y != 0) k = (b-dy) / y;

        if(k < 0 ) k = 0;
        if(dx + k*x == a && dy + k*y == b) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
    return 0;
}
