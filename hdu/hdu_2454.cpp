/*
	图论  简单图判定  构造判定  思路题   好题
	题意：给出一个无向图的度的序列{Degree}，问该图有没有可能是简单图（不存在平行边和自环的图）

	思路：高阳推出来的。
		  按度大到小排序。对于当前度最大的点度x，删掉该点，后面连续x个点度减1。每次执行完后还是按度大小排序一遍，保证接下来要删掉的点是度最大的点。我用优先队列搞。
*/
#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
priority_queue<int> Q;
vector<int> v;
bool check()
{
	while(!Q.empty()) {
		while(!Q.empty() && Q.top() == 0) Q.pop();
		if(Q.empty()) return true;

		v.clear();
		int x = Q.top();   Q.pop();
		while(x--) {
			if(Q.empty()) return false;
			int y = Q.top();   Q.pop();
			if(y - 1 > 0) v.push_back( y - 1 );  
		}
		for(vector<int> :: iterator it = v.begin(); it != v.end(); it++) Q.push( *it );
	}
	return true;
}
int main()
{
	int cases, n, x;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		while(!Q.empty()) Q.pop();
		for(int i = 1; i <= n; i++) {
			scanf("%d", &x);
			Q.push( x );
		}

		puts( check() ? "yes" : "no" );
	}
	return 0;
}
