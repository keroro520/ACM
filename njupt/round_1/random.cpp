#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int a[1000000];
#define     MAX     10
#define     MAXN    10
int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % MAXN + 1;
    int m = rand() % MAXN + 1;
    int t = rand() % MAXN + 1;
    cout << n << " " << t << " " << m << endl;
    a[0] = rand() % MAX;
    for(int i = 1; i < m; i++) {
        a[i] = a[i-1] + rand() % MAX;
    }
    for(int i = 0; i < m; i++) cout << a[i] << endl;

    return 0;
}
