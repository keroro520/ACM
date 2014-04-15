/*
    思路题  好题
    
    题意：一个城市调查了N个人, 每个人的回答是这种形式： "我所在党派的其他人有a[i]人" . 计算城市最少人数.

    思路：a[i]+1 表i所在的党派的人数。
          刚开始只从大致思路上写，即若有a[i] == a[j]，则把i，j放在一个党派里边。1 WA。
          WA了之后才开始想细节，若数据1 1 1 1 1 过不去。
          考虑，i所在的党派人数x >= (a[i]等于x-1的人数) ，即我们要尽量让回答相同的人在同一党，同时也要保证，同一党的人数不超过a[i]+1个
*/
//lightoj 1148
#include <stdio.h>
#include <algorithm>
using namespace std;
int a[100];
int n;

int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]), a[i]++;
        sort(a, a+n);
        int tmp = 1, sum = 0;       //tmp记录当前党派有多少个人被询问到
        for(int i = 1; i < n; i++) {
            if(a[i] == a[i-1]) {   //相同元素，尽量放一块儿
                tmp++;
                if(a[i] < tmp) sum += a[i], tmp = 1;        //a[i] < tmp，说明该党容纳不了tmp个人，只能容纳tmp-1个人，所以剩余1个人只能重开一个党派
            } else {
                sum += a[i-1];        
                tmp = 1;
            }
        }
        sum += a[n-1];
        printf("Case %d: %d\n", ++Cas, sum);
    }
    return 0;
}
