#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 21;
int a[1 << N];

int main() {
  freopen("1_out.txt","w",stdout);
	a[0] = 0;
	for (int i=0; i<N; i++) {
		int t = 1 << i;
		for (int j=t-1; j>=0; j--) {
			a[t+j] = a[t-1-j] | t;
		}
	}
	int n, m;
	scanf("%d%d", &n, &m);
		for (int i=0; i<(1<<n); i++) {
			for (int j=0; j<(1<<m); j++) {
				printf("%d%c", (a[i] << m) | (a[j]), (j+1 == (1<<m)) ? '\n' : ' ');
			}
		}

	return 0;
}
