/*
  区间DP输出解  好题
  题意：给定一个正整数序列a(1)，a(2)，...，a(n),(1<=n<=20)
        不改变序列中元素在序列中的位置，把它们相加，并用括号记每次加法所得和，称为中间和
        现在要添上n-1对括号，加法运算依括号顺序进行，得到n-1个中间和，求出使中间和之和最小
        的添括号方法。

  思路：裸区间DP，主要是输出解...搞着搞着就出来了=_= 其实可以一遍AC的，数据没有special judge
        遇到2 2 2这种数据要输出((2+2)+2)而不能是(2+(2+2))

        输出解：output(i,j) {
                  k = find_correct_mid(i, j);
                  output(1, k), output(k+1, j);
                }
*/
/*
sample input : 4   4 1 2 3
sample output: (4+((1+2)+3))
               19
               3 6 10
*/
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
#define MAXN 25
vector<int> ans;
int n, f[MAXN][MAXN], sum[MAXN][MAXN], a[MAXN];
void output(int i, int j)
{
  if(i == j)   { printf("%d", a[i]); return ; }
  if(i == j-1) { printf("(%d+%d)", a[i], a[j]); ans.push_back(a[i]+a[j]); return ; }
  putchar('(');
  for(int k = j-1; k >= i; k--)
    if(f[i][j] == f[i][k] + f[k+1][j] + sum[i][j]) {
      output(i, k);
      putchar('+');
      output(k+1, j);
      break;
    }
  putchar(')');
  ans.push_back(sum[i][j]);
}
int main()
{
  scanf("%d", &n);
  memset(f, 127, sizeof(f));
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]), f[i][i] = 0;

  for(int i = 1; i <  n; i++) f[i][i+1] = a[i] + a[i+1];
  for(int i = 1; i <= n; i++)
    for(int j = i; j <= n; j++) sum[i][j] = sum[i][j-1] + a[j];

  for(int l = 3; l <= n; l++)
    for(int j = n; j >= l; j--) {
      int i = j - l + 1;
      for(int k = i; k < j; k++)
        f[i][j] = min(f[i][j], f[i][k] + f[k+1][j] + sum[i][j]);
    }

  output(1, n);
  printf("\n%d\n", f[1][n]);
  for(int Size = ans.size(), i = 0; i < Size; i++)
    printf("%d%c", ans[i], i == Size-1 ? '\n' : ' ');
  return 0;
}
