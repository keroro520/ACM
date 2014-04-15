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

	    int n = rand() % 5 + 1;
    	int m = rand() % 10;
		int money = rand() % 20;
	    cout << endl << endl << n << " " << m << endl;
    	for(int i = 0; i < n; i++) {
        	int x = rand() % 3+1 ;
        	int y = rand() % 3 ;
        	cout << x << " " << y << endl;
			for(int j = 0; j < x; j++) printf("%d %d\n", rand()%10, rand()%10);
		}
    }

    return 0;
}
