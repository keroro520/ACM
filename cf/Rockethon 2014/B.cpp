// 读题读了半个小时！！！！！
// 找规律。或者乱搞
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
string s;
int f[1005];
int main()
{
	cin >> s;
	for(int n = s.length(), i = 0; i < n; i++) f[i] = 1;
	for(int n = s.length(), i = 1; i < n; i++) 
		for(int j = 0; j < i; j++) 
			if(s[i] == s[j] && (i-j) % 2 == 1) f[i] = max(f[i], f[j] + 1);
	int ans = 1;
	for(int n = s.length(), i = 1; i < n; i++) ans = max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}
