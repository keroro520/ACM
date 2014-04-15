/*
    数学题  构造题

    **未完全弄懂细节**

    题意 : 给出长为n的unique序列s. 要求把s切分成两个长度为n的序列a, b, 
           使得: (1 <= i <= n)
            1)ai, bi都大于0
            2)si = ai + bi
            3)a,和b都是`almost unique`序列. 所谓的almost unnique序列是指, 当且仅当移除不超过[n/3]个元素后, 剩下的序列是unique序列. ps: [x] 是向上取整



    思路: 看题解知道的规律 : http://www.codeforces.com/blog/entry/7437
          另一个不错的题解: http://delta4d.github.io/
          虽然能够证明其结果正确, 但未能完全理解.


        证明该结果正确:
          以a为例,  第一阶段的a = 0, 1, ..., [n/3]-1      
                    第二阶段的忽略, 有[2n/3] - [n/3] = [n/3]个, 即使这时候这[n/3]个数都相同, 且第一阶段有一个数也与之相同, 最多也只需要删除[n/3]个数就能使a是unique
                    接下来只要证明第三阶段没有数与之前的数相等即可. 第三阶段的公式是ai = si - (n-i-1) , 令i=2n/3 + r, si=2n/3 + k, 
                      则ai = 2n/3 + k + 2n/3 + r + 1 - n = n/3 + k + r + 1
                      因为第一阶段的最后一个是([n/3]-1), 所以第三阶段的ai与第一阶段最后一个数的差为:ai - ([n/3]-1) = k+r+2 >= 2, 即说明第三阶段的a不会与之前阶段的结果有重合, 所以只需要[n/3]个即可满足a是almost unique.


        b与a不同点是, 第二阶段的数不会和第一阶段的数重合, 但是有可能第三阶段的第一个数和第二阶段的第一个重合, 所以也是最多只需要删[n/3]即可.
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100001
class Num {
    public :
    int ID, num, a, b;
};
Num s[N];
bool cmp_numeric(Num a, Num b) { return a.num < b.num; }
bool cmp_id(Num a, Num b) { return a.ID < b.ID; }

int main()
{
    int n, i;
    cin >> n;
    for(i = 0; i < n; i++) {
        cin >> s[i].num;
        s[i].ID = i;
    }
    sort(s, s+n, cmp_numeric);
    //for(i = 0; i < n; i++) cout << s[i].num << endl;

    int deadline = (n+2) / 3;
    for(i = 0; i < deadline; i++) {
        s[i].a = i;
        s[i].b = s[i].num - i;
    }
    i = deadline;
    deadline += (n-deadline+1) / 2;
    for( ; i < deadline; i++) {
        s[i].a = s[i].num - i;
        s[i].b = i;
    }
    for(i = deadline; i < n; i++) {
        s[i].b = n - i - 1;     //为什么要减1
        s[i].a = s[i].num - s[i].b;
    }

    sort(s, s+n, cmp_id);
    cout << "YES" << endl;
    for(i = 0; i < n; i++) 
        cout << s[i].a << " " ;
    cout << endl;
    for(i = 0; i < n; i++) 
        cout << s[i].b << " " ;
    cout << endl;
    return 0;
}
/*
    An equivalent definition for almost unique, is arrays with at least ⌊ 2n / 3⌋ different elements. The idea is to split s into three parts. In the first part, we give uniqueness to a. In the second part, we give uniqueness to b. In the third part, we give uniqueness to both.
*/
