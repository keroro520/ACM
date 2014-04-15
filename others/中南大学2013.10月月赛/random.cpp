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
	int cases = 10000;
	printf("%d\n", cases);
	for(int i = 000; i <= cases; i++) printf("%d\n", i);
    return 0;
}
