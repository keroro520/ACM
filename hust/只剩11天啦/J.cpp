/*
	字符串hash  哈希  好题

	第一次写字符串hash
*/
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
#define  MAXN  1005
ll  hash[MAXN][2], bit[MAXN];
int len[MAXN], n;
string str[MAXN];
ll Hash(string & s, int len)
{
	ll sum = 0;
	for(int i = 0; i < len; i++) sum = sum * 26 + s[i] - 'a';
	return sum;
}
bool check(int i, int j)
{
	//前两种写法是错的，想了好久终于想通了，联系Hash函数思考。
	//ll x = hash[i][0] + bit[len[i]] * hash[j][0], y = hash[j][1] + bit[len[j]] * hash[i][1];
	//ll x = hash[j][0] * bit[len[i]] + hash[i][0], y = hash[i][1] * bit[len[j]] + hash[j][1];

	ll x = hash[i][0] * bit[len[j]] + hash[j][0], y = hash[j][1] * bit[len[i]] + hash[i][1];
	if(x != y) return 0;
	string tmp = str[i] + str[j];  int l = tmp.length();
	for(int k = 0; k < l/2; k++) if(tmp[k] != tmp[l-1-k]) return 0;
	return 1;
}
int main()
{
	bit[0] = 1;  
	for(int i = 1; i <= 500; i++) bit[i] = bit[i-1] * 26;
	int Cas = 0, cases; char __str[505];
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%s", __str);
			string s = (string) __str;
			str[i] = s;
			len[i] = s.length();
			hash[i][0] = Hash(s, len[i]);
			reverse(s.begin(), s.end());
			hash[i][1] = Hash(s, len[i]);
		}
		int ans = 0;
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(i != j) {
			ans += check(i, j);
		}
		printf("Case #%d: %d\n", ++Cas, ans);
	}
	return 0;
}
