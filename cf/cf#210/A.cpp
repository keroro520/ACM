 /*
	WA
 */
 #include <stdio.h>
#include <algorithm>
using namespace std;
typedef		long long 	ll;
#define		MAXN		5005
int n; 
ll add[MAXN], _max[MAXN];
int main()
{
	int l, r, op, val, query;
	bool yes = true;
	scanf("%d %d", &n, &query);
	for(int i = 1; i <= n; i++) _max[i] = 1000000000;
	while(query--) {
		scanf("%d %d %d %d", &op, &l, &r, &val);
		if(op == 1) {
			while(l <= r) {
				add[l] += val;
				l++;
			}
		} else {
			bool flag = false;
			while(l <= r) {
				if(_max[l] + add[l] >= val) flag = true, _max[l] = val - add[l];
				l++;
			}
			if(!flag) yes = false;
		}
	}
	for(int i = 1; i <= n; i++) if(abs(_max[i]) > 1000000000) yes = false;
	if(!yes) { puts("NO"); return 0; }
	puts("YES");
	for(int i = 1; i <= n; i++) printf("%d%c", (int)_max[i], i == n ? '\n' : ' ');
	return 0;
}
