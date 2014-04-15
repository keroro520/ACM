#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
#define			Pii			pair<int,int>
#define			MAXN		100005

vector< Pii > black, white;
bool fab[MAXN];
int  fa[MAXN];
int  n, m;

void fab_init()
{
	int a = 1, b = 2;
	memset(fab, false, sizeof(fab));
	fab[1] = fab[2] = true;
	do {
		fab[a+b] = true;
		swap(a, b), b = a+b;
	} while(a+b <= 100000);
}
void init()
{
	white.clear(), black.clear();
	for(int i = 1; i <= n; i++) fa[i] = i;
}
int  Find(int x) { return x == fa[x] ? x : fa[x] = Find( fa[x] ); }
void Union(int x, int y)
{   
	int fx = Find(x), fy = Find(y);
	fa[fx] = fy;
}
int main()
{
	int cases, Cas = 0, u, v, c;
	fab_init();
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &c);
			if(c) white.push_back( Pii(u, v) );
			else  black.push_back( Pii(u, v) );
		}

		int least_white = 0, most_white = 0;
		for(vector<Pii> :: iterator it = black.begin(); it != black.end(); it++) {
			u = it->first, v = it->second;
			if(Find(u) != Find(v)) Union(u, v);
		}
		for(vector<Pii> :: iterator it = white.begin(); it != white.end(); it++) {
			u = it->first, v = it->second;
			if(Find(u) != Find(v)) Union(u, v), least_white++;
		}

		bool flag = true;
		for(int i = 2; i <= n; i++) if(Find(i) != Find(1)) flag = false;
		if(!flag) { printf("Case #%d: No\n", ++Cas); continue; }


		for(int i = 1; i <= n; i++) fa[i] = i;
		for(vector<Pii> :: iterator it = white.begin(); it != white.end(); it++) {
			u = it->first, v = it->second;
			if(Find(u) != Find(v)) Union(u, v), most_white++;
		}
		for(vector<Pii> :: iterator it = black.begin(); it != black.end(); it++) {
			u = it->first, v = it->second;
			if(Find(u) != Find(v)) Union(u, v);
		}

		flag = false;
		for(int i = least_white; i <= most_white; i++) if(fab[i]) flag = true;
		printf("Case #%d: %s", ++Cas, flag ? "Yes\n" : "No\n");
	}
	return 0;
}
