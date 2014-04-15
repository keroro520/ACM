#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 9223372036854775807
int main()
{
    srand((unsigned)time(NULL));

    cout << 1 << endl;
    int n = rand() % 10000 + 1;
    cout << n+1 << endl;
    for(int i = 0; i <= n; i++) {
        cout << (rand() % 2 == 0 ? '(' : ')' );
    }
    cout << endl;
    int m = rand() % 2000;
    cout << m << endl;
    for(int i = 0; i < m; i++) {
        int op = rand() % 3;
        int l = rand() % n;
        int r = l + rand() % (n-l);
        int s = rand() % 2;

        if(op == 0) cout << "query ", r += ((r - l) % 2 == 0);
        else cout << (op == 1 ? "set " : "reverse ") ;

        cout << l << " " << r << " ";
        if(op == 1) cout << (rand() % 2 == 0 ? '(' : ')') ;
        cout << endl;
    }

    return 0;
}
