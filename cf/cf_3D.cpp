/*
	贪心  优先队列  堆  括号序列
	题意：给一个有'(',')','?'的括号序列，要求把'?'替换成括号，使得该括号序列合法。并且每个'?'替换成左括号和右括号有不同花费(ai,bi)。问替换之后的最小总花费
	思路：http://www.gonglin91.com/codeforces-least-cost-bracket-sequence/
		  用计数器法来保证括号序列合法（细节除了上面blog还可以看Bracket Sequence UESTC 1546: http://hi.baidu.com/zyz913614263/item/ed68843a6839ecd2392ffa2b）
		
		  摘：
		  I.如果是一个没有问题的括号串要怎么判断是否是个合法的匹配？一般的方法是用栈，如果中途出现了’)'但是栈中空，那么就失败了。或者所有括号读完了，栈中还有元素，那么也是失败的。其实我们可以只用一个计数器来代替栈，效果完全一样。count计数器，遇到’(‘增1，遇到’)'减1，如果串还没读完count出现了小于0的值，那么和栈的第一种情况是等价的，失败。如果读完了整个串，count不为0（那只会为正数），那么和栈的第二种情况是等价的
		  II.贪心的前提是一定要保证这个问题有解。一开始将所有’?'换成’)'，然后先计算一个花费
		  1.替换完后从左到右读这个串，从上面说的方法去计数
		  2.如果读到’(‘，那么这个’(‘原来一定不是括号，并且count++
		  3.如果读到’)'，count–，但是要判断这个’)'是不是由’?'变来的，如果是的话，将这个元素放入一个堆中，堆中的每个元素要记录两个信息，一个信息就是它来自于串中的那个位置，另一个信息等下再说
		  4.如果count<0，说明出现了无法匹配的情况，但这时候不是退出宣布失败，而是看看能不能补救，之所以会发生不匹配，可能是因为一开始的时候将所有'?'变成了')'导致的，也就是说看看之前是否出现过'?'，如果没有出现过，那么说明这个不匹配是不关'?'的事的，那么只好退出宣告失败了。但是如果之前出现了'?'，那么还可以补救，那么就将前面的'?'换成'(',就可以抵消掉当前这个')'.但是前面可能有多个'?'，要怎么选？贪心就是贪在这里。
		  试想，一开始将所有'?'变为')'并计算了花费 +b，现在把一个')'变回'('，那么花费的变化就是 cost - b + a = cost + (a-b) , 也就是说要让cost越小，让(a-b)越小。所以之前堆记录的另外一个信息就是每个括号的a-b值，每次从推堆中取出一个'?'就是取出a-b值最小的那个元素。
		  取出一个'?'将其从')'变为'('的时候，会对count值产生影响，本来是')'变'('，count += 2
*/
//codeforce 3D  : http://codeforces.com/problemset/problem/3/D
#include <string>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
#define		MAXN	50005
class Node {
	public :
	int a, b, diff, idx;
	Node (int a, int b, int idx) : a(a), b(b), idx(idx) {
		diff = a - b;
	}
	friend bool operator < (const Node & x, const Node & y) {
		return x.diff > y.diff;
	}
} ;
priority_queue<Node> Q;
string s;
int main()
{	
	int a, b, n = 0;
	cin >> s;
	int sum = 0;
	long long ans = 0;
	for(int i = 0; i < s.length(); i++) {
		if(s[i] == '(') sum ++;
		else if(s[i] == ')') {
			sum--;
		} else if(s[i] == '?') {
			sum--;
			cin >> a >> b;
			ans += b;
			Q.push( Node(a, b, i) );
			n++;
		}

		if(sum < 0) {
			if(!Q.empty()) {
				Node tmp = Q.top();
				Q.pop();
				ans += tmp.diff;
				s[tmp.idx] = '(';
			} else {
				cout << -1 << endl;
				return 0;
			}
			sum = 1;
		}
	}
	if(sum > 0) {
		cout << "-1" << endl;
		return 0;
	}
	cout << ans << endl;
	for(int i = 0 ; i < s.length(); i++) if(s[i] == '?') cout << ')'; else cout << s[i];
	cout << endl;
	return 0;
}
