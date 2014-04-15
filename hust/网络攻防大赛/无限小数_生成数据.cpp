#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 150000, K = 1000000000;
int main()
{
  freopen("无限小数_in_4.txt","w", stdout);
  srand( (unsigned int) time(0));
  printf("%d %d\n", n, K);
  for(int i = 0; i < n; i++) printf("%1d", rand()%10);
  puts("");
  return 0;
}
