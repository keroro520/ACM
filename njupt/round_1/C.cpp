#include <iostream>
#include <vector>
#include <stdio.h>
#define     MAXN    1500
using namespace std;
long long a[MAXN];
vector<int> ans;
int n, M, t;
int main()
{
    while( cin >> n >> t >> M) {
        ans.clear();
        for(int i = 0; i < M; i++) cin >> a[i];
        int num = 0;
        ans.push_back(M-1);
        for(int i = M-1; i >= 0; i--) {
            num++;
            if(num == n) {
                num = 0;
                if(i != 0) ans.push_back(i-1);
            }
        }
        long long sum = 0;
        for(int i = ans.size()-1; i > 0; i--) {
            sum = max(sum, a[ans[i]]) + 2*t;
        }
        if(ans.size() == 1) cout << a[M-1]+t << " " << 1 ;
        else cout << max(sum, a[M-1]) + t << " " << ans.size() ;
        cout << endl;
    }
    return 0;
}
