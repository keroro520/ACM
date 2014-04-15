#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <map>
using namespace std;
#define MOD 2000000000
#define MAXN 1600
map<int,bool> M1, M2;
int n = 1;

int main()
{
  srand( (unsigned int) time(NULL) );
  printf("%d\n", n);
  for(int i = 0; i < n; i++) {
    while(true) {
      int x = rand() % MOD + 1;
      int y = rand() % MOD + 1;
      if(!M1[x] && !M2[y]) {
        M1[x] = true, M2[y] = true;
        printf("%d %d\n", x, y);
        break;
      }
    }
  }
  return 0;
}
