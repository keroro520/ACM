/*
    构造题
    题意：给出n，m，要求找到一个最大点集，使得该点集里的点都是整数点，且两两距离
          都是非整数
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    int x = min(n, m), y = 0;
    int tot = min(n, m) + 1;
    printf("%d\n", tot);

    while(tot) {
        printf("%d %d\n", x, y);
        x--, y++;
        tot--;
    }
    return 0;
}