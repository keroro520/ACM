/*
    问给出T, M, 是否存在n使得 nT % M =  1 成立.


    思路: 如果T, M互质, 则"YES"
*/
#include <iostream>
#include <string.h>
using namespace std;

int gcd(long long a, long long b)
{
    if(!b) return a;
    else return gcd(b, a%b);
}
int main()
{
    long long cases, m, t, prod;
    cin >> cases;
    while(cases--) {
        cin >> m >> t;
        cout << (gcd(m ,t) == 1? "Yes" : "No") << endl;
    }
    return 0;
}

