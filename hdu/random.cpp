#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX 9223372036854775807
#define	MAXN	10
int main()
{
    srand((unsigned)time(NULL));
	int cases = 10;
	while(cases--) {

	    int n = rand() % 1000;
    	int m = rand() % (2*n);
	    cout <<  n << " " << m << endl;
    	for(int i = 0; i < m; i++) {
        	int x = rand() % n ;
        	int y = rand() % n ;
        	if (x == y) { i--; continue; }
			else cout << x << " " << y << endl;

		}
		cout << endl ;
    }
	puts("0 0");

    return 0;
}
