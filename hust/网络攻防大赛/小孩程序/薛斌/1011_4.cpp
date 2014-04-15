#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 2010;
int l[N], r[N], n;

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i=0; i<n; i++) {
			scanf("%d%d", l+i, r+i);
		}
		int ans = 0;
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (l[j] < l[i] && r[i] < r[j]) {
					ans ++;
					break;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
