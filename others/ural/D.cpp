#include <iostream>
using namespace std;

int main()
{
    long long n, k, x;
    cin >> n >> k;
    long long sum = 0;
    for(int i = 0; i < k; i++) {
        cin >> x;
        sum += x;
    }
    cout << (sum > (k-1)*n ? sum - (k-1)*n : 0) << endl;
    return 0;
}
