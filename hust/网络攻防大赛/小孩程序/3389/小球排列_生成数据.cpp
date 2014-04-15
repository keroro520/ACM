#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int cases = 20;
int main()
{
  freopen("ball_in.txt","w",stdout);
  srand( (unsigned int)time(0) );
  printf("%d\n", cases);
  puts("5 5 5");
	puts("3 3 2");
	puts("9 9 8");
	puts("9 9 7");
	puts("0 0 1");
	puts("0 0 2");
	puts("0 0 9");
	puts("3 4 5");
	puts("7 7 8");
	puts("1 1 0");

	puts("2 2 1");
	puts("1 1 2");
	puts("1 1 1");
	puts("100000 800000 1");

	cases -= 14;
	while(cases--) printf("%d %d %d\n", rand() % 10000, rand() % 10000, rand() % 10000);
	return 0;
}
