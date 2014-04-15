/*
  �㾭�����  ƴ��n���ַ���ʹ�ý���ֵ�����С
  ��ʼ����ʱ����˼������ݣ������޸ıȽϺ���cmp()��������ܸ��ӣ�WA�˼���
  ������һ������һ������ƴ�ӷ��Ƚ�~Ȼ������һ��Ϳ�����

  ����neko˵ֱ�ӿ��ż��ɣ�Ȼ��������Ϊʲôƴ�ӱȽ��д�����blablaû���۳�����
*/
#include <string>
#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 105
vector<int> v[MAXN];
string s[MAXN];
int in[MAXN];
deque <int> Q;
int n;
bool cmp(int i, int j)
{
  string s1 = s[i] + s[j], s2 = s[j] + s[i];
  if(s1 != s2) return s1 < s2;
  return i < j;
//  int len1 = s[i].length(), len2 = s[j].length(), len = min(len2, len1);
////  for(int k = 0; k < len; k++) if(s[i][k] != s[j][k]) return s[i][k] < s[j][k];
//  if(len1 > len2) {
////    for(int k = len2; k < len1; k++)
//      if(s[i][k] != s[j][k%len2]) return s[i][k] < s[j][k%len2];
//  } else {
//    for(int k = len1; k < len2; k++)
//      if(s[j][k] != s[i][k%len1]) return s[i][k%len1] < s[j][k];
//  }

//  if(s[i] == s[j]) return i < j;
//  else return len1 < len2;
}
void topsort()
{
  Q.clear();
  for(int i = 0; i < n; i++) if(in[i] == 0) Q.push_back(i);
  while(!Q.empty()) {
    int u = Q.front(); Q.pop_front();
    cout << s[u];
    for(int i = 0; i < v[u].size(); i++) {
      int w = v[u][i];
      if(--in[w] == 0) Q.push_back(w);
    }
  }
}
int main()
{
  cin >> n;
  for(int i = 0 ;i < n; i++) cin >> s[i];
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) if(i != j) {
      if(cmp(i, j)) v[i].push_back(j), in[j]++;
    }
  topsort();
  return 0;
}
