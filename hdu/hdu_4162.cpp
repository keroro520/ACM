/*
	最小表示法 简单题
	题意：给你一个环，相邻相减，如果小于0就加上8，求出这个新串的环中字典序最小的那个
	思路：最小表示法
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MOD			8
char s[300005];
int min_Presentation(char *s, int len)
{
	int i = 0, j = 1, k = 0;
	while(i < len && j < len && k < len) {
		int res = s[(i+k) % len] - s[(j+k)%len];
		if(!res) k++;
		else {
			if(res > 0) i = i + k + 1;
			else j = j + k + 1;
			if(i == j) j ++;
			k = 0;
		}
	}
	return min(i,j);
}
int main()
{
	while(scanf("%s", s) != EOF) {
		int len = strlen(s);
		for(int i = 0; i < len; i++) s[i] -= '0';
		int tmp = s[0];
		for(int i = 1; i < len; i++) s[i-1] = (s[i]-s[i-1]+MOD) % MOD;
		s[len-1] = (tmp - s[len-1] + MOD) % MOD;
		int idx = min_Presentation(s, len);
		printf("%c", s[idx]+'0');
		for(int i = idx+1; i != idx; i = (i+1)%len) printf("%c", s[i]+'0');
		puts("");
	}
	return 0;
}
