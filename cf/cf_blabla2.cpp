/*
    ������
    ���⣺����n��m��Ҫ���ҵ�һ�����㼯��ʹ�øõ㼯��ĵ㶼�������㣬����������
          ���Ƿ�����
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