#include <stdio.h>
int digit[100];
bool check(int x)
{
	int len = 0;
	while(x) {
		digit[len++] = x % 10;
		x /= 10;
	}
	for(int i = 0; i < len-1; i++) if(digit[i] != 0 && digit[i] == digit[i+1]) return false;
	return true;
}
int work(int x)
{
	for(int i = x+1; ; i++) if(check(i)) return i;
}
int main()
{
	int cases, x;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &x);
		printf("%d\n", work(x));
	}
	return 0;
}

