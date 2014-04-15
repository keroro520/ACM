#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    long long x,y,M;
    cin >> x >> y >> M;
    if(x >= M || y >= M) {
        cout << 0 << endl;
        return 0;
    } else if(x <= 0 && y <= 0) {
        cout << -1 << endl;
        return 0;
    }
    if(x > y )swap(x,y);
    long long sum = 0;
    if(x < 0) {
        //sum += -x/y;
        //x = x + y*(-x/y);
    }
    if(x > y )swap(x,y);
    while(y < M) {
        x = x + y;
        if(x > y) swap(x,y);
        sum++;
    }
    cout << sum << endl;
    return 0;
}
