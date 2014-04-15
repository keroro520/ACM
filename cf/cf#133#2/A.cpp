/*
    费解. 为什么第一种方法(注释掉的)不对? 
*/
#include <stdio.h>

int max(int a, int b, int c) {
    int tmp;
    if(a > b) tmp = a; else tmp = b;
    return tmp > c ? tmp : c;
}
int min(int a, int b, int c) {
    int tmp;
    if(a < b) tmp = a; else tmp = b;
    return tmp < c ? tmp : c;
}
int main()
{
    int a, b, c;
    int ans = 0;
    scanf("%d%d%d", &a, &b, &c);
    int a2 = min(a, b, c);
    int c2 = max(a, b, c);
    int b2 = a + b + c - a2 - c2;
   // for(int i = 0; i < b2; i++) {
   //     ans += a2;
   //     a2++;
   // }
   // ans *= 2;
    ans = (c2+a2-1)*(b2+a2-1);
    int tt = 0;
    for(int i = 1; i < a2; i++) tt += i;
    ans = ans - tt*2;
    printf("%d\n", ans);
    return 0;
}
