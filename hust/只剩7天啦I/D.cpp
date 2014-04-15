// 猜测，yes的串是不是都是回文串？
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
typedef		pair<int,int>	Pii;
#define		MOD			10003

string str;
vector<Pii> v[MOD];
int n;

bool inv_equal(int i1, int j1, int j2, int i2)
{
	for(int a = i1, b = j2; a <= j1; a++, b--)
		if(str[a] != str[b]) return false;
	return true;
}
bool judge()
{
	for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++) {
			int tmp = 0;
			for(int k = i; k <= j; k++) tmp = (tmp * 27 + str[k] - 'a') % MOD;
			v[tmp].push_back( Pii(i,j) );
		}
	for(int j = n-1; j >= 0; j--)
		for(int i = j; i >= 0; i--) {
			int tmp = 0, flag = 0;
			for(int k = j; k >= i; k--) tmp = (tmp * 27 + str[k] - 'a') % MOD;
			for(vector<Pii> :: iterator it = v[tmp].begin(); it != v[tmp].end(); it++)
				if( inv_equal(it->first,it->second, j,i) ) { flag = true; break; }
			if(!flag) return false;
		}
	return true;
}
int main()
{
	int cases;
	char s[21];
	scanf("%d", &cases);
	while(cases--) {
		for(int i = 0; i < MOD; i++) v[i].clear();
		scanf("%s", s);
		str = (string) s;
		n = str.length();
		puts(judge() ? "YES" : "NO");
	}
	return 0;
}
