#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
bool cmp(int i, int j){ return i < j; }
int  min(int i, int j){ return i > j ? j : i; }
int a[101];
int main()
{
    int n;
    scanf("%d", &n);

    int N = 2*n-1;
    int neg = 0;
    int sum = 0;

    for(int i = 0; i < N; i++) {
        scanf("%d", a+i);
        if(a[i] < 0) neg++;
        a[i] = a[i] < 0 ? -a[i] : a[i];
        sum += a[i];
    }
    sort(a, a+N, cmp);

    cout << "sum: " << sum << endl;
    cout << min(neg%n, n-neg%n) << endl;
    for(int i = 0; i < min(neg%n, n-neg%n); i++) 
        sum -= 2*a[i];

    printf("%d\n", sum);
    return 0;
}
