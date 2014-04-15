#include <string.h>
#include <iostream>
using namespace std;

int main()
{
    int n, start, end, l, r ;
    string s;

    cin >> n;
    cin >> s;

    r = s.find('R');
    l = s.find('L');

    if(r != -1 && l != -1) {
        start = r + 1;
        end   = l;
    } else if(l == -1) {
        start = r + 1;
        end   = s.find_last_of('R') + 2;
    } else {
        start = s.find_last_of('L') + 1;
        end   = l ;
    }
    cout << start << " "<< end << endl;
    return 0;
}
