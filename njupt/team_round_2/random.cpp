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
	int n = rand()  % 50 + 1;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		printf("%d %d\n", rand() % n+1, rand() % n + 1);
	}
    return 0;
}
