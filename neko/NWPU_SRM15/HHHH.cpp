#include <stdio.h>
int a[4], b[4];

const int Bit[64] = {1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536 ,131072 ,262144 ,524288 ,1048576 ,2097152 ,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 } ;

int calc(int x)
{
    int sum = 0;
    for(int i = 0; i < 8; i++) {
        int r = x % 10;
        x /= 10;
        if(r) sum += Bit[i];
    }
    return sum;
}
bool check()
{
   for(int i = 0; i < 4; i++) {
        if(a[i] != calc(b[i])) return false;
   }
   return true;
}
int main()
{
    int cases, Case = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
        scanf("%d.%d.%d.%d", &b[0], &b[1], &b[2], &b[3]);
        if(check()) printf("Case %d: Yes\n", ++Case);
        else printf("Case %d: No\n", ++Case);
    }
    return 0;
}
