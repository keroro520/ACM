#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#define     MAXN    1000006
int len;
int a[MAXN];
void add_one(int * a)
{
    a[0]++;
    for(int i = 0; i < len && a[i] > 9; i++) {
        a[i+1] += a[i] / 10;
        a[i] %= 10;
    }
    if(a[len] != 0) len++;
}

bool check(int * a)
{
   int sum = 0;
   for(int i = 0; i < len; i++) sum += a[i];
   return sum % 10 == 0;
}
int main()
{
    int cases;
    string x;
    scanf("%d", &cases);
    while(cases--) {
        memset(a, 0, sizeof(a));
        cin >> x;
        len = x.length();
        for(int i = 0; i < len; i++) a[len - i - 1] = x[i] - '0';
        while(true) {
            add_one(a);
            if(check(a)) {
                for(int i = len-1; i >= 0; i--) printf("%d", a[i]);
                printf("\n");
                break;
            }
        }
    }
    return 0;
}
