#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;

bool is_word(char ch)
{
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}
bool is_yuan(char ch)
{
    return  ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ;
}
bool boo[1000];
int main()
{
    string s;
    getline(cin, s); 
    int len = s.length(), n ;
    for(int i = 0; i < len; i++) printf("%c", is_word(s[i]) ? '.' : s[i]);
    printf("\n");
    n = 0;
    for(int i = 0; i < len; i++) n += is_word(s[i]);
    int deadline = (int)round(n*1.0/3);
    for(int i = 0; i < len ; i++) {
        if(is_word(s[i])) {
            if(deadline) {
                printf("%c", s[i]);
                boo[i] = true;
                deadline--;
            } else {
                printf(".");
            }
        } else printf("%c", s[i]);
    }
    printf("\n");
    bool flag = false;
    int i = 0;
    for(i = len-1; i >= 0; i--) if(boo[i] == true) break;
    int start = i+1;
    for(i = start; i < len; i++) if(is_yuan(s[i])) {
        flag = true;
        break;
    }
    if(flag) {
        for(i = 0; i < start; i++) printf("%c", s[i]);
        for(i; i < len; i++) 
            if(is_word(s[i])) {
                if(is_yuan(s[i])) printf("%c", s[i]);
                else printf(".");
            } else printf("%c", s[i]);
        printf("\n");
        return 0;
    }
    deadline = (int)round(n*1.0/3*2);
    for(int i = 0; i < len ; i++) {
        if(is_word(s[i])) {
            if(deadline) {
                printf("%c", s[i]);
                boo[i] = true;
                deadline--;
            } else {
                printf(".");
            }
        } else printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}
