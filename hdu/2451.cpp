/*
	构造 二分  规律
	题意：0-N有多少个数i满足：i + (i+1) + (i+2) 没有任何进位，如2 + 3 + 4和131 + 132 + 133没有进位，3 + 4 + 5就进位了。

	思路：小朱和高阳推出的规律
		  我是先预处理按位长构造出所有i，然后二分
		  构造是这样的，会发现，i有这样的规律：
		  一位: 0,   1,  2
		  两位: 10, 11, 12
		  三位: 100, 101, 102
		  	    110, 111, 112
		        120, 121, 122
				130, 131, 132 ...
		  ...
		 
		  易证，不会存在xx9, x10, x11这样的
*/
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define			MAXN		((1 << 17) + 2)
#define			VLL		vector<long long> :: iterator
typedef		long long 		ll;
vector<ll> v[20];
ll a[786432 + 100000];
int idx ;

void init()
{
	for(int i = 0; i < 3; i++) v[1].push_back( i );
	for(VLL it = v[1].begin(); it != v[1].end(); it++) {
		for(int i = 1; i < 4; i++) v[2].push_back( i*10 + *it );
	}

	ll tmp = 100;
	for(int i = 3; i <= 10; i++) {
		for(int j = 1; j < i; j++) 
			for(VLL  it = v[j].begin(); it != v[j].end(); it++) 
				for(int k = 1; k < 4; k++)
					v[i].push_back( k*tmp + *it );
		tmp *= 10;
	}
	idx = 0;
	for(int i = 1; i <= 10; i++) 
		for(VLL  it = v[i].begin(); it != v[i].end(); it++) 
			a[idx++] = *it;
	
	sort(a, a+idx);
	//for(int i = 0; i < 100; i++)printf("%lld\n", a[i]);
}
int Find(ll x)
{
	int l = 0, r = idx-1, ans = 0, mid ;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(a[mid] >= x) r = mid - 1;
		else ans = mid, l = mid + 1;
	}

	//for(int i = 0; i <= ans; i++) printf("%lld\n", a[i]);
	return ans + 1;
}
int main()
{
	init();
	ll x;
	while(scanf("%I64d", &x) != EOF) {
		//if(x > a[idx-1]) printf("%d\n", idx);
		//else 
		if(x <= 0) printf("0\n");
		else printf("%d\n", Find(x));
	}
	return 0;
}
