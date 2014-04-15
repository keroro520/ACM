/*
    详情看C.cpp


    如果线段树只是加/减的话, 且只查询一次的话, 是可以用特殊方法的. 如下面的代码
    C.cpp是用了两次线段树, 这里则用了特殊方法.
*/
#include <stdio.h>
#include <iostream>
using namespace std;

#define N       100003

struct Operation { int start, end ; long long value; };
struct Tree { 
    int left, right;
    long long value; 
};
Operation op[N];
long long a[N], b[N], c[N];

int main()
{
    int n, m, k, x, y;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= m; i++) 
        cin >> op[i].start >> op[i].end >> op[i].value;

    while(k--) {
        scanf("%d%d", &x, &y);
        b[x]++;
        b[y+1]--;
    }
    for(int i = 2; i <= m; i++) b[i] += b[i-1];
    //for(int i = 1; i <= m; i++) {
      //  cout << i << "\t" << action[b[i]].value << endl;
//    }
    for(int i = 1; i <= m; i++) {
        c[op[i].start] += b[i]*op[i].value;
        c[op[i].end+1]   -= b[i]*op[i].value;
    }
    for(int i = 2; i <= n; i++) c[i] += c[i-1];
        
    for(int i = 1; i <= n; i++) cout << a[i]+c[i] << "\t";
    cout << endl;
    return 0;
}
