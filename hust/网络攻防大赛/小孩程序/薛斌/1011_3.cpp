#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
namespace suf {
	const int MAXN = 200050;
	const int ASCII = 300;//MAXN>ASCII,否则会出问题，比如访问到b[ASCII]
	int array[4][MAXN], height[MAXN];
	int *sa, *nsa, *rank, *nrank;
	int n, arr[MAXN], b[MAXN];
	void suffix_array()
	{
		sa = array[0];
		nsa = array[1];
		rank = array[2];
		nrank = array[3];
		int i, k;
		memset(b, 0, sizeof(b));
		for(i = 0; i < n; i++)
			b[arr[i]]++;
		for(i = 1; i <= ASCII; i++)
			b[i] += b[i - 1];
		for(i=n-1;i >= 0; i--)
			sa[--b[arr[i]]] = i;
		for(rank[sa[0]] = 0, i = 1; i < n; i++)
		{
			rank[sa[i]] = rank[sa[i - 1]];
			if(arr[sa[i]] != arr[sa[i - 1]])
				rank[sa[i]] ++;
		}
		for(k = 1; k < n && rank[sa[n - 1]] < n - 1; k *= 2)
		{
			for(i = 0; i < n; i++)
				b[rank[sa[i]]] = i;
			for(i = n - 1; i >= 0; i--)
				if(sa[i] - k >= 0)
					nsa[b[rank[sa[i] - k]]--] = sa[i] - k;
			for(i = n - k; i < n; i++)
				nsa[b[rank[i]] --] = i;
			for(nrank[nsa[0]] = 0, i = 1; i < n; i++)
			{
				nrank[nsa[i]] = nrank[nsa[i - 1]];
				if(rank[nsa[i]] != rank[nsa[i - 1]] || rank[nsa[i] + k] != rank[nsa[i - 1] + k])
					nrank[nsa[i]] ++;
			}
			int *t = sa; sa = nsa; nsa = t;
			t = rank; rank = nrank; nrank = t;
		}
	}
	void cal_height()
	{
		int i, j, k;
		for(i = 0, k = 0; i < n; i++)
		{
			if(rank[i] == 0)
				height[rank[i]] = 0;
			else
			{
				for(j = sa[rank[i] - 1]; arr[i + k] == arr[j + k]; k++);
				height[rank[i]] = k;
				if(k > 0) k --;
			}
		}
	}
}
char d[suf::MAXN];
int n, k, m;
int ans[suf::MAXN], res[suf::MAXN];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int cmp(int *a, int *b, int n) {
	for (int i=0; i<n; i++) {
		if (a[i] != b[i]) {
			return a[i] - b[i];
		}
	}
	return 0;
}

void get_ans(int i) {
	int nn = n / m;
	for (int j=0; j<nn; j++) {
		suf::arr[j] = (int)d[int((i+1LL*k*j) % n)];
	}
	suf::n = nn + 1;
	suf::arr[nn] = 0;
	suf::suffix_array();
	int t = suf::sa[nn];
	for (int j=0; j<nn; j++) {
		res[j] = suf::arr[(j+t) % nn] - '0';
	}
	if (cmp(ans, res, nn) < 0) {
		for (int j=0; j<nn; j++) {
			ans[j] = res[j];
		}
	}
}

int main() {
  freopen("in_6.txt","r",stdin);
	while (scanf("%d%d", &n, &k) == 2) {
		k %= n;
		scanf("%s", d);
		fill(ans, ans+n+3, 0);
		m = gcd(n, k);
		for (int i=0; i<m; i++) {
			get_ans(i);
		}
		for (int i=0; i<m; i++) {
			int nn = n / m;
			for (int j=0; j<nn; j++) {
				printf("%d", ans[j]);
			}
		}
		printf("\n");
	}
	return 0;
}
