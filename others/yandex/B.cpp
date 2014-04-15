#include <stdio.h>
#include <math.h>
#define     MAXN    40005
int prime[MAXN];
bool boo[MAXN];
int top = 0;
int n;
int check(int x)
{
    if(x > n * n) return -1;
    int tmp = (int)sqrt((double)x);
    if(x == tmp*tmp) return tmp;
    else return -1;
}
void init()
{
    top = 0;
    for(int i = 2; i < MAXN; i++) if(!boo[i]) {
        int j = i;
        prime[top++] = i;
        while(j < MAXN) {
            boo[j] = true;
            j += i;
        }
    }   
}
int main()
{
    init();
    scanf("%d", &n);
    for(int i = 0; i < top; i++)
        for(int j = i; j < top; j++) {
            int tmp = check(prime[i]*prime[j]+1);
            if(tmp != -1) printf("%d\n", tmp);
        }
    return 0;
}
