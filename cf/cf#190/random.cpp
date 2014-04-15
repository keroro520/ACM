#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAXN 10007
int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % 100000;
    cout << n << endl;
    for(int i = 1; i < n; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        cout <<  y << " "  <<x<< endl;
    }
    
    return 0;
}
