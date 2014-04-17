#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
int paper[1000], need[1000];
int main()
{
	string s;
	cin >> s;
	for(int i = 0; i < s.length(); i++) paper[s[i]] ++;
	cin >> s;
	for(int i = 0; i < s.length(); i++) need[s[i]] ++;

	int ans = 0;
	bool flag = true;
	for(char c = 'a'; c <= 'z'; c++) {
		if(need[c] && !paper[c]) flag = false;
		ans += min(paper[c], need[c]);
	}
	printf("%d\n", !flag ? -1 : ans);
	return 0;
}
