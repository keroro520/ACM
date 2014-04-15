#include <stdio.h>
#include <string>
#include <set>
#include <algorithm>
using namespace std;
set<string> S[2], all;
int change[6][3][4] = {
	{ {2, 3, 1, 0}, {4, 6, 8, 23}, {5, 7, 9, 22} },
	{ {0, 1, 3, 2}, {23, 8, 6, 4}, {22, 9, 7, 5} },
	{ {8, 14, 15, 9}, {1, 7, 17, 21}, {3, 13, 19, 23} },
	{ {9, 15, 14, 8}, {21, 17, 7, 1}, {23, 19, 13, 3} },
	{ {2, 8, 17, 11}, {3, 14, 16, 5}, {6, 7, 13, 12}  },
	{ {11, 17, 8, 2}, {5, 16, 14, 3}, {12, 13, 7, 6}  }
} ;
int ans;
string Change(string s, int x)
{
	for(int i = 0; i < 3; i++) {
		char tmp = s[change[x][i][3]];
		for(int j = 3; j >= 1; j--) 
			s[ change[x][i][j] ] = s[ change[x][i][j-1] ];
		s[change[x][i][0]] = tmp;
	}
	return s;
}
int check(const string & s)
{
	int sum = 0;
	sum += (s[0] == s[1] && s[0] == s[2]     && s[0] == s[3]);
	sum += (s[4] == s[5] && s[4] == s[10]    && s[4] == s[11]);
	sum += (s[6] == s[7] && s[6] == s[12]    && s[6] == s[13]);
	sum += (s[8] == s[9] && s[8] == s[14]    && s[8] == s[15]);
	sum += (s[16] == s[17] && s[16] == s[18] && s[16] == s[19]);
	sum += (s[20] == s[21] && s[20] == s[22] && s[20] == s[23]);
	return sum;
}
void Update(int cur)
{
	for(set<string> :: iterator it = S[cur].begin(); it != S[cur].end(); it++) {
		ans = max(ans, check(*it));
	}
}
void solve(int n)
{
	all = S[0];
	Update(0);

	int cur = 1;
	while(n--) {
		S[cur].clear();
		for(set<string> :: iterator it = S[1-cur].begin(); it != S[1-cur].end(); it++) {
			for(int i = 0; i < 6; i++) {
				string res = Change(*it, i);
				if(all.find(res) == all.end()) 		//我用all来去重加速，不过不要也可以ac
				S[cur].insert(res);
			}
		}
		all.insert(S[cur].begin(), S[cur].end());
		Update(cur);
		cur = 1 - cur;
	}
}
int main()
{
	int n;
	while( scanf("%d", &n) != EOF ) {
		string s = "";	char ch;
		for(int i = 0; i < 24; i++) {
			while(ch = getchar()) if('0' <= ch  &&  ch <= '5') break;
			s += ch;
		}
		S[0].clear();
		S[0].insert(s);
		ans = 0;
		solve(n);
		printf("%d\n", ans);
	}
	return 0;
}
