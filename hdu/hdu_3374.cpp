/*
	最小表示法  KMP应用  KMP的周期问题   KMP求字符串的循环节  好题
	
	题意：求串的最小/最大表示，并输出最大/最小表示串的同构串个数

	思路：最小表示简单，学到的是KMP的next原来还可以用来求循环节...
			int len = s.length();
			int rep = len - next[len];
			int times = (len%rep == 0 ? len/rep : 1);

		  KMP求循环节：http://blog.sina.com.cn/s/blog_7981299401012xl0.html
*/
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
#define			MAXN		1000005
int next[MAXN];
int  max_Presentation(string &s)
{
	int i = 0, j = 1, k = 0, len = s.length();
	while(i < len && j < len && k < len) {
		int res = s[(j+k)%len] - s[(i+k)%len] ;
		if(!res) k++;
		else {
			if(res > 0) i = i + k + 1;
			else j = j + k + 1;
			if(i ==  j) j++;
			k = 0;
		}
	}
	return min(i,j);
}
int  min_Presentation(string &s)
{
	int i = 0, j = 1, k = 0, len = s.length();
	while(i < len && j < len && k < len) {
		int res = s[(i+k)%len] - s[(j+k)%len];
		if(!res) k++;
		else {
			if(res > 0) i = i + k + 1;
			else j = j + k + 1;
			if(i == j) j++;
			k = 0;
		}
	}
	return min(i,j);
}
void fail(string &s)
{
	int len = s.length();
	int i = 0, j = -1;
	next[0] = -1;
	while(i < len) {
		if(j == -1 || s[i] == s[j]) {
			i++, j++;
			next[i] = j;
		} else j = next[j];
	}
}
int main()
{
	string s;
	while(cin >> s) {
		fail(s);
		int len = s.length();
		int rep = len - next[len];
		int times = (len%rep == 0 ? len/rep : 1);
		cout << min_Presentation(s) + 1 << " " << times << " " << max_Presentation(s) + 1 << " " << times << endl;
	}
	return 0;
}
