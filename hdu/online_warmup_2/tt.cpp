#include <stdio.h>


bool check(int x)
{
	int sum = 0;
	while(x) {
		sum += x % 10;
		x /= 10;
	} 
	return sum % 10 == 0;
}
int main()
{
	int sum = 0;
	for(int i = 0; i <= 10000; i++) {
		if(check(i)) printf("# %d\n", i);
		sum += check(i);
		if(i % 100 == 0) {
			printf("%d  %d\n", i, sum);
			sum = 0;
		}
	}
	return 0;
}
