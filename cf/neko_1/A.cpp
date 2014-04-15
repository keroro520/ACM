#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
string s;

void output();
int main()
{
	cin >> s;
	if(s.length() == 1) {
		s[0] = '0';
		output();
		return 0;
	}
	bool flag = false;
	for(int len = s.length(), i = 0; i < len; i++) if(s[i] == '0') {
		s[i] = '-';
		flag = true;
		break;
	}
	if(flag) {
		output();
		return 0;
	}
	s[s.length()-1] = '-';
	output();
	return 0;
}
void output()
{
	if(find(s.begin(), s.end(), '1') == s.end()) {
		cout << "0" << endl;
		return ;
	}
	for(int len = s.length(), i = 0; i < len; i++) if(s[i] != '-') {
		cout << s[i] ;
	}
	cout << endl;
}
