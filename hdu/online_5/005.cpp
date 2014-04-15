#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#define		MAXN		1000005
int PMT[MAXN];
string s;
//PMT[] : 部分匹配值 
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
	//for(int i = 0; i < len; i++) printf("%d ", PMT[i]);
	//puts("");
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		cin >> s;
		fail(s);
		int len = s.length();
	    int maxn=0;
		int i=1;
		int M=PMT[len-1];
		while(i<len)
		{
			if(s[i] == s[len-1]) maxn = max(maxn,   min(len-1-i, min(PMT[len-1], min((i+1)/2, PMT[i]))));
		    //int tmp=PMT[i];
			//if(tmp>maxn && tmp <=M)
			//{
			// int start_mid=i-tmp+1;
			// int start_end=len-1-tmp+1;
			// int first_end=tmp-1;
			// if(first_end < start_mid && i < start_end)
			// maxn=tmp;
			// else
			// {
			//   int M_first=(i+1)/2;
			//   if(M_first>maxn && M_first <=M)
			//   maxn=M_first;
			//   int tt=
			//   if()

			// }
			//}
			i++;
		}
		printf("%d\n", maxn);
	}
	return 0;
}
