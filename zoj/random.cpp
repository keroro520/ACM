#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
#define     MAXN    90
#define     MAXM    20
#define     MAXQ    1000
#define MAX 9223372036854775807
void gen_tree(int n);
int work();
int main()
{
	srand((unsigned)time(NULL));
	int cases = 200;
	printf("%d\n", cases);
	while(cases--) {
		work();
	}
}
int work()
{
    int n = 3 + rand() % MAXN + 1;
	printf("%d\n", n);
	for(int i = 2; i <= n; i++) printf("%d ", rand() % n + 1);  puts("");
	for(int i = 2; i <= n; i++) printf("%d ", rand() % MAXQ + 1);  puts("");
    return 0;
}
