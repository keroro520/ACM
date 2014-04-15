#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
using namespace std;

int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % 100000 + 1;
    int m = rand() % 100000 + 1;
    cout << n << " " << m << endl;
    for(int i = 0; i < n; i++) {
        int x = rand() % (LONG_MAX) + 1;
        cout << x << " " << endl;
    }
    for(int i = 0; i < m; i++) {
        int x = rand() % (INT_MAX) + 1;
        cout << x << " " << endl;
    }

    return 0;
}
