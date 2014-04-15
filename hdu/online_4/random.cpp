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
	    int n = rand() % MAXN + 1;
    	int m = rand() % (n*n);
	    cout << n << " " << m << " " ;
		
		int l = rand() % 100, r = rand() % 100;
		cout << l << " " << r << " : " ;
		cout << (l*n+r*m)/(n+m) << endl;
    }

    return 0;
}
