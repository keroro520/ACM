/*
    记忆化搜索  DP  好题

    题意：一个字符串，若串中至少含有连续的3个元音字母或者至少5个辅音字母，则该串为bad，反之为good；串中字符可以是问号，问好可以被替代为任何字母，若被替代后的串都是bad，则串最终为bad；若问号被替代后都是good，则串最终为good；若问号被替代后的串可能为good可能为bad，则串最终为mixed.


    思路：归类为DP，看雷的DP题解，一知半解。
          到github搜了个记忆化搜索的，直接看代码。
          我是觉得这样记忆化搜虽然看起来很平凡，但是很妙啦...是我记忆化搞得太少吗...
*/
//lightoj 1051
#include <string.h>
#include <stdio.h>
#define     MAXN    60
char s[MAXN];
bool is_vowel[256], mem[MAXN][6][6];
bool Bad, Good;
int n;

void init()
{
    is_vowel['A'] = true; is_vowel['E'] = true; is_vowel['I'] = true;
    is_vowel['O'] = true; is_vowel['U'] = true;
}
void DP(int idx, int vow, int con)
{
    if(vow == 3 || con == 5) {
        Bad = true;
    } else if(idx == n) {
        Good = true;
    } else if(mem[idx][vow][con]) return;           //看起来搓，但简单巧妙，我是想不到..    去掉直接超时
    else {  
        char ch = s[idx];
        if(is_vowel[ch]) DP(idx+1, vow+1, 0);
        else if(ch != '?') DP(idx+1, 0, con+1);
        else {
            DP(idx+1, vow+1, 0);
            DP(idx+1, 0, con+1);
        }
        mem[idx][vow][con] = true;
    }
}
int main()
{
    int cases, Cas = 0;
    init();
    scanf("%d", &cases);
    while(cases--) {
        scanf("%s", s);
        n = strlen(s);
        memset(mem, false, sizeof(mem));
        Good = Bad = false;
        DP(0, 0, 0);
        if(Good && Bad) printf("Case %d: MIXED\n", ++Cas);
        else printf("Case %d: %s\n", ++Cas, Bad ? "BAD" : "GOOD");
    }
    return 0;
}
