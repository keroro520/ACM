/*
	二维格雷码（循环码）

	格雷码有一个公式：G(x) = x XOR (x>>1)
	其实就是对于2^n * 2^m矩阵，每个数的前n位负责行上满足格雷码性质，后m位负责列上满足格雷码性质，这样一来，一个二维上的格雷码就分成两个不互相影响的两部分了。对于gray[i][j]，我们先算出该行的前n位togray(i)，再算出该列的后m位togray(j)...
	直接看代码吧...
	http://blog.csdn.net/beiyeqingteng/article/details/7044471
*/
//sgu 249
#include <stdio.h>
inline int togray(int i)
{
	return (i >> 1) ^ i;
}
int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF) {
		int r = (1 << n), c = (1 << m);
		for(int i = 0; i < r; i++) {
			int ans = togray(i);
			for(int j = 0; j < c; j++) printf("%d%c", (ans << m) | togray(j), j == c-1 ? '\n' : ' ');
		}
	}
	return 0;
}
