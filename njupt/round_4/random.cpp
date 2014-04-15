#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

bool path[105][105];
int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % 100;
    int m = rand() % (n/2/2*(n-1));
    cout << n << " " << m << endl;
    for(int i = 0; i < m; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        if(x == y || (path[x][y])) { i--; continue; }
        path[x][y] = path[y][x] = false;
        cout << x << " " << y << endl;
    }

    return 0;
}
