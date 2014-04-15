#include <stdio.h>
#include <string.h>
long long Bit[100];

bool check(int sum)
{
    long long m = (long long)sum;
    for(int i = 0; i < 63; i++) {
        if((Bit[i] - m) % 6 == 0) return true;
    }
    return false;
}
char s[1000005];
int main()
{   
    Bit[0] = 1;
    for(int i = 1; i < 63; i++) Bit[i] = Bit[i-1] * 2;
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%s", s);
        int len = strlen(s);
        if(len == 2 && s[0] == 'M' && s[1] == 'I') {
            printf("Yes\n");
            continue;
        }
        if(s[0] != 'M') {
            printf("No\n");
            continue;
        }
        bool flag = true;
        int sum = 0;
        for(int i = 1; i < len; i++) {
            if(s[i] == 'I') sum++;
            else if(s[i] == 'U') sum += 3;
            else {flag = false; break;}
        }   
        if(!flag || sum % 2 == 1) {
            printf("No\n");
            continue;
        }
        printf(check(sum) ? "Yes\n" : "No\n"); 
    }
    return 0;
}
