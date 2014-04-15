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
	int cases = 1;
	while(cases--) {
		work();
	}
}
int work()
{
    srand((unsigned)time(NULL));

    int n = rand() % MAXN + 1;
	int q = rand() % MAXQ + 1;
	int S = rand() % n + 1;
	printf("%d\n", n);
	gen_tree(n);
	for(int i = 1; i <= n; i++) printf("%d ", rand() % 13);
	printf("%d\n", q);
	while(q--) {
		int op = rand() % 3;
		if(op == 0) printf("QMAX %d %d\n", rand() % n + 1, rand() % n + 1);
		else if(op == 1) printf("QSUM %d %d\n", rand() % n + 1, rand() % n + 1);
		else {
			int e = rand() % (n - 1) + 1;
			int w = (rand() % 13);
			printf("CHANGE %d %d\n", e, w);
		}
	}
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
		printf("%d  %d\n", already[v], wait[u]);
		already.push_back(wait[u]);
		wait.erase(wait.begin() + u);
	}
}
