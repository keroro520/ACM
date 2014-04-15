/*
    Xor  Trie  好题 神题

    题意：给出一串数，在其首尾各取连续的一段，要使其异或和最大。

    思路：
        暴力思路：枚举i,j，O(n^2)，TLE

        Trie：其实在暴力思路中，我们每枚举一个前缀pref[i]，那接下来就只是看在接下来的所有后缀中找一个后缀，使得pref[i] XOR suff[j]最大。
              
              ***问题就转换成了“给一个数a，另外一堆数找出一个数b，使得a XOR b最大” ***
              
              想想：肯定要把这些数转换成二进制数，枚举a的最高位，要使异或值最大，就要与a对应的位不同。
              想到这里，那就好办了：把这一堆数装进一个字典树中，当然，是从最高位开始装，然后就是在这一棵字典树中尽量找出与 a 当前位不同的数，直到找到最低位为止，那么当前路径上经过的数就是我们的数 b 了，a 异或 b 也一定是最大的


              
              利用XOR的特性...于是就出现了Trie
              

        自己实现Trie的时候撮了，这里的代码是抄别人的
        竟然用到了Trie，太神了!
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN        100005
long long a[MAXN], suff[MAXN];
long long n;
class Trie { 
    public :
        Trie *children[2];
        Trie () { children[0] = children[1] = NULL; }
        void Insert(long long x, int deep) {
            if(deep == -1) return ;
            int t = ((x >> deep) & 1LL);
            if(!children[t]) {
                children[t] = new Trie();
            }
            children[t]->Insert(x, deep-1);
        }
        long long Query(long long x, int deep) {
            if(deep == -1) return 0;
            int t = ((x >> deep) & 1LL);
            if(children[!t]) {
                return (1LL << deep) + children[!t]->Query(x, deep-1);
            } else {
                return children[t]->Query(x, deep-1);
            }
            return 0;       //ATTENTION !
        }
} ;
Trie root = *(new Trie());
int main()
{
    scanf("%I64d", &n);
    for(long long i = 0; i < n; i++) scanf("%I64d", &a[i]);
    for(long long i = n-1; i >= 0; i--) suff[i] = suff[i+1] ^ a[i];
    root.Insert(0, 63);
    long long pre = 0;
    long long ans = 0;
    for(long long i = 0; i < n; i++) {
        ans = max(ans, root.Query(suff[i], 63));
        pre ^= a[i];
        root.Insert(pre, 63);
    }
    ans = max(ans, root.Query(0, 63));
    printf("%I64d\n", ans);
    return 0;
}
