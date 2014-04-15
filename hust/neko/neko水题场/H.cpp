/*
    WA  估计是数据有问题，对拍没错，到论坛找数据也没错，猜测是我用了long long。
*/
//lightoj_1142
#include <stdio.h>
#include <iostream>
using namespace std;

long long calc(long long x)
{
    int i;
    for(i = 0; i < 64; i++) if((x & (1LL << i)) != 0) break;
    for(i = i + 1; i < 64; i++) if((x & (1LL << i)) == 0) break;
    x ^= (1LL << i);
    int sum = 0;
    for(i = i - 1; i >= 0; i--) if(x & (1LL << i)) {
        sum++;
        x ^= (1LL << i);
    }
    for(sum = sum - 1, i = 0; sum > 0; sum--, i++) x ^= (1LL << i);
    return x;
}
int main()
{
    int cases, Cas;
    long long x;
    scanf("%d", &cases);
    while(cases--) {
        cin >> x;
        cout << "Case " << ++Cas << ": " << calc(x) << endl;
        //scanf("%lld", &x);
        //printf("Case %d: %lld\n", ++Cas, calc(x));
    }
    return 0;
}
