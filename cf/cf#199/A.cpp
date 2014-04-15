#include <stdio.h>
int num[10000000];

int main()
{
	int n, x;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &x), num[x] ++;
	bool flag = true;
	if(num[7] || num[5]) flag = false;

	if(num[6] < num[3]) flag = false;
	if(num[2] < num[6] - num[3]) flag = false;
	if(num[2] - (num[6] - num[3]) != num[4]) flag = false;

	if(num[1] != num[6] + num[4] || num[1] != num[2] + num[3]) flag = false;
	if(!flag) {puts("-1"); return 0;}

	for(int i = 0; i < num[4]; i++) puts("1 2 4");
	for(int i = 0; i < num[3]; i++) puts("1 3 6");
	for(int i = 0; i < num[2] - num[4]; i++) puts("1 2 6");
	return 0;
}
