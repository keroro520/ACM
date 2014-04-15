#include <functional>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
char str[100];
vector<int> need, ok;

int K, n, m;
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		need.clear(), ok.clear();
		scanf("%d %d %d", &n, &m, &K);
		int sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%s", str);
			int tmp = 0;
			for(int j = 0; j < m; j++) tmp += (str[j] == '*');
			if(tmp < (m+1)/2) need.push_back(tmp), sum += tmp;
			else ok.push_back(tmp);
		}
		sort(need.begin(), need.end());//, greater<int>() );
		for(vector<int> :: iterator it = need.begin(); it != need.end() && K; it++, K--)
			ok.push_back( m - *it ), sum = sum - *it;
		for(vector<int> :: iterator it = ok.begin(); it != ok.end(); it++)
			sum += *it;
		if(!K || !(K & 1)) {
			printf("%d\n", sum);
		} else{
			sort(ok.begin(), ok.end());
			sum = sum - *ok.begin() + (m - *ok.begin());
			printf("%d\n", sum);
		}
	}
	return 0;
}
