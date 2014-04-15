/*
    思路题  操作维护题   好题

    题意：对于一个序列{pi}，定义操作f(p,k)为将序列按k个分为一组，最后一组若不够分，则含有n%k个元素，然后对于每一个小组循环左移一位。
          k从2到N依次轮转。


    思路：这种题要么就是能找到规律，直接出结果，要么就时考验对于每一轮操作f(p, k)该如何用时间复杂度较小的方法来维护。
          这里是法2.
          直接copy大牛的例子：
                1 2 3 4 5 6 7 8 9 =>
                2 3 1 5 6 3 8 9 7
                将被移动的字符看作*，于是：
                * 2 3 * 5 6 * 8 9
                  2 3 * 5 6 * 8 9 *
                这样就可以将左移变为O(1)了



     反思：这种利用“相对位置”的“相对论”有启发。发散思维，不让排列被位置(下标)束缚住，利用了“相对位置”这一点将每次循环左移复杂度降到最低
    
*/
#include <stdio.h>

int p[2000005];
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) p[i] = i;
    int start = 1;
    for(int k = 2; k <= n; k++) {
        int pos = n % k == 0 ? n-k+1 : k * (n/k) + 1;
        pos += start - 1;
        p[start+n] = p[pos];
        pos -= k;
        while(pos >= start) {
            p[pos+k] = p[pos];
            pos -= k;
        }
        start++;
//    printf("K = %d : ", k);
//    for(int i = start; i < start + n ; i++) printf("%d ", p[i]);
//    printf("\n");
    }
    for(int end = start + n, i = start; i < end; i++) printf("%d ", p[i]);
    printf("\n");
    return 0;
}
