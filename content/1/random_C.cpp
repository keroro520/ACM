#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
using namespace std;

#define     MAXN    100000
#define     MAXM    60
#define     MAXC    10000
#define     MAXP    100000
int main()
{
    srand((unsigned)time(NULL));

    int n = rand() % MAXN + 1;
    int m = rand() % MAXM + 1;
    int C = rand() % MAXC + 1;
    cout << n << " " << m << " " << C << endl;
    for(int i = 1; i <= n; i++) {
        int l = rand() % m;
        printf("%d %d ", rand()%MAXP+1, l);
        for(int j = 1; j <= l; j++) printf("%d ", rand() % m+1);
        printf("\n");
    }
    for(int i = 0; i < C; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        if(x == y) {
            i--;
            continue;
        }
        cout << x << " " << y << endl;
    }
    return 0;
}
