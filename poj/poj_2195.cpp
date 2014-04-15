/*
    二分图带权匹配      最小权匹配

    题意：n*m格子里，若干个小人&&房子，小人必须选一个房子进去，一个房子只能容纳一个小人，问小人们选择各自的房子使得总路程最小.

    思路：二分图最小权匹配，转换为最大权匹配:
          不存在的边取无穷大，存在的边取反。LX[]初始化为无穷小。最后答案取反。


          完备匹配即所有X部或Y部的点都匹配成功，而最优匹配肯定是完备匹配，这道题可以虚拟出一些点使得|X| = |Y|，而因为题目明确了小人的数量小于等于房子数，所以可以直接求小人的完备匹配，不用虚拟点出来，最后因为一定是完备匹配，所以ans求和时候不用判断link[i] != -1.
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <limits.h>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    205
class  Node {
    public : int x, y;
    Node(int x, int y) : x(x), y(y) { }
};
int slack;
int LX[MAXN], LY[MAXN], w[MAXN][MAXN], link[MAXN];
bool visitx[MAXN], visity[MAXN];
vector<Node> people, hours;

bool find(int  u)
{
    visitx[u] = true;       //为了更新角标的时候
    for(int Size = hours.size(), v = 0; v < Size; v++) if(!visity[v]) {
        int rest = LX[u] + LY[v] - w[u][v];
        if(rest == 0) {    
            visity[v] = true;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
        } else slack = min(slack, rest);
    }
    return false;
}
void KM()
{
    memset(link, -1, sizeof(link));
    memset(LX, 128, sizeof(LX));
    memset(LY, 0, sizeof(LY));
    for(int Size1 = people.size(), i = 0; i < Size1; i++)
        for(int Size2 = hours.size(), j = 0; j < Size2; j++)
            LX[i] = max(LX[i], w[i][j]);
    for(int Size = people.size(), i = 0; i < Size; i++) {
        while(true) {
            slack = INT_MAX;
            memset(visitx, false, sizeof(visitx));
            memset(visity, false, sizeof(visity));
            if(find(i)) break;
            for(int Size1 = people.size(), j = 0; j < Size1; j++) if(visitx[j]) LX[j] -= slack;
            for(int Size2 = hours.size(),  j = 0; j < Size2; j++) if(visity[j]) LY[j] += slack;
        }
    }
}
void init()
{
    people.clear();
    hours.clear();
    memset(w, 127, sizeof(w));          // ???
}
int main()
{
    int n, m;
    while(scanf("%d%d", &n, &m) && n+m) {
        init();
        for(int i = 0; i < n; i++) {
            while(getchar() != '\n') ;
            for(int j = 0; j < m; j++) {
                char ch = getchar();
                if(ch == 'm') people.push_back(Node(i, j));
                else if(ch == 'H') hours.push_back(Node(i, j));
            }
        }
        for(int Size1 = people.size(), i = 0; i < Size1; i++)
            for(int Size2 = hours.size(), j = 0; j < Size2; j++)
                w[i][j] = -(abs(people[i].x - hours[j].x) + abs(people[i].y - hours[j].y));

        KM();
        int ans = 0;
        for(int Size = hours.size(), i = 0; i < Size; i++) ans += w[link[i]][i];
        printf("%d\n", -ans);
    }
    return 0;
}
