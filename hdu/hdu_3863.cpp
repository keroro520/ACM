/*
	博弈     做过的唯一一道不用定义变量就能A的题
	因为图是对称的，所以肯定都是先手或者后手胜。
*/
//hdu 3863
#include <stdio.h>

int main()
{
	while(getchar() != '-') {
		while(getchar() != '\n') ;
		puts("I bet on Oregon Maple~");
	}
	return 0;
}
