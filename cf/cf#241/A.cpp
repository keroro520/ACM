#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
int p = -2*1000000000, q = 2*1000000000;
void func(int type , int x, bool right)
{
	//printf(" ? %d  %d  %d  | %d %d\n", type, x, right, p, q);
	if(right) {
		switch(type) {
			case 1 : p = max(p, x + 1); break;
			case 2 : q = min(q, x - 1); break;
			case 3 : p = max(p, x); break;
			case 4 : q = min(q, x); break;
		}
	} else {
		switch(type) {
			case 1 : q = min(q, x); break;
			case 2 : p = max(p, x); break;
			case 3 : q = min(q, x-1); break;
			case 4 : p = max(p, x+1); break;
		}
	}
}

int main()
{
	int n, x;
	char sign[100], answer[100];
	scanf("%d", &n);
	while(n--) {
		scanf("%s %d %s", sign, &x, answer);
		if( strcmp(sign, ">") == 0 ) {
			func(1, x, answer[0] == 'Y');
		} else if( strcmp(sign, "<") == 0) {
			func(2, x, answer[0] == 'Y');
		} else if( strcmp(sign, ">=") == 0) {
			func(3, x, answer[0] == 'Y');
		} else if( strcmp(sign, "<=") == 0) {
			func(4, x, answer[0] == 'Y');
		} 
		if(p > q) {
			printf("Impossible\n");
			return 0;
		}
	}
	printf("%d\n", p);
	return 0;
}
