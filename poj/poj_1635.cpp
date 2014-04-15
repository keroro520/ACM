/*
	树的同构   树的最小表示法
	题意：判断两棵树是否同构。输入给出的是dfs的方向，0表下去，1表上来。

	思路：比较树的最小表示即可。

		  树的最小表示跟串的最小表示在做法上其实没什么关系。。。
		  树的最小表示：将每棵子树用0/1串表示，然后按字典序把他们串起来，最终根的连接串如果一样，则同构。
		  byvoid有向树与树的括号序列最小表示法：https://www.byvoid.com/blog/directed-tree-bracket-sequence
*/
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

string min_Presentation(string s)
{
	vector<string> v;
	int sum = 0, len = s.length(), st = 0;
	for(int i = 0; i < len; i++) {
		if(s[i] == '0') sum++;
		else sum--;
		if(sum == 0) {
			if(i-1 == st+1) v.push_back("01");			//叶子节点
			else v.push_back("0" + min_Presentation(s.substr(st+1, i-st-1)) + "1");		//记住把首尾提取出来 
			st = i + 1;
		}
	}
	sort(v.begin(), v.end());
	string res = "";
	for(int Size = v.size(), i = 0; i < Size; i++) res += v[i];		//按字典序串起来
	return res;
}
int main()
{
	int cases;
	string s1, s2;
	cin >> cases;
	while(cases--) {
		cin >> s1 >> s2;
		cout <<  (min_Presentation(s1) == min_Presentation(s2) ? "same" : "different") << endl;
	}
	return 0;
}
