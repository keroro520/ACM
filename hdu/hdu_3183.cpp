/*
    ST sparsee table应用  思路题   算好题吧
    题意：给你一个1000位的数，要你删掉m个位，求最小结果

    思路：在n个位里面删除m个位，也就是顺序找出n-m个位组成最小数
          所以，在[0,m]中找最小元素的位置i，作为ans的第一位
          在[i+1, m+1]中找最小元素的位置i'，作为ans的第二位
          在[i'+1, m+2]...
          找出n-m个数

    思路我是看题解的，能理解它的正确性，但不知道怎么想出来的orz..
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;
#define     MAXN    1005
#define     debug   printf("!\n")

const int Bit[64] = {1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536 ,131072 ,262144 ,524288 ,1048576 ,2097152 ,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 } ;
int f[MAXN][64];            //记录极值的位置，而不是极值本身
string s;
int Query(int l, int r)
{
    int j = (int)(log2(r-l+1));
    if(s[f[l][j]] <= s[f[r-Bit[j]+1][j]]) return f[l][j];
    else return f[r-Bit[j]+1][j];
}
int main()
{
    int m;
    while(cin >> s >> m) {
        int n = s.length();
        for(int i = 0; i < n; i++) f[i][0] = i; 
        for(int j = 1; Bit[j] < n; j++)
            for(int i = 0; i + Bit[j] - 1 < n; i++) 
                if(s[f[i][j-1]] <= s[f[i+Bit[j-1]][j-1]]) 
                    f[i][j] = f[i][j-1];
                else f[i][j] = f[i+Bit[j-1]][j-1];

        string ans(n, ' ');
        int i = -1;
        while(m < n) {
            i = Query(i+1, m++);
            ans[i] = '.';
        }
        bool flag = false;
        for(i = 0; i < n; i++) if(ans[i] == '.' && s[i] != '0') break;
        for(i; i < n; i++) if(ans[i] == '.') {
            printf("%c", s[i]);
            flag = true;
        }
        if(flag == false) printf("0");
        printf("\n");
    }
    return 0;
}

