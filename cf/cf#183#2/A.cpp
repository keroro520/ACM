#include <iostream>
#include <math.h>
using namespace std;

long long square(int x) { return x * x; }
int main()
{
    int n;
    cin >> n;
    long long N = n*n;
    long long C;
    long long ans = 0;
    for(int a = 1; a < n; a++)
        for(int b = a; b <= n; b++) {
            C = a*a + b*b;
            if(C > N) break;

            ans += (square( (int)sqrt(C) ) == C) ;
        }
    cout << ans << endl;
    return 0;
}
