/*
    XOR     抑或   思路题
    题意：给出区间[l, r]，找出l <= a,b <= r，使得a XOR b最大.

    思路：可以证明最优异或结果总是1111..11形式的。这一点我自己做的时候没能高出来。
          来试着小证一下：当l == r时，ans = 0;
                          当l <  r时，假设l和r在第k位上的数字（二进制）不同。则k+1,k+2,...,63位的异或值肯定是0，易知b的k右部分可取2^k-1
                          所以可以这样取a，b：b = r, a取b的异或值的前k位, 后面的位数跟r一样
                          r:10101100
                          l:10000110
                          b:10101100 (r)
                          a:01010011
*/
#include <iostream>
#include <string>
using namespace std;
K
int main()
{
    long long left, right, ans = 0;
    cin >> left >> right;
    int i;
    for(i = 63; i >= 0; i--) if((left & (1LL << i)) ^ (right & (1LL << i))) break;
    for(i ; i >= 0; i--) ans |= (1LL << i);
    cout << ans << endl;
    return 0;
}
0001000
0001010



/*
int main()
{
      long long left, right;
    cin >> left >> right;
      long long mid = ~(right);
    if(left <= mid) {
        cout << (  long long)(mid ^ right) << endl;
        return 0;
    }
    for(int i = 63; i >= 0 && ((1LL << i) & mid); i--) mid ^= (1LL << i);
      long long ans = (left | mid);
    cout << "one: " << (signed long long)(ans ^ right) << endl;
    return 0;
}
*/
