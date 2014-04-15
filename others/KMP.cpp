/*
阮一峰版本（我觉得更加正统 http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html）：　　
			移动位数 = 已匹配的字符数 - 对应的部分匹配值
			《部分匹配表》（Partial Match Table）

void fail(string s)
{
    int len = s.length();
    int j = 0;
    PMT[0] = 0;
	for(int i = 1; i < len; i++) {
        while(j > 0 && s[i] != s[j]) {
            j = PMT[j-1];
        }
		if(s[i] == s[j]) j ++;
        PMT[i] = j;
    }
}
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
vector<string> content;
int next[100005];

void fail(string s)
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
bool KMP(string s1, string s2, int lineIndex)
{
    bool flag = false;
    int len1 = s1.length();
    int len2 = s2.length();
    fail(s2);
    int i = 0, j = 0;

    while(true) {
        while(i < len1 && j < len2) {
            if(j == -1 || s1[i] == s2[j]) {
                i++, j++;
            } else j = next[j];
        }

        if(j == len2) {
            cout << lineIndex << "\t" << i - j + 1 << endl;
            j = 0;
            i = i - len2 + 1;
            flag = true;
        } else return flag;
    }
}

void shell()
{
    string s;
    while(true) {
        bool flag = false;
        getline(cin, s);
        if(s == "quit") return ;
        for(vector<string> :: iterator it = content.begin(); it != content.end(); it++) {
            flag = flag | KMP(*it, s, 1 + (it - content.begin()));
        }
        if(!flag) cout << "Not found \"" << s << "\""<< endl;
    }
}
int main()
{
    string s;
//    ifstream ifs ("in.txt", ifstream :: in);
//    while(getline(ifs, s)) content.push_back(s); 
//    shell();
    cin >> s;
    fail(s);
	for(int i = 0; i < s.length(); i++) printf("%2c%c", s[i], i == s.length()-1 ? '\n' : ' ');
	for(int i = 0; i < s.length(); i++) printf("%2d%c", next[i], i == s.length()-1? '\n' : ' ');
//    for(int i = 0; i < s.length(); i++) printf("%c\t", s[i]);
    printf("\n");
//    for(int i = 0; i < s.length(); i++) printf("%d\t", next[i]);
    printf("\n");
    return 0;
}
