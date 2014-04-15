#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define     debug   cout << "!" <<endl
class Pair { 
    public :
        int s, t;
        Pair(int _s, int _t) {
            s = _s; t  = _t;
        }
} ;
vector<Pair> ans;
int main()
{
    string s;
    cin >> s;
    int end = s.length()-1, sum = 0, label = end;
    for(int len = s.length(), i = len-1; i >= 0; i--) {
        if(s[i] == '(') {
            if(sum == 0) end = i-1;
            else {
                sum--;
                if(sum == 0) {
                    ans.push_back(Pair(i, end));
                    end = i - 1;
                }
            }
            label = i;
        } else {
            sum++;
        }
    }
    if(sum != 0) {
        if(end - sum > label)
            ans.push_back(Pair(label, end-sum));
    }
    if(ans.empty()) {
        cout << 0 << endl;
        return 0;
    }
    sum = 0;
    for(int Size = ans.size(), i = Size-1; i >= 0; i--) {
        sum += ans[i].t - ans[i].s + 1;
    }
    cout << max(0, sum) << endl;
//    for(int i = 0;i < ans.size(); i++) cout << ans[i].s << "  " << ans[i].t << endl;
    return 0;
}
