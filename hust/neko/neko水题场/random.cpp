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
    int cases = 10000;
    cout << cases+1 << endl;
    cout << 1000000000 << endl;
    while(cases--) {
        printf("%d\n", rand() % 1000000000+1);
    }
    return 0;
}
