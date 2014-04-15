/*
  ���ݽṹ  ջ  �����ѧ   ˼·��   ����
  ƾ��������neko����Ϯ�ˣ���neko13����14�� ~~~ O(��_��)O����~

  ���⣺��n���ַ��������ж���������ʹ�øø������㣺For every two names on the list that
        begin with the same letter sequence, all names between them on the list must also
        begin with that letter sequence.

  ˼·������һ�鱣֤�����ͬǰ׺����һ��
        ��С�����ӽ�ջ�ά��ջ�ﴮ�Ĺ���ǰ׺���ȷ��ϸ����

        Ҫ��si��ȥ��ʱ��
        <1>����ջ������si�Ĺ���ǰ׺���ȡ� ���ڵ��� ��ջ�����ʹ�ջ�����Ĺ���ǰ׺������ֱ����si��ȥ
        <2>����ջ������si�Ĺ���ǰ׺���ȡ� С�� ��ջ�����ʹ�ջ�����Ĺ���ǰ׺�����Ͱ�ջ��������ͬ��
           ��ǰ׺���ȵĴ�except��ǰ���Ǹ�����pop��������һ������p�� ans *= p
           ��ջ����'AB' 'ABC' 'ABCD'����p = 1*2*3����'AB'����ջ����
           ΪʲôҪ�����һ���أ���Ϊ��������siҪ������si��ջ��������ǰ׺С����ʱ�����ǿ���
           ��ջ���ļ���Ԫ��������һ�����p���Ǹ������ڵ�����P(n,n)������ʵpop���̾��������
           �̡�
           �������ظ���<1>��

         ������ʱ����������������һ����'A', 'AA', 'AAA'�����������<2>���Ƶظ�һ�¼��ɣ�һ
         һ����'A','B','C'���������ans *= P(S_top)

  ��ʼһֱ��string�㣬TLE������C_string������ˡ��Ҿ�˵�ҵ��㷨��O(n)����ô��TLE����Ȼ��STL
  C_string��������Neko���ҵģ�˵ʲô�±�����...

  ������֮ǰ��long long����᲻��̫��ʱ��Neko����һ���취���������int�������ʱ��ǿ��ת��
  long long��˵�ٶȻؿ�...

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
int calc(char *s1, char *s2, int &S_top, int len1, int len2)//�㹫��ǰ׺
{
  int len = min(len1, len2);
  for(int i = 0; i < len; i ++) if(s1[i] != s2[i]) return i;
  return len;
}
ll another_calc(int &S_top)//����ĩβ'A', 'AA', 'AABC'������������ʣ����ջ�ڵĴ��й���ǰ׺
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
      while(S_top && vS[S_top-1] > same) {  //����ǰ����ǰ׺same��������ϸ����
        int num = 0, tmp = vS[S_top-1];
        while(S_top && vS[S_top-1] == tmp) { //��ȳ��ȹ���ǰ׺�Ĵ�������ʣ��һ����������
          num++;
          S_top--;
        }
        ans = ((ll)ans * P[num+1]) % MOD;   //ѹ��һ������
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
