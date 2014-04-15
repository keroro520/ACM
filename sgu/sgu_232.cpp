/*
	最小表示法
	题意：给你一个长度为n的有数字组成的字符串，由第i个字符开始对应的无限循环小数由一定规则确定 D[[(i + 0K) mod N], D[(i + 1K) mod N], D[(i + 2K) mod N]，问你最大的无限循环小数是什么。

	思路：找不同循环节，找该循环节最大表示序列，记录最优。
		  
		  题目要求输出前N个数字，没注意道这一点，WA死了...
*/
//sgu 232
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
using namespace std;
#define		MAXN		150005
char a[MAXN];
bool vis[MAXN];
int n;
long long K;

string dfs(int st)
{
	string res = "";
	for(int i = 0; ; i++) {
		long long j = (long long)(st + (long long)i*(long long)K) % (long long)n;
		if(vis[j]) break;
		vis[j] = true;
		res += a[j];
	}
	return res;
}
string max_Presentation(string s)
{
	int len = s.length(), i = 0, j = 1, k = 0;
	while(i < len && j < len && k < len) {
		int res = s[(i+k)%len] - s[(j+k)%len];
		if(!res) k++;
		else {
			if(res < 0) i = i + k + 1;
			else j = j + k + 1;
			if(i == j) j ++;
			k = 0;
		}
	}
	i = min(i,j);
	string y(len, ' ');
	for(j = 0; j < len; i = (i+1) % len, j++)
		y[j] = s[i];
	return y;
}
int main()
{
	scanf("%d%lld", &n, &K);
		K %= n;
		while(getchar() != '\n');
		for(int i = 0; i < n; i++) scanf("%c", &a[i]);
		memset(vis, false, sizeof(vis));
		string ans = "";
		for(int i = 0; i < n; i++) if(!vis[i]) {
			string res = max_Presentation( dfs(i) );
			if(res > ans) ans = res;
		}
		for(int i = 0; i < n/ans.length(); i++)
			cout << ans;
		for(int i = 0; i < n % ans.length(); i++) cout << ans[i];
		cout << endl;
	
	return 0;
}
