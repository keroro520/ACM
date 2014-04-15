#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;

priority_queue< int , vector<int>, greater<int> > Q;
int n;
int main()
{
	int x, y;
	while(scanf("%d", &n) != EOF) {
		while(!Q.empty()) Q.pop();
		int ans = 0;
		for(int i = 0 ; i < n; i++) {
			scanf("%d", &x);
			Q.push(x);
		}
		for(int i = 0; i < n-1; i++) {
			x = Q.top(), Q.pop();
			y = Q.top(), Q.pop();
			ans += x + y;
			Q.push(x + y);
		}
		printf("%d\n", ans);
	}
	return 0;
}
