#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


int main()
{
	int Cas = 0, cases;
	string s;
	scanf("%d", &cases);
	while(cases--) {
		cin >> s;
		Cas ++;
		cout << "Case #" << Cas << ": " ;
		int len = s.length();
		if(len < 4) {
			cout << s << "nanodesu" << endl;
			continue;
		}
		if(s.substr(len-4, 4) == "desu") cout << s.substr(0, len-4) << "nanodesu" << endl;
		else cout << s << "nanodesu" << endl;
	}
}
