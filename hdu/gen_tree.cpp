#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
#define     MAXN    5
#define     MAXM    30
#define     MAXQ    10
#define MAX 9223372036854775807
void gen_tree(int n);
void gen_graph(int n, int m);
int work();
int main()
{
	int cases = 1;
	while(cases--) {
		work();
	}
}
int work()
{
    srand((unsigned)time(NULL));

    int n = rand() % MAXN + 1;
	int m = rand() % MAXM + 1;
	printf("%d %d\n", n,  m);
	//gen_tree(n);
	gen_graph(n, m);
    return 0;
}
void gen_graph(int n, int m)
{
	for(int i = 0; i < m; i++) {
		int u = rand()%n + 1, v = rand()%n+1, w = rand() % 10;
		printf("%d %d %d\n", u ,v , w);
	}
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
