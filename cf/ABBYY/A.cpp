/*
    nice idea...
*/
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define     debug   cout << "!" << endl
bool boo[256];

int calcBits(long long x)
{
    int sum = 0;
    while(x) {
        sum++;
        x /= 10;
    }
    return sum;
}
int main()
{
    string s;
    int maxP = 10;
    cin >> s;
    int top = 0;
    long long ans = 1;

    if('A' <= s[0] && s[0] <= 'Z') {
        boo[s[0]] = true;
        maxP--;
        ans *= 9;
    } else if(s[0] == '?') ans *= 9;
    for(int len = s.length(), i = 1; i < len; i++) {
        if('A' <= s[i] && s[i] <= 'Z' && !boo[s[i]] && maxP != 0) {
            ans = ans * maxP;
            maxP--;
            boo[s[i]] = true;
        } else if(s[i] == '?') {
            top++;
        }
    }
    if(top == 0) cout << ans << endl;
    else {
        cout << ans ;
        for(int i = 0; i < top; i++) printf("0");
        printf("\n");
    }
    return 0;
}
