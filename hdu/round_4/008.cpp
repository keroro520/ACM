#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
#define     MOD     10007

vector<int> ans;
int F[12000];

void init()
{
    F[1] = F[0] = 1;
    F[2] = 2;
    F[3] = 3;
    for(int i = 4; i <= 10086; i++) F[i] = (F[i-1] + F[i-2]) % MOD;
}
int main()
{
    string s;
    int cases, Cas = 0;
    init();
    scanf("%d", &cases);
    while(cases--) {
        printf("Case %d: ", ++Cas);
        cin >> s;
        ans.clear();
        for(int len = s.length(), i = 1; i < len; i++) if(s[i] == 'e') {
           if(s[i-1] == 'h') ans.push_back(i); 
        }
        int tmp = 1;
        long long result = 1;
        bool flag = false;
        for(int Size = ans.size(), i = 1; i < Size; i++) {
            if(ans[i] == ans[i-1] + 2) tmp++, flag = true;
            else {
                result = (result * F[tmp]) % MOD; 
                tmp = 1;
            }
        }
        result = (result * F[tmp]) % MOD; 
        printf("%I64d\n" , result);
    }
    return 0;
}
