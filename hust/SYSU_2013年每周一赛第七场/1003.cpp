/*
  数据结构  栈  组合数学   思路题   好题
  凭着这道题把neko给逆袭了，把neko13挤到14了 ~~~ O(∩_∩)O哈哈~

  题意：给n个字符串，问有多少种排列使得该该列满足：For every two names on the list that
        begin with the same letter sequence, all names between them on the list must also
        begin with that letter sequence.

  思路：排序一遍保证有最长共同前缀的贴一起
        从小到大扔进栈里，维护栈里串的公共前缀长度非严格递增

        要扔si进去的时候，
        <1>若‘栈顶串和si的公共前缀长度’ 大于等于 ‘栈顶串和次栈顶串的公共前缀’，则直接扔si进去
        <2>若‘栈顶串和si的公共前缀长度’ 小于 ‘栈顶串和次栈顶串的公共前缀’，就把栈顶的有相同公
           共前缀长度的串except最前面那个串都pop出来，算一个排列p， ans *= p
           如栈顶有'AB' 'ABC' 'ABCD'，则p = 1*2*3，把'AB'留在栈里面
           为什么要留最后一个呢？因为我们遇到si要进来，si跟栈顶串公共前缀小，这时候我们可以
           把栈顶的几个元素捆绑在一块儿（p就是该捆绑内的排列P(n,n)），其实pop过程就是捆绑过
           程。
           接下来重复第<1>步

         结束的时候可能有两种情况，一种是'A', 'AA', 'AAA'这种情况，跟<2>类似地搞一下即可；一
         一种是'A','B','C'这种情况，ans *= P(S_top)

  开始一直用string搞，TLE，换成C_string就秒过了。我就说我的算法是O(n)的怎么会TLE，竟然卡STL
  C_string的排序是Neko帮我的，说什么下标排序...

  还有我之前想long long计算会不会太费时，Neko教我一个办法，都定义成int，运算的时候强制转成
  long long，说速度回快...

  problem link : http://soj.me/8845
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
#define MOD   1000000007
#define MAXN 3005
char s[MAXN][MAXN];
int vS[MAXN], S[MAXN], n, ls[MAXN];
int P[MAXN];
int idx[MAXN];
void init()
{
  P[0] = P[1] = 1;
  for(int i = 2; i <= 3000; i++) P[i] = (ll)P[i-1] * i % MOD;
}
int calc(char *s1, char *s2, int &S_top, int len1, int len2)//算公共前缀
{
  int len = min(len1, len2);
  for(int i = 0; i < len; i ++) if(s1[i] != s2[i]) return i;
  return len;
}
ll another_calc(int &S_top)//处理末尾'A', 'AA', 'AABC'这类的情况，即剩余在栈内的串有公共前缀
{
  int ans = 1;
  while(S_top > 1) {
    int tmp = vS[S_top-1], num = 0;
    if(tmp == 0) return ans;
    while(S_top > 1 && tmp == vS[S_top-1]) {
      num++;
      S_top--;
    }
    ans = (ll)ans * P[num+1] % MOD;
  }
  return ans;
}
int solve()
{
  ll ans = 1;
  int S_top = 0, same = 0;
  vS[0] = vS[1] = 0;
  for(int i = 0; i < n; i++) {
    same = 0;
    if(S_top < 1 || ( same = calc( s[S[S_top-1]], s[idx[i]], S_top, ls[S[S_top-1]], ls[idx[i]])) >= vS[S_top-1] )
      S[S_top] = idx[i], vS[S_top++] = same;
    else {
      while(S_top && vS[S_top-1] > same) {  //若当前公共前缀same不满足非严格递增
        int num = 0, tmp = vS[S_top-1];
        while(S_top && vS[S_top-1] == tmp) { //相等长度公共前缀的串出来，剩第一个留在里面
          num++;
          S_top--;
        }
        ans = ((ll)ans * P[num+1]) % MOD;   //压成一个捆绑
      }
      S[S_top] = idx[i], vS[S_top++] = same;
    }
  }

  if(vS[S_top-1] != 0)
    ans = (ll)ans * (another_calc(S_top)) % MOD;
  if(vS[S_top-1] == 0)
    ans = ((ll)ans * P[ S_top ]) % MOD;
  return ans;
}
bool cmp(int l, int r) {
  return strcmp(s[l], s[r])<0;
}
int main()
{
  init();
  while(scanf("%d", &n) != EOF) {
    for(int i = 0; i < n; i++) scanf("%s", s[i]), ls[i] = strlen(s[i]), idx[i] = i;
    sort(idx, idx+n, cmp);
    cout << solve() << endl;
  }
  return 0;
}
