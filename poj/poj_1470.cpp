/*
   题目大意是：有N堆石子，两人轮流进行操作，每一次为“操作者指定一堆石子，先从中扔掉一部分（至少一颗，可以全部扔掉），然后可以将该堆剩下的石子中的任意多颗任意移到其他未取完的堆中”，操作者无法完成操作时为负。

   思路：blog的作者是先通过小数据分析，然后推出规律的。小数据的check程序可以通过博弈DP来搞，如三堆石子的话就三元dp[a][b][c]，表示先手是否必胜.
         如果它的后继局面里有必败态， dp[a][b][c] = true
         如果它的后继局面里全是必胜态， dp[a][b][c] = false

*/
#include <algorithm>
#include <stdio.h>
using namespace std;
int a[105];
bool check(int n)
{
    sort(a, a+n);
    for(int i = 0; i < n; i += 2) if(a[i] != a[i+1]) return true;
    return false;
}
int main()
{
    int n;
    while(scanf("%d", &n) , n) {
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        if(n % 2 == 1 || check(n)) {
            puts("1");
        } else puts("0");
    }
    return 0;
}
