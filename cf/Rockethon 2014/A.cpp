#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
string s;
int main()
{
	cin >> s ;
	int ans = 0, n  = s.length(), sum = 1;
	for(int i = 1; i < n; i++) {
		if(s[i] == s[i-1]) sum ++;
		else if ((sum & 1) == 0) ans ++ , sum = 1;
		else sum = 1;
	}
	if ((sum & 1) == 0) ans ++ ;
	printf("%d\n", ans);
	return 0;
}
