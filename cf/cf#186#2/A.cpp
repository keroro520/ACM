#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char s[100];
    scanf("%s", s);
    if(s[0] != '-') {
        printf("%d\n", atoi(s));
        return 0;
    }
    if(s[strlen(s)-1] < s[strlen(s)-2]) {
        s[strlen(s)-2] = s[strlen(s)-1];
        s[strlen(s)-1] = '\0';
    } else 
        s[strlen(s)-1] = '\0';
    
    printf("%d\n", atoi(s));
    return 0;
}
