#include <stdio.h>
bool boo[100005];

int main()
{
	for(int i = 1; i <= 10002; i++) {
		int j = i-1;
		for( ; j > 0; j--) if((i+j) % 2 == 1 && (i+j) % 3 == 0) {
			boo[i] = !boo[j];
			break;
		}
	}
	for(int i = 1; i <= 10002; i++) printf("%d,", boo[i]);
	puts("");
	return 0;
}
