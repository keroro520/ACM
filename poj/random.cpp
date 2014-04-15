#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
#define     MAXN    20
#define     MAXM    20
#define     MAXQ    10
#define MAX 9223372036854775807
void gen_tree(int n);
int work();
int main()
{
	int cases = 20;
	while(cases--) {
		work();
	}
}
int work()
{
    srand((unsigned)time(NULL));

    int n = rand() % MAXN + 1;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d\n", rand() % 100);
    return 0;
}
void gen_tree(int n)
{
	vector<int> already, wait;
	already.push_back(1);
	for(int i = 2; i <=n; i++) wait.push_back(i);
	
	for(int i = 1; i < n; i++) {
		int u = rand() % wait.size();
		int v = rand() % already.size();
		printf("%d  %d %d\n", already[v], wait[u], rand() % 13+1);
		already.push_back(wait[u]);
		wait.erase(wait.begin() + u);
	}
}
