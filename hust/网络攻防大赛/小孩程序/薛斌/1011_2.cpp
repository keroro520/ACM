#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int main() {freopen("ball_in.txt","r",stdin);freopen("ball_out.txt","w",stdout);
	int T; scanf("%d", &T);
	while (T --) {
		int r, g, b;
		scanf("%d%d%d", &r, &g, &b);
		int t = min(r, min(g, b));
		r -= t; g -= t; b -= t;
		int ans = 0;
		if (r > 1 || g > 1 || b > 1) {
			ans = 0;
		} else if (r + g + b == 0) {
			if (t == 0) {
				ans = 1;
			} else {
				ans = 6;
			}
		} else if (r + g + b == 1) {
			if (t == 0) {
				ans = 1;
			} else {
				ans = 2;
			}
		} else {
			ans = 2;
		}
		printf("%d\n", ans);
	}
	return 0;
}
