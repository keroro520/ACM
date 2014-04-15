/*
    埃及分数
    是不是数据有问题呀？rqnoj第9个数据过不去，但貌似我的答案比它的优.
    http://www.rqnoj.cn/Discuss_Show.asp?DID=1750
*/
#include <iostream>
#include <string.h>
using namespace std;
int Limit;
long long ans[10000], result[10000];

long long gcd(long long a, long long b)
{
    return a % b == 0 ? b : gcd(b, a%b);
}

void symplify(long long & a, long long & b)
{
    long long g = gcd(a, b);
    a /= g;
    b /= g;
}
bool cmp(long long * a, long long * b)
{
    for(int i = Limit; i > 0; i--) if(a[i] != b[i]) return a[i] > b[i];
}
bool dfs(long long a, long long b, int deep)
{
    if(deep == Limit) {
        if(a == 1 && b > result[deep-1]) {
            result[deep] = b;
            if(cmp(ans, result)) {
                for(int i = 1; i <= deep; i++) ans[i] = result[i];
            }
            return true;
        } else return false;
    }

    long long start = b / a + 1;
    long long end   = (Limit - deep + 1) * b / a + 1;
    bool flag = false;
    for(int i = start; i <= end; i++) if(i > result[deep-1]) {
        result[deep] = i;
        long long aa = i * a - 1 * b;
        long long bb = b * i;
        symplify(aa, bb);
        flag |= dfs(aa, bb, deep+1);
    }
    return flag;
}
int main()
{
    long long a, b;
    cin >> a >> b;
    long long tmpa = a, tmpb = b;
    symplify(a, b);
    if(a == 1) {
        cout << b << endl;
        return 0;
    }
    for(Limit = 2; ; Limit++) {
        memset(ans, 127, sizeof(ans));
        if(dfs(a, b, 1)) break;
        //cout << Limit << endl;
    }
    cout << tmpa << '/' << tmpb << " = ";
    for(int i = 1; i < Limit; i++) cout << 1 << '/' << ans[i] << " + ";
    cout << 1 << '/' << ans[Limit] << endl;
    return 0;
}
