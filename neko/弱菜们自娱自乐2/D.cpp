/*
    思路题  贪心   好题   

    题意：给出两个重复的字符串[A, b], [C, d]，A,C分别是两串的重复单元，b,d分别是重复次数，问第二个串在第一个串出现的次数（非严格连续子序列）。note : [s,p]表示s重复p次
    
    思路：这道题太妙了。首先，[C,d]在[A,b]出现的次数 = [C, ∞]串与[A,b]串的最长公共子序列 / len(c)*d

    知道了这个以后，接下来就是求[C, ∞]串与[A,b]串的最长公共子序列的字数了：
    <1>先预处理出以C串的每个位置开头时，在A串中能匹配到的字数（因为有可能以C[i]开头，一个A串能循环匹配C串多次，所以这个字数很可能大于len(c)），我用get[i]表示“开始C[i]，匹配一个A串，能匹配多少个字母”。
    <2>接下来算[C, ∞]串与[A,b]串的最长公共子序列的字数，最好对照代码看。words表当前位置能够匹配到的字母数，也表示下一轮跟A匹配时的起始位置（想一想，为什么）
    
    
    
          和gyy讨论了好久，未果。一开始是想找出循环节，然后前后部分搞一下，就可以了。找循环节的时候是想直接从[A,b]的开始找，第一次能完全匹配[C,d]的地方就是循环节了，可是gyy给出了反例，显示要第二次完全匹配到[C,d]的部分才是最小循环节...于是就囧了。
          连CF上的题解都说最好对照着代码看...
    
*/
#include <iostream>
#include <string>
using namespace std;
int get[105];

int main()
{
    string A, C;
    int b, d;
    cin >> b >> d >> A >> C;
    int len1 = A.length(), len2 = C.length();
    for(int i = 0; i < len2; i++) {
        int k = 0;
        for(int j = 0; j < len1; j++)
            if(A[j] == C[(i+k) % len2]) k++;
        get[i] = k;         //get[i]表示C串以i开头开始匹配，能够匹配多少位字符？  //i+k有可能大于len2，所以要模
    }
    long long words = 0;        //[a,b], [c,d]最多能够匹配到的字数，注意，是字数
    for(int i = 0; i < b; i++)
        words += get[words % len2];
    cout << words/(len2*d) << endl;     //答案 = 能匹配到的总字数/[c,d]的长度
    return 0;
}
