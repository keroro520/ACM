#include <iostream>
using namespace std;

int cases, M, N;
int ans[1000];
long long C(int low, int big, int small)
{
    if(big == 0) {
        for(int i = N; i > small; i--) cout << ans[i] << " ";
        cout << endl;
        return 1;
    }
    if(small == 0) return 0;
    long long sum = 0;
    for(int i = big; i >= low; i--)   {
        ans[small] = i;
        sum += C(i, big-i, small-1);
    }
    return sum;
}
int main()
{
    cin >> cases;
    while(cases--) {
        cin >> M >> N;
        long long sum = 0;
        sum += C(0, M, N);
        cout << sum << endl;
    }
    return 0;
}
