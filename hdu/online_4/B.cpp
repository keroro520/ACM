#include <stdio.h>
#include <algorithm>
using namespace std;

int T, n, A, B, exp;
int array[100000];
bool less_than(int x, int y) {
	T++;
	return x < y;
}
void output(int l, int r)
{
	printf("%d  %d : ", l, r);
	for(int i = 0; i < n; i++) printf("%d ", array[i]);
	puts("");
}
void work(int array[], int l, int r) {
	if (l >= r) return;
	swap(array[(l * A + r * B) / (A + B)], array[r]);
	output(l,r);
	int index = l;
	puts("---");
	puts("");
	output(l,r);
	for (int i = l; i < r; i++)
		if (less_than(array[i], array[r]))
			swap(array[index++], array[i]), output(i,r);
	puts("");
	puts("");
	output(l,r);
	swap(array[r], array[index]);
	output(l,r);
	work(array, l, index - 1);
	work(array, index + 1, r);
}
int  main() {
	T = 0;
	scanf("%d%d%d%d", &n, &exp, &A, &B);
	for(int i = 0; i < n; i++) scanf("%d", &array[i]);
	output(0,n-1);
	work(array, 0, n - 1);
	if (T == exp) 
		printf("YES");
	else
		printf("NO");
	return 0;
}
