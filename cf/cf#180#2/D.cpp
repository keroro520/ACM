/*
    简单题
    题意: 对于一非严格递增序列{W} : 0 < W1 <= W2 <= W3 <= ... <= Wk
    再给出两个序列a, b. 问是否有一个{W}使得
        sum( W(ai) ) > sum( W(bi) )


    思路:   若a.size > b.size, 则直接"YES"
            sort一遍, 从大到小同时遍历a和b, 若ai <= bi, 则使W(ai) == W(bi), 就能够使得sum_a绝不会小于sum_b
            若ai > bi, 则我们可以使W(ai) >> W(bi), `>>`表远大于, 就可以使得sum_a > sum_b

*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int a[100000], b[100000];
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    if(n > m) {
        printf("YES\n");
        return 0;
    }
    
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    for(int i = 0; i < m; i++) scanf("%d", b+i);
    sort(a, a+n);
    sort(b, b+m);


    int pa = n-1;
    int pb = m-1;
    bool flag = false;
    while(pa >= 0) {
        if(a[pa] > b[pb]) {
            flag = true;
            break;
        }
        pa--;
        pb--;
    }
    printf(flag ? "YES\n" : "NO\n");
    return 0;
}
