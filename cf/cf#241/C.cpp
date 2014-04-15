#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
#define		MAXM		1005

struct Group {
	int visitors, money, id;
} g[MAXM];

struct Table {
	int cap, id;
} t[MAXM];

bool cmp_group(const Group & a, const Group & b) {
	return a.money > b.money;
}
bool cmp_table(const Table & a, const Table & b) {
	return a.cap < b.cap;
}

int n, K;
vector<Table> table;

int exist_table(int need)
{
	int l = 0, r = table.size() - 1, ans = -1;
	while(l <= r) {
		int mid = ((l + r) >> 1);
		if(table[mid].cap >= need) {
			r = mid - 1, ans = mid;
		} else l = mid + 1;
	}
	if(ans != -1) {
		int res = table[ans].id;
		table.erase( table.begin() + ans );
		return res;
	}
	return -1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &g[i].visitors, &g[i].money), g[i].id = i;
	}
	scanf("%d", &K);
	for(int i = 1; i <= K; i++) {
		scanf("%d", &t[i].cap), t[i].id = i;
	}

	sort(g+1, g+1+n, cmp_group);
	sort(t+1, t+1+K, cmp_table);
	for(int i = 1; i <= K; i++) table.push_back(t[i]);

	int ans_group = 0, ans_money = 0, res;
	vector<pair<int,int> > ans_vector;
	for(int i = 1; i <= n; i++) {
		if((res = exist_table(g[i].visitors)) != -1) {
			ans_group++, ans_money += g[i].money;
			ans_vector.push_back( pair<int,int>(g[i].id, res) );
		}
	}
	printf("%d %d\n", ans_group, ans_money);
	for(vector<pair<int,int> > :: iterator it = ans_vector.begin(); it != ans_vector.end(); it++) 
		printf("%d %d\n", it->first, it->second);
	return 0;
}
