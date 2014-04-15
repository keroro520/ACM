#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

bool check(string s1, string s2){ return s1 == s2; }
int main()
{
    int n, flag;
    string s;
    cin >> n;
    getline(cin, s);
    while(n--) {
        getline(cin,s);
        //cout << s << endl;
        if(check(s.substr(0, 5), "miao.") && check(s.substr(s.length()-5, 5), "lala.")) 
            flag = 2;
        else if(check(s.substr(0, 5), "miao."))
            flag = 0;
        else if(check(s.substr(s.length()-5, 5), "lala."))
            flag = 1;
        else flag = 2;

        if(flag == 1) printf("Freda's\n");
        else if(flag == 0) printf("Rainbow's\n");
        else printf("OMG>.< I don't know!\n");
    }
    return 0;
}
