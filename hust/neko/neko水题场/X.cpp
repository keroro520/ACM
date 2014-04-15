/*
    题意：给出整数a，b，-10^100 <= a <= 10^200，-2^30 <= b <= 2^30
    问b是否能整除a.

    思路：爆搞模拟高精除法即可。
*/
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


int main()
{
    int cases, Cas = 0;
    long long b ;
    string a;
    scanf("%d", &cases);
    while(cases--) {
        cin >> a >> b;
        b = b > 0 ? b : -b;
        int i = 0, len = a.length();
        long long tmp = 0;
        if(a[0] == '-') i ++;
        while(i < len) {
            if(tmp < b) tmp = tmp * 10 + a[i] - '0', i++;
            else tmp %= b;
        }
        tmp %= b;
        if(tmp) printf("Case %d: not divisible\n", ++Cas);
        else printf("Case %d: divisible\n", ++Cas);
    }
    return 0;
}
