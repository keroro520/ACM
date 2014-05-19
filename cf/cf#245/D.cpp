/*
	最近点对

	点(i, sum[i])

	思考: 刚看完最近点对的做法, 我再好好总结一下.

		  最近点对算法就是分治加上一些优化.
		  优化很好理解, 先排序一下, 再根据单调性搞一下就能优化掉冗余的计算.
		  但为什么会想到分治呢?
		  我认为想到"分治"这一点跟"最近"并没有什么关系, 而是跟"点对"有关系. 这里分治步骤是先排序x, 再分治, 分治过程里是先排序y, 再根据单调性优化冗余, 再合并. 这里就很明显啦, 所谓"分治"只是把点的x部和y部分开而已, 而因为在计算距离上, x坐标和y坐标确实没有什么联系, 所以我们才会想到愉快地分治吧, 能减少冗余哩.

		  于是, 最近点对思想可以用在数据量为10^5级别的, 数据分为几个类型, 且每个类型的计算不相互影响, 如G(x,y,z) = x*x+y*y+z*z, 这类型的题目就可用分治后优化冗余的思想来搞.
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define			MAXN		100005
typedef			long long		ll ;
ll a[MAXN], tmp[MAXN];

bool cmp(const int &x, const int &y)
{
	return a[x] < a[y];
}
ll SQR(ll x) { return x * x; }
ll G(int i, int j)
{
	return SQR(i-j) + SQR(a[i]-a[j]);
}
ll solve(int l, int r)
{
	if (l == r) return 9999999999999999LL;
	if (l + 1 >= r) return G(l,r) ;
	int mid = (l + r) / 2;
	ll ans = min(solve(l, mid), solve(mid+1, r));
	
	int nTmp = 0;
	for (int i = mid; i >= l; i--) if (SQR(mid - i) < ans) tmp[nTmp++] = i; else break;
	for (int i = mid+1; i <= r; i++) if (SQR(i-mid) < ans) tmp[nTmp++] = i; else break;
	sort(tmp, tmp+nTmp, cmp);
	for (int i = 0; i < nTmp; i++)
		for (int j = i+1; j < nTmp; j++) {
			int k1 = tmp[i], k2 = tmp[j];
			if (SQR(a[k1]-a[k2]) > ans) break;
			ans = min(ans, G(k1,k2));
		}
	return ans;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%I64d", &a[i]), a[i] = a[i-1] + a[i];

	printf("%I64d\n", solve(1, n));
	return 0;
}
