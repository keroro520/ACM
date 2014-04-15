/*
    单调栈      好题  启发题

    题意：给出一个序列，要求找到一个区间[l, r]，使得这个区间里的最大数和次最大数的XOR值最大。

    思路：一定要好好吸收这个思想。
          //贴题解：从另外一个角度考虑，当我确定一个数为次大数以后，那么对应的最大数其实是可以确定下来的了，就是左边第一个比当前数大的，和右边的第一个。这两个数都可以用单调栈来维护，因此复杂度就是O(N)，枚举一遍求最大值即可。

          如果a[i]想当区间maximum，则从i处出发从左往右扫，这个过程它都可以作为区间maximum，直到扫到一个比a[i]大的数x，扫描停止。
          如果a[i]想当区间second maximum，在上述扫描过程中，我们不是扫到一个比a[i]大的数x吗，这个时候就可以用x作为区间maximum，而a[i]就可以作为second maximum了。
          为什么我们只考虑从右往左扫，那i的右边部分呢？    其实i的右边部分对于a[i]来说是可以不用考虑的，因为对于后面的j(i < j)，我们同样也会做上述的扫描，所以“i的右边”变成了“j的左边”，这时候就帮i搞定了“i的右边”。


          上述过程用线性暴力扫的话冗余很多，所以用从大到小的单调栈来维护，减少冗余：
            <1>如果栈顶元素a[x] < a[i]，则区间[x, i] maximum = a[i], second_muximum = a[x]，将a[x]弹出栈，a[i]继续向下比较
            <2>如果栈顶元素a[x] > a[i]，则区间[x, i] maximum = a[x], second_muxinum = a[i], 将a[i]压栈，停止扫描。因为再下去扫没有意义，扫下去的区间a[i]充当不了maximum和second_maximum
            
*/
#include <stack>
#include <algorithm>
#include <stdio.h>
using namespace std;
int main()
{
    int n, x;
    scanf("%d", &n);
    stack<int> S;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        while(!S.empty() && x > S.top()) {
            ans = max(ans, x ^ S.top());
            S.pop();
        }
        if(!S.empty()) ans = max(ans, x ^ S.top());
        S.push(x);
    }
    printf("%d\n", ans);
    return 0;
}
