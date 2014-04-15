#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 9223372036854775807
int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % 100000+1;
    int m = rand() % 100000+1;
    cout << n << " " << m << endl;
    for(int i = 0; i < m; i++) {
        int x = rand() % 20000 - 10000 + 1;
        int l = rand() % n + 1;
        int r = (l+rand()) % n + 1;
        cout << x << " " << l << " " << r << endl;
    }

    return 0;
}
