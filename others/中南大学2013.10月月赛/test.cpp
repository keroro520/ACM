#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

#define MAX 9223372036854775807
#define	MAXN	10
map<int,int> M;
int main()
{
    srand((unsigned)time(NULL));
	int cases = 10;
	printf("%d\n", cases);
	for(int i = 000; i <= cases; i++) M[ i] = rand() % 100;
	for(map<int,int> :: iterator it = M.begin(); it != M.end(); it ++) printf("%d %d\n", it->first, it->second);
    return 0;
}
