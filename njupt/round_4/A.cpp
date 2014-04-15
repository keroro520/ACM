#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     ABS(x)      ((x) < 0 ? (-(x)) : (x))
string s, t;

int main()
{
    cin >> s >> t;
    int row = t[0] - s[0];
    int col = t[1] - s[1];
    int sum = max(ABS(row), ABS(col));
    printf("%d\n", sum);
    for(int i = 0; i < sum; i++) {
        char x = ' ', y = ' ';
        if(i < ABS(row)) {
            x = (row > 0) ? 'R' : 'L';
        }
        if(i < ABS(col)) {
            y = (col > 0) ? 'U' : 'D';
        }
        if(x != ' ') printf("%c", x);
        if(y != ' ') printf("%c", y);
        printf("\n");
    }
    return 0;
}
