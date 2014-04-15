#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define     MAXN    20
#define     MAXM    20
#define     MAXQ    10
#define MAX 9223372036854775807
int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % MAXN + 1;
    int m = rand() % MAXM + 1;
    cout << n << " " << m << endl;
    for(int i = 0; i < m; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        if(x == y) {
            i--;
            continue;
        }
        cout << x << " " << y << endl;
    }
    int q = rand() % MAXQ + 1;
    cout << q << endl;
    for(int i = 0; i < q; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        if(x == y) {
            i--;
            continue;
        }
        cout << x << " " << y << endl;
    }
    cout << 0 << " " << 0 << endl;
    return 0;
}
