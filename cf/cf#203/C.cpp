/*
	好题  
	题很简单，但WA让我更理解块排的算法.........

	思考一下为什么下面两种排序结果不一样。。。待续。。。下棋先。。。
		if(abs(a.x) != abs(b.x)) return abs(a.x) < abs(b.x);
		return ABS(a.y) < ABS(b.y);

		//if(a.x != b.x) return abs(a.x) < abs(b.x);
		//return ABS(a.y) < ABS(b.y);
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define		MAXN		100005
#define		ABS(x)		((x) > 0 ? (x) : (-(x)))
class Operation {
	public : int type, num ;
	char dir;
	Operation () { }
	Operation (int type, int num, char dir) : type(type) , num(num), dir(dir) { }
} ;
vector<Operation> path;
class Node {
	public :
	int x, y;
	long long _dis()
	{
		return (long long)this->x*this->x+(long long)this->y*this->y;
	}
	friend bool operator < (Node a, Node b) {
		//return a._dis() < b._dis();									//前两种排序都是对的，但后一种排序是错的
		if(abs(a.x) != abs(b.x)) return abs(a.x) < abs(b.x);
		return ABS(a.y) < ABS(b.y);

		//if(a.x != b.x) return abs(a.x) < abs(b.x);
		//return ABS(a.y) < ABS(b.y);
	}
} a[MAXN];
int n;
void solve(Node &g)
{
	if(g.x == 0) {
		path.push_back( Operation(1, ABS(g.y), g.y>0?'U' : 'D') );
		path.push_back( Operation(2, 0, 0) );
		path.push_back( Operation(1, ABS(g.y), g.y>0?'D' : 'U') );
		path.push_back( Operation(3, 0, 0) );
	} else if(g.y == 0) {
		path.push_back( Operation(1, ABS(g.x), g.x>0?'R' : 'L') );
		path.push_back( Operation(2, 0, 0) );
		path.push_back( Operation(1, ABS(g.x), g.x>0?'L' : 'R') );
		path.push_back( Operation(3, 0, 0) );
	} else {
		path.push_back( Operation(1, ABS(g.x), g.x>0?'R' : 'L') );
		path.push_back( Operation(1, ABS(g.y), g.y>0?'U' : 'D') );
		path.push_back( Operation(2, 0, 0) );
		path.push_back( Operation(1, ABS(g.y), g.y>0?'D' : 'U') );
		path.push_back( Operation(1, ABS(g.x), g.x>0?'L' : 'R') );
		path.push_back( Operation(3, 0, 0) );
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	sort(a, a+n);
	//for(int i = 0; i < n; i++) printf("(%d %d)\n", a[i].x, a[i].y);
	int k = 0;
	//for(k = 0; k < n; k++) if(a[k].x > 0) break;
	//for(int i = k-1; i >= 0; i--) {
	//	solve(a[i]);
	//}
	for(int i = k ; i < n; i++) {
		solve(a[i]);
	}
	printf("%d\n", path.size());
	for(vector<Operation> :: iterator it = path.begin(); it != path.end(); it ++) {
		if(it->type != 1) printf("%d\n", it->type);
		else printf("%d %d %c\n", 1, it->num, it->dir);
	}
	return 0;
}
