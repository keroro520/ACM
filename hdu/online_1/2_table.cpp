#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
int ans;
string ans_s;
int calc(string s)
{
	s = "~" + s + "#";
	int ans = 0;
	for(int i = 0; i < s.length(); i++) {
		int mid = i;
		int p = mid, q = mid;
		while(p >= 0 && q < s.length() && s[p] == s[q]) p--, q++;

		ans = max(ans, q-1 - (p+1) +1);

		p = mid, q= mid+1;
		while(p >= 0 && q < s.length() && s[p] == s[q]) p--, q++;

		ans = max(ans, q-1 - (p+1) +1);
	}
	return ans;
}
void dfs(int n, string s)
{	
	if(n == 0) {
		int tmp = calc(s);
		if(tmp < ans) ans = tmp, ans_s = s;
		return ;
	}
	for(char ch = '0'; ch <= '1'; ch++) {
		dfs(n-1, s+ch);
	}
}
int main()
{
	for(int i = 1; i <= 30; i++) {
		ans = 100000;
		dfs(i, "");
		printf("### %d : %d", i, ans);
		cout << "   " << ans_s << endl;
	}
	return 0;
}
