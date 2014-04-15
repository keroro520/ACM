/*
    xor 性质题    好题

    题意：求一个排列(0^n)使得0^p0 + 1^p1 + 2^p2 + ... + n^pn 最大


	思路：
        <1>自己做的时候是打表找规律，不过没找到，唯一一个游泳的规律是，当n为偶数的时候，排列的第一个是0。其实也发现了序列的数貌似有“对偶”性质，不过这对数学渣的我没意义>O<
        <2>后来看题解，题解说贪心，利用互补性质。
           Aha 了一下，因为是0~n的排列，若n为奇，则利用互补性质搞个两两配对就行了，若n为偶，则空出0位，利用到了<1>打表出来的规律。
           一上来我就用刚才打表的程序跑了一下这个思路，就是输出一下 (bit[len]-1) ^ ans[i] 是不是等于i，但发现不等于，想了好没想出来。
           又去看题解，才知道我把“互补”理解错了，互补的两个数的位数要相等，而我直接用 bit[len]-1来搞，那当然不能得到互补数啦，
               要bti[length(i)]-1 == i ^ ans[i]。既然互补要两个数的位数相等，那4的互补是3，他们的位数不相等撒？
               所以，这里就出现了我对“互补”的另一个误解，纠正：对于互补对pair<a,b>, patch(a) == patch(b) == Bit[len(max(a, b))]-1，而不是patch(a) == Bit[len(a)]-1. 这个时候要取最大位的。所以程序里有一点要特别注意，循环数倒过来跑的，因为这样能保证对于一个互补pair<a,b>,a<b，第一次遍历到的一定是b，所以len(pair) == len(b) 而不是len(pair) == len(a)!!! 


            再来看，为什么这样贪心是对的，这里有一份证明，不过我还没看：http://codeforces.com/blog/entry/7249
            因为是两两配对，任意两对不互相影响，而因为每一对都互补，都使得xor操作取得了最大值(不难想)，所以sum最大。
            
            TODO : 题解有直接就得出了sum = n*(n+1)，不理解

*/
#include <stdio.h>
#include <iostream>
using namespace std;
#define     debug   printf("!\n")
int ans[1000005], bit[100];

int len(int x)
{
    int sum = 0;
    while(x) {
        x >>= 1;
        sum++;
    }
    return sum;
}
int main()
{
    int n;
    long long sum = 0;
    bit[0] = 1;
    for(int i = 1; i < 63; i++) bit[i] = bit[i-1]<<1;
    scanf("%d", &n);
    for(int i = n; i >= 0; i--) {
        if(ans[i] != 0) continue;           //因为ans[a] != 0就能肯定和a同在一个pair里的b(a<b)已经被遍历过，那时候取道的len才是互补pair的位数，这个时候取的len(a)可能小，不正确。
        int j = bit[len(i)] - 1 - i;
        ans[i] = j;
        ans[j] = i;
        sum += 2*(bit[len(i)]-1);//2*(i ^ ans[i]);      //两种写法都可以
    }
    cout << sum << endl;
    for(int i = 0; i <= n; i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
