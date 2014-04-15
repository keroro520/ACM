/*
    排序(1 - 1000)，第一关键字为约数个数，第二关键字为数字的大小
*/  
#include <stdio.h>
#include <algorithm>
using namespace std;
pair<int, int> f[1005];

bool cmp(const pair<int, int> & a, const pair<int, int> & b) {
    if(a.first != b.first) return a.first < b.first;
    else return a.second > b.second;
}
void init()
{
    for(int i = 1; i <= 1000; i++) {
        f[i].first = 1;
        f[i].second = i;
        for(int j = 1; j <= i/2; j++) f[i].first += (i % j == 0);
    }
    sort(f+1, f+1001, cmp);
}
int main()
{
    int cases, Cas = 0, n;
    init();
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        printf("Case %d: %d\n", ++Cas, f[n].second);        
    }
    return 0;
}
