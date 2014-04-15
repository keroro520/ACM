/*
	概率论  实现题
	题意：给出n*n的n个人相互比赛的胜率，来log(n, 2)场淘汰赛，问最后i夺冠的概率。

	思路：感觉就是靠实现的=_=
		  我是对于每一轮，计算每个人能在该轮出线的概率，则夺冠概率就是在第4轮出线的概率，初始概率都为1

		  然后就说实现吧，我用set来搞，每一轮结束我都合并一次set
		  某轮比赛set[i]只和set[i+1](奇)或set[i-1](偶)有关

		  个人感觉实现还是比较漂亮的~~
*/
#include <set>
#include <stdio.h>
using namespace std;

const int n = 16;
char  name[n+1][1000];
double p[n+1][n+1], f[10][n+1];
set<int> Set[n+1];
int main()
{
	for(int i = 1; i <= n; i++) scanf("%s", name[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%lf", &p[i][j]), p[i][j] *= 0.01;
	for(int i = 1; i <= n; i++) Set[i].insert(i);
	
	for(int i = 1; i <= n; i++) f[0][i] = 1;
	int top = 16;

	for(int step = 1; step <= 4; step++) {
		for(int i = 1; i <= top; i++) {
			int j = (i & 1) ? i + 1 : i - 1;		//i,j两个set里的人物PK
			for(set<int> :: iterator u = Set[i].begin(); u != Set[i].end(); u++) {
				double sum = 0;
				for(set<int> :: iterator v = Set[j].begin(); v != Set[j].end(); v++) {
					sum += f[step-1][*v] * p[*u][*v];
				}
				f[step][*u] = f[step-1][*u] * sum;
			}
		}
		for(int i = 1; i <= top; i ++) {		//合并set，有个if是因为有i=1时
			if((i-1)/2+1 != i) Set[(i-1)/2+1].insert(Set[i].begin(), Set[i].end()), Set[i].clear();
		}
		top /= 2;								//合并之后set个数少一半
	}
	for(int i = 1; i <= n; i++) printf("%-10s p=%.2f\%\n", name[i], f[4][i]*100);
	return 0;
}
