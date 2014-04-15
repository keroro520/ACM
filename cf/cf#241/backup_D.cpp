/*
	贪心策略 ： 对于当前的ai (ai>0) ，让它尽量属于前面的等差数列。  下一步就是把 -1 归到已知的由正整数
				构成的等差数列里，归不了的就ans++

				但这样的贪心遇到下面的数据就跪了：
				-1  1  5  -1  7
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define		MAXN		200005
#define		NA			(1000000000+9)
#define		NAM			200001
struct Prog {
	int begin, end, d;
	int tmp;
	Prog(int t) { tmp = t; }
	Prog(int b, int e, int _d) {
		tmp = 0;
		begin = b, end = e, d = _d;
	}
};
vector<Prog> result;
int a[MAXN];
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]); a[0] = 0;
	int tmp = 0, j = 1;
	for(int i = 1; i <= n; i++) 
		if(a[i] == -1) tmp += -1;
		else if(tmp < 0) a[j++] = tmp, tmp = 0, a[j++] = a[i];
		else a[j++] = a[i];
	if(tmp < 0) a[j++] = tmp;
	n = j - 1;

	int d = NA, pre = NA, begin;
	tmp = 0;
	if(a[1] < 0) result.push_back( Prog(a[1]) );
	for(int i = (a[1] > 0 ? 1 : 2); i <= n; i++) {
		if(	a[i] < 0 ) tmp = a[i];
		else if(pre == NA) begin = pre = a[i], d = NA, tmp = 0;
		else {
			if(d == NA) {
				if((a[i]-pre) % (abs(tmp)+1) == 0) {
					d = (a[i]-pre) / (abs(tmp)+1);
					pre = a[i];
					tmp = 0;
				} else {
					result.push_back( Prog(begin, pre, NA) );
					if(tmp)result.push_back( Prog(tmp) );
					begin = pre = a[i], d = NA;
					tmp = 0;
				}
			} else {
				if(pre + d*(1+abs(tmp)) == a[i]) {
					pre = a[i];
					tmp = 0;
				} else {
					result.push_back( Prog(begin, pre, d) );
					if(tmp)result.push_back( Prog(tmp) );
					begin = pre = a[i], d = NA;
					tmp = 0;
				}
			}
		}
	}
	result.push_back( Prog(begin, pre, d) );
	if(a[n] < 0) result.push_back(a[n]);
	//for(vector<Prog> :: iterator it = result.begin(); it != result.end(); it++) {
	//	if(it->tmp) printf("%d\n", it->tmp);
	//	else printf("%d\t%d\t%d\n", it->begin, it->end, it->d);
	//}


	int ans = 0;
	for(int i = 0; i < result.size(); i++) if(result[i].tmp == 0) ans++;
	for(int i = 0; i < result.size(); i++) {
		if(result[i].tmp) {
			tmp = -result[i].tmp;
			if(i != 0) {
				pre = result[i-1].end, d = result[i-1].d;
				tmp = tmp - ((d >= 0 || d == NA)? NAM : (pre - 1) / (-d));
			}
			if(tmp <= 0) continue;
			if(i < result.size() - 1) {
				pre = result[i+1].begin, d = result[i+1].d;
				tmp = tmp - ((d <= 0 || d == NA)? NAM : (pre - 1) / d);
			}
			if(tmp > 0) ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
