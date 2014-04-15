/*
    纯数组模拟栈暴搞
*/
#include <iostream>
using namespace std;
int S[10005];
int K, top , m, x, bottom;
int main()
{
    string s;
    cin >> K >> m;
    while(m--) {
        cin >> s;
        if(s == "push") {
            cin >> x;
            S[top++] = x;
            if(top - bottom > K) bottom++;
        } else {
            if(top == bottom) cout << "Empty!" << endl;
            else cout << S[--top] << endl;
        }
    }
    return 0;
}
