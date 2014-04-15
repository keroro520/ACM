#include <stdio.h>

void output(int a, int b ,int c)
{
	if(a <= 0 || b <= 0 || c <= 0 || c > 100) puts("Impossible");
	else {
		for(int i = 0; i < a; i++) printf("|");
		printf("+");
		for(int i = 0; i < b; i++) printf("|");
		printf("=");
		for(int i = 0; i < c; i++) printf("|");
		puts("");
	}
}

int main() 
{
	int a = 0, b = 0, c = 0; char ch;
	while( (ch = getchar()) != '+' )  if(ch == '|') a ++;
	while( (ch = getchar()) != '=' )  if(ch == '|') b ++;
	while( (ch = getchar()) != '\n' ) if(ch == '|') c ++;
	if(a + b == c) output(a, b, c);
	else if(a + b + 2 == c) output(a+1, b, c-1);
	else if(a + b - 2 == c) {
		if(a-1 > 0) output(a-1, b, c+1);
		else output(a, b-1, c+1);
	} else puts("Impossible");
	return 0;
}
