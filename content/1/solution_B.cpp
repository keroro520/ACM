/*
    栈的性质就是先进后出，所以对于依次入栈的两个元素a,b，有两种情况：
        <1>先压a进栈，不弹出，再压b进栈，则最终的出栈序列a一定位于b之后。
        <2>要想a位于b之前，则只能在b进栈之前把a弹出。

    所以求字典序最大的出栈序列，就可以根据这一性质来搞。。设rmax[i] 为区间[i, n]中最大元素，而max_pos则记录该元素的位置。
    <1>初始l=1
    <2>若栈为空，则直接压入当前元素
       若栈顶元素S.top() 比区间[l, n]的最大元素rmax[l]值小，则应该把当前元素到max_pos[l]的这段全都压入栈(即区间[i, max_pos[l]])，然后pop出此时的栈顶元素，其实也就是rmax[l].  接着新的l = max_pos[l] + 1.
       若S.top() > rmax[l]，则栈顶元素出栈，l不变。
    <3>重复<2>

*/
#include <stdio.h>
#include<iostream>
#include<stack>
using namespace std;

const int N = 128;

stack<int> stk;
int n, a[N], rmax[N], max_pos[N];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", a+i);
    for(int i = n-1; i >= 0; --i)
        if(rmax[i+1] > a[i]) rmax[i] = rmax[i+1], max_pos[i] = max_pos[i+1];
        else  rmax[i] = a[i], max_pos[i] = i;
    for(int j = 0, i = 0; i < n; ++i) {
        if(stk.empty() || stk.top()<rmax[j])
            for(int k = max_pos[j]; j <= k; ++j) stk.push(a[j]);
        printf("%d%c", stk.top(), i<n-1?' ':'\n'), stk.pop();
    }
    return 0;
}
