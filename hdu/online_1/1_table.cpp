#include <stdio.h>

int pos[10000];
int calc(int x)
{
	int i = 0, sum = 0;
	while(x) {
		sum += (x % 10) * (1 << i);
		x /= 10;
		i++;
	}
	return sum;
}
int main()
{
	printf("# %d \n", calc(1000000000-1));
	for(int i = 0; i < 1000; i++) {
		printf("%5d", calc(i));
		if((i+1) % 10 == 0) puts("");
	}
	return 0;
}
