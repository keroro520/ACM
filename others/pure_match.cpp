#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
vector<string> content;
int top = 0;

bool pure_match(string s1, string s2, int lineIndex)
{
    bool flag = false;
    int len1 = s1.length();
    int len2 = s2.length();
    int i = 0, j = 0;
    while(true) {
        do {
            if(s1[i] == s2[j]) {
                i++, j++;
            } else {
                i = i - j + 2;
                j = 0;
            }
        } while(i < len1 && j < len2);
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
        if(s == "quit") return;
        for(vector<string> :: iterator it = content.begin(); it != content.end(); it++) {
            flag = flag | pure_match(*it, s, 1 + (it - content.begin()));
        }
        if(!flag) cout << "Not found \"" << s << "\""<< endl;
    }
}

int main()
{
    string s;
    ifstream ifs ("in.txt", ifstream :: in);
    while(getline(ifs, s)) content.push_back(s);
    shell();
    return 0;
}

