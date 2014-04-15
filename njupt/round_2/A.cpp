#include <iostream>
using namespace std;
long long n , m , a, nn , mm;

int main()
{
    cin >> n >> m >> a;
    nn = ((n-1)/a+1)*a;
    mm = ((m-1)/a+1)*a;
    cout << (mm/a)*(nn/a) << endl;
    return 0;
}
