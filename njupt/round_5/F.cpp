#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#define     MAXN    1010
using namespace std;    
int a[MAXN], b[MAXN], c[MAXN];
int main()
{
    int Case = 0, cases;
    string s0, s1;
    scanf("%d", &cases);
    while(cases--) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        if(Case != 0) printf("\n");
        printf("Case %d:\n", ++Case);
        cin >> s0 >> s1;
        int len1 = s1.length(), len0 = s0.length(), len;
        for(int i = len0-1; i >= 0; i--) a[len0-1-i] = s0[i] - '0';
        for(int i = len1-1; i >= 0; i--) b[len1-1-i] = s1[i] - '0';
        len = max(len0, len1);
        for(int i = 0; i < len; i++) {
            c[i] += a[i] + b[i];
            c[i+1] += c[i]/10;
            c[i] %= 10;
        }
        if(c[len] != 0) len++;
      
        for(int i = len0-1; i >= 0; i--) printf("%d", a[i]);
        printf(" + ");
        for(int i = len1-1; i >= 0; i--) printf("%d", b[i]);
        printf(" = ");
        for(int i = len-1; i >= 0; i--)  printf("%d", c[i]);
        printf("\n");
    }
    return 0;
}
