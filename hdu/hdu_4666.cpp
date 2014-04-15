/*
	堆 优先队列 set 数据结构 曼哈顿距离
	距离：最远曼哈顿距离

	思路：学会了处理最远曼哈顿和multiset的用法。武森的《浅谈信息学竞赛中的“0”和“1”》

		  set/multiset是用二叉树来维护的，priority_queue是用heap来维护的。
		  两者的区别这里讲得挺好：http://stackoverflow.com/questions/10141841/difference-between-stdset-and-stdpriority-queue

	实现：这步的实现代码还是挺好看的:
			for(int i = 0; i < k; i++) 
				if(j & (1 << i)) sum += x[i];
				else sum -= x[i];
*/
#include <string.h>
#include <stdio.h>
#include <set>
using namespace std;
#define		MAXN	(1 << 6)
multiset<int> S[MAXN];
int status[60005][MAXN], x[MAXN];
inline		int		rdi() { int x; scanf("%d", &x); return x; }
void init()
{
	memset(status, 128, sizeof(status));		//为了防止op = 1时删错之前case的东西，把status初始化一下
	for(int i = 0; i < (1 << 6); i++) S[i].clear();
}
int main()
{
	int query, k;
	while(scanf("%d%d", &query, &k) != EOF) {
		int K = (1 << k);			//k维度，K状态数=2*k
		init();
		for(int no_ = 1; no_ <= query; no_++) {
			if(rdi() == 0) {
				for(int i = 0; i < k; i++) scanf("%d", &x[i]);
				for(int j = 0; j < K; j++) {		//第j种状态
					int sum = 0;
					for(int i = 0; i < k; i++) 
						if(j & (1 << i)) sum += x[i];		//TODO  这个实现不错哟~
						else sum -= x[i];
					status[no_][j] = sum;
					S[j].insert(sum);
				}
			} else {
				int u = rdi();
				for(int j = 0; j < K; j++) {
					multiset<int> :: iterator it;
					it = S[j].find(status[u][j]);
					if(it != S[j].end()) S[j].erase(it);
				}
			}

			int ans = 0;
			for(int j = 0; j < K; j++) if(S[j].size()) ans = max(ans, *(--S[j].end()) - *(S[j].begin()));
			printf("%d\n", ans);
		}
	}
	return 0;
}
