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

    int cases = 10;
    cout << cases << endl;
    while(cases--) {
        int n = rand() % 100 + 1, m = rand() % 100 + 1;
        for(int i = 0; i < n; i++) {
            cout << (char)(rand() % 26 + 'a' );
        }
        cout << endl;
        for(int i = 0; i < m; i++) {
            cout << (char)(rand() % 26 + 'a' );
        }
        cout << endl;
    }
    return 0;
}
