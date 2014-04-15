/*
    top代表in.txt里的字符串个数, content保存.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
string content[100005];
int top = 0;
int next[100005];

void add_content(string s)
{
    content[top++] = s;
}
void get_next(string s)
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
bool KMP(string s1, string s2, int Row)       //要匹配的主串s1 , 搜索串s2，
{
    bool flag = false;
    int len1 = s1.length();
    int len2 = s2.length();
    get_next(s2);
    int i = 0, j = 0;                       //i,j分别指着s1,s2当前正在匹配的下标

    while(true) {
        while(i < len1 && j < len2) {               /* KMP */
            if(j == -1 || s1[i] == s2[j]) {
                i++, j++;
            } else j = next[j];
        }
        //==============
        if(j == len2) {                     //j == len2的话表示匹配成功，则输出(行Row, 列i-j+1);    否则返回flag(表是否至少一次匹配成功)
            cout << Row << "\t" << i - j + 1 << endl;
            j = 0;                          //因为还有下次匹配，所以把j清零，而i就继续~~
            i = i - len2 + 1;
            flag = true;
        } else return flag;
    }
}

void shell()
{
    int i ;
    string s;
    while(true) {               //因为想要shell一直循环，所以设了while(true)，使它只有当我们暴力Ctrl+C时才停
        bool flag = false;
        cout << "输入 : " ;
        getline(cin, s);
        for(i = 0; i < top; i++) {      
            if(KMP(content[i], s, i+1)) flag = true;        //第i+1行和s匹配，如果有过一次成功则flag = true，就不用输出下面的"没.."
        }
        if(!flag) cout << "没找到 \"" << s << "\""<< endl;
    }
}
int main()
{
    string s;
    ifstream ifs ("in.txt", ifstream :: in);        //输入流---可以把in.txt看作ifs了
    while(getline(ifs, s)) add_content(s);          //一行一行地读入in.txt存到content数组里面...getline(输入流, 返回字符串)
    shell();
    return 0;
}


