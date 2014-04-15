/*
	简单题
*/
#include <map>
#include <string.h>
#include <stdio.h>
using namespace std;
map<int,int> M;
char str[10];
int n, m, a[5005];

int  hash(char ch)
{
	switch (ch) {
		case 'a' : case 'b' : case 'c' : return 2;
		case 'd' : case 'e' : case 'f' : return 3;
		case 'g' : case 'h' : case 'i' : return 4;
		case 'j' : case 'k' : case 'l' : return 5;
		case 'm' : case 'n' : case 'o' : return 6;
		case 'p' : case 'q' : case 'r' : case 's' : return 7;
		case 't' : case 'u' : case 'v' : return 8;
		case 'w' : case 'x' : case 'y' : case 'z' : return 9;
	}
}
int main()
{
    int cases, x;
    scanf("%d", &cases);
    while(cases--) {
        M.clear();
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++) scanf("%d", &x), M[x] = 1, a[i] = x;
        for(int i = 0; i < m; i++) {
            scanf("%s", str);
            int sum = 0, len = strlen(str);
            if(len > 6) continue;
            for(int i = 0; i < len; i++) sum = sum * 10 + hash(str[i]);
            if( M.find(sum) != M.end() ) M[sum]++;
        }
        for(int i = 0; i < n; i++) printf("%d\n", M[ a[i] ] - 1);
    }
    return 0;
}
