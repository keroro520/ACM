#include <stdio.h>
#include <string.h>
int A;
int  a[4005*10], b[4005*10];
char str[4005];
int main()
{
	scanf("%d %s", &A, str);
	int n = strlen(str);
	for(int i = 0; i < n; i++) a[i] = str[i] - '0';
	memset(b, 0, sizeof(b));
	for(int i = 0; i < n; i++) {
		int sum = 0;
		for(int j = i; j < n; j++) {
			sum += a[j];
			b[sum]++;
		}
	}
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		int sum = 0;
		for(int j = i; j < n; j++) {	
			sum += a[j];
			if(sum > 0 && A % sum == 0 && A / sum <= n*9) ans += b[A/sum];
			else if(sum == 0 && A == 0) ans += n * (n+1) / 2;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
