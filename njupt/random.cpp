#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define MAX 9223372036854775807
#define     debug       printf("!\n")
#define     out(n)      output(n)
void output(int n) { printf("%d", n); }
void output(char ch) { printf("%c", ch); }
int main()
{
    srand((unsigned)time(NULL));
    printf("50000\n");
    for(int i = 0; i < 50000; i++) printf("%d\n", rand() % 1000000000);
    return 0;
}
