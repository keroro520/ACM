#include <stdio.h>
#include <vector>
using namespace std;

vector<int> v;
int main()
{
    int cases, m, x;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d" , &m);
        //bool flag = false;
        v.clear();
        for(int i = 0; i < m; i++) {
            scanf("%d", &x);
            if(x != 3 && x != 6) v.push_back(x);
        }
        if(v.empty()) printf("\n");
        else {
            for(int i = 0; i < v.size()-1; i++) printf("%d ", v[i]+1);
            printf("%d\n", v[v.size()-1]+1);
        }
    }
    return 0;
}
