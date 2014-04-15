/*
	最小表示法
	题意：判断0/1串是否同构

	思路：字符串循环同构的最小表示法
	     
		  在char*的排序这里花了时间，而map对char*哈希是对地址进行判断 ~~所以用不了.
		  qsort(b, n, sizeof(b[0]), cmp);	//size那部分要注意~~是element的size，不是长度length
*/
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <map>
using namespace std;
#define		MAXN	105

map<char*,bool> M;
char a[MAXN], b[10005][MAXN];
int n, m;
int min_Presentation(char *s, int len)
{
	int i = 0, j = 1, k = 0;
	while(i < len && j < len && k < len) {
		int res = s[(i+k)%len] - s[(j+k)%len];
		if(res == 0) k++;
		else {
			if(res > 0) i = i + k + 1;
			else j = j + k + 1;
			if(i == j) j++;
			k = 0;
		}
	}
	return min(i,j);
}
void convert(char * a, int len)
{
	int s = min_Presentation(a, len), idx = 0;
	b[m][idx++] = a[s];
	for(int i = (s+1)%len; i != s; i = (i+1)%len) {
		b[m][idx++] = a[i];
	}
	b[m][idx] = '\0';
	m++;
}
bool equal(char * a, char * b, int len)
{
  	for(int i = 0; i < len; i++) if(a[i] != b[i]) return false;
	return true;
}
int cmp(const void *a, const void *b)
{
	return strcmp((char*)a, (char*)b);
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		m = 0;
		for(int i = 0; i < n; i++) {
			scanf("%s", a);
			convert(a, strlen(a));
		}
		int ans = 1, l = strlen(b[0]);
		qsort(b, n, sizeof(b[0]), cmp);
		for(int i = 1; i < n; i++) if(!equal(b[i], b[i-1], l)) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
