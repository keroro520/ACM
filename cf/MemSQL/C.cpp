/*
    理解错题意了，这道题对“最大值无限”的定义太恶心了！！！！
    我对“最大值无限”的定义：能无限扩展就是无限。
    他对“最大值无限”的定义：有终结的方式的话就终结，实在不能终结的话才无限。
    下面两组数据:
    (1)
    3 2
    1 2 1 -1
    2 2 -1 -1
    2 3 2 1 -1
    答案：-1 -1
          2  2
    (2)
    1 2 1 -1
    2 2 -1 -1
    2 2 2 -1
    答案：-1 -1 
          2  -2

    不说了，累了...懒得改了...


    再根据自己的理解改了一下，还是跟题目的题意不一样。。。妹的
*/
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
#define     MAXN    100005
#define     debug   printf("!\n")
const int   CONST     =   314000000;
struct Rule {
    int diamond;
    vector<int> ref;
};
Rule rule[MAXN];
vector<int>  R[MAXN];
bool visit[MAXN];
int Max[MAXN], Min[MAXN];
int n;

bool Get_max(int u)
{
    if(Max[u] == -2) return false;
    if(Max[u] != -1) return true;
    if(visit[u]) {
        Max[u] = -2;
        return false;
    }
    visit[u] = true;
    bool flag = false;
    int  mm   = 0;
    for(int Size = R[u].size(), i = 0; i < Size; i++) {
        int     r       =   R[u][i];
        int     tmp     =   rule[r].diamond;
        for(int Size2 = rule[r].ref.size(), j = 0; j < Size2; j++) {
            if(!Get_max(rule[r].ref[j])) {
                tmp  = -2;
                break;
            } else {
                tmp += Max[rule[r].ref[j]];
                if(tmp >= CONST) tmp = CONST;
            }
        }
        if(tmp != -2) flag = true, mm = max(mm, tmp); //, Max[u] = max(Max[u], tmp);
    }
    if(flag == false) Max[u] = -2;
    else Max[u] = mm;
    return flag;
}

int min(int x, int y) {
    if(x == -1) return y;
    return x < y ? x : y;
}
bool Get_min(int u)
{
    if(Min[u] == -2) return false;
    if(Min[u] != -1) return true;
    if(visit[u]) return false;
    visit[u] = true;
    for(int Size = R[u].size(), i = 0; i < Size; i++) {
        bool    flag  = true;
        int     r     = R[u][i];
        int     sum   = rule[r].diamond;
        for(int Size2 = rule[r].ref.size(), j = 0; j < Size2; j++) {
            if(Get_min(rule[r].ref[j])) {
                sum += Min[rule[r].ref[j]];
                if(sum >= CONST) sum = CONST;
            } else {
                flag = false;
                break;
            }
        }
        if(flag) Min[u] = min(Min[u], sum);
    }
    if(Min[u] == -1) {
        Min[u] = -2;
        return false;
    } else return true;
}
int main()
{
    int m, x, l, y;
    scanf("%d%d", &m, &n);
    memset(Min, -1, sizeof(Min));
    memset(Max, -1, sizeof(Max));
    while(m--) {
        scanf("%d%d", &x, &l);
        //rule[m].belong = x;
        R[x].push_back(m);
        while(l--) {
            scanf("%d", &y);
            if(y == -1) rule[m].diamond++;
            else rule[m].ref.push_back(y);
        }
        if(rule[m].ref.size() == 0) Min[x] = rule[m].diamond;       // 找最小值树的叶子节点
    }
    for(int i = 1; i <= n; i++) {       //找最大值树的叶子节点
        bool flag = true;
        int tmp = 0;
        for(int Size = R[i].size(), j = 0 && flag; j < Size; j++) 
            if(!rule[R[i][j]].ref.empty()) flag = false;
            else tmp = max(tmp, rule[R[i][j]].diamond);
        if(flag) Max[i] = tmp;
    }
    memset(visit, false, sizeof(visit));
    for(int i = 1; i <= n; i++) if(Min[i] == -1) Get_min(i);
    memset(visit, false, sizeof(visit));
    for(int i = 1; i <= n; i++) if(Max[i] == -1) Get_max(i);
    for(int i = 1; i <= n; i++) 
        if(Min[i] == -2) printf("-1 -1\n");
        else printf("%d %d\n", Min[i], Max[i] == -2 ? -2 : Max[i]);
    return 0;
}
