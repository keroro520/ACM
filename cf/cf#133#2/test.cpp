/*
    贪心 + 模拟

    我没AC.
*/
#include <vector>
#include <stdio.h>
using namespace std;
int n, m, k;
vector<int> ans;

void work()
{
    for(int i = 0; i < k; i++)
        ans.push_back(1);

    ans.push_back(n);

    if(k == 1) {
        if(n-1 <= m) ans.push_back(n+m-1);
        return ;
    }

    for(int i = 1; i < k; i++) ans.push_back(n+1);

    if(m == n) ans.push_back(m+n-1);
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);

    work();
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
