#include <iostream>
using namespace std;

int main()
{
    long long n, K;
    cin >> n >> K;
    if(K <= (n+1)/2) {
        cout << K*2 - 1 << endl;
    } else {
        cout << (K - (n+1)/2) * 2 << endl;
    }
    return 0;
}
