#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
#define MAXN 100005
string str;
int PMT[MAXN];
string print[MAXN];

void fail(string &s)
{
  int len = s.length();
  int j = 0;
  PMT[0] = 0;
  for(int i = 1; i < len; i++) {
    while(j > 0 && s[i] != s[j]) {
      j = PMT[j-1];
    }
    if(s[i] == s[j]) j++;
    PMT[i] = j;
  }
}
int KMP(string &s1, string &s2)
{
  int sum = 0, len1 = s1.length(), len2 = s2.length();
  int i = 0, j = 0;
  while(i < len1) {
    while(i < len1 && j < len2) {
      if(s1[i] != s2[j]) j -= PMT[j];
      else j++;
      i++;
    }
    if(len2 == j) {
      sum++;
      j = 0;
      i = i - len2 + 1;
    }
  }
  return sum;
}
int solve(string &s1, string &s2)
{
  fail(s2);
  return KMP(s1, s2);
}
int main()
{
  freopen("in.txt","r",stdin);
  int n, query, x, y;
  string tmp = "";
  cin >> str;
  n = 0;
  for(int i = 0, len = str.length(); i < len; i++) {
    if(str[i] == 'P') print[n++] = tmp;
    else if(str[i] == 'B' ) tmp.erase( tmp.end()-1 ) ;
    else tmp.push_back( str[i] );
  }

  scanf("%d", &query);
  while(query--) {
    scanf("%d%d", &x, &y);
    if(x > n || y > n) { puts("0"); continue; }
    printf("%d\n", solve(print[y-1], print[x-1]));
  }
  return 0;
}
