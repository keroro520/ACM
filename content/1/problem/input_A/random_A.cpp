#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 9223372036854775807
int main()
{
    srand((unsigned)time(NULL));

    int K = rand() % 100+1;
    int m = rand() % 10000+1;
    cout << K << " " << m << endl;
    for(int i = 0; i < m; i++) {
        int op = rand() % 2;
        if(op == 0) {
            cout << "push " << rand() % (1<<31) << endl;
        } else cout << "pop" << endl;
    }

    return 0;
}
