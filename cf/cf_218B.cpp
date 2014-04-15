/*
  简单题
  用堆来维护一下就可以了
*/
#include <queue>
#include <stdio.h>
#include <vector>
#include <functional>
using namespace std;
priority_queue<int, vector<int>, less<int> >    heap_max;
priority_queue<int, vector<int>, greater<int> > heap_min;
int main()
{
  int m, x, n;
  scanf("%d%d", &n, &m);
  while(m--) {
    scanf("%d", &x);
    heap_max.push(x); heap_min.push(x);
  }
  int sum_max = 0, sum_min = 0;
  while(n--) {
    x = heap_max.top(); heap_max.pop();
    sum_max += x;
    if(--x) heap_max.push(x);
    x = heap_min.top(); heap_min.pop();
    sum_min += x;
    if(--x) heap_min.push(x);
  }
  printf("%d %d\n", sum_max, sum_min);
  return 0;
}
