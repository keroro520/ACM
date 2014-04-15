#include <algorithm>
#include <string>
#include <stdio.h>
#include <map>
using namespace std;
#define MAXN 1005
int n;
map<string,int> L, R;
string s[MAXN], front[MAXN], after[MAXN];
char str[505];
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d" , &n);
		R.clear(), L.clear();  int ans = 0;
		for(int i = 0; i < n; i++) {
			scanf("%s", str), s[i] = (string) str;
			int j, len = s[i].length();
			for(j = 0; j < len; j++) 
				if(s[i][j] != s[i][0]) break;
			after[i] = s[i].substr(j-1, len-(j-1));
			L[after[i]] ++;

			for(j = len-1; j >= 0; j--)
				if(s[i][j] != s[i][len-1]) break;
			front[i] = s[i].substr(0, j+2);
			R[front[i]] ++;
		}
		//for(int i = 0; i < n; i++) {
		//	printf("%d %s %s %s\n", i, s[i].c_str(), front[i].c_str(), after[i].c_str());
		//}
		for(int i = 0; i < n; i++) {
			string tmp = front[i];
			reverse(tmp.begin(), tmp.end());
			int x = R[tmp];
			
			if(x != 0) {
				if(after[i] == tmp) x--;
				ans += x;
			}
			tmp = after[i];
			reverse(tmp.begin(), tmp.end());
			x = L[tmp];
			if(x != 0) {
				if(tmp == front[i]) x--;
				ans += x;
			}
		}
		printf("Case #%d: %d\n", ++Cas, ans);
	}
	return 0;
}
