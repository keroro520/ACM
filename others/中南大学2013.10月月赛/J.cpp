#include <stdio.h>
#include <string.h>
#define		MAXN		20
int digit[MAXN];

int  init(int x)
{
	memset(digit, 0, sizeof(digit));
	int len = 0;
	while(x) {
		digit[len++] = x % 10;
		x /= 10;
	} 
	return len;
}
int main()
{
	int cases, n;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		if(n < 0) {
			puts("0");
			continue;
		}
		n++;
		int len = init(n);
		for(int i = len-1; i > 0; i--) if(digit[i] == digit[i-1] && digit[i] != 0) {
			int j = i-1;
			while(true) {
				digit[j]++;
				if(digit[j] == 10) digit[j] = 0, j++;
				else if(digit[j] != digit[j+1]) break;
			};
			for(int j = 0; j < i-1; j++) digit[j] = 0;
			break;
		}
		if(digit[len] != 0) len++;
		for(int i = len-1; i >= 0; i--) printf("%d", digit[i]);
		puts("");
	}
	return 0;
}
