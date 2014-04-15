#include <stdio.h>

int main()
{
	printf("%d %d\n", 5000, 5000);
	for(int i = 0; i < 5000; i++) {
		for(int j = 0; j < 5000; j++) 
			printf("1");
		puts("");
	}
	return 0;
}
