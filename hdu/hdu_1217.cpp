/*
    最短路 

    以前对图论的理解只停留在“路径模型”上，这道题让我觉得，所谓的最短路，其实就是最优化问题。
    问s-->s能够到达的利率能否大于1,其实就是问利率最优化问题。。路径 = 利率~

    题意：若干种货币及其之前的转换利率，问有没有可能经过若干次货币转换取得利益？


    思路：可以floyd，这里用的是SPFA，每个点都来一次SPFA，如果dis[s] > 1.0则return true;
          最优路径 = 最大利率

    尝试了一下SLF优化，可是貌似数据太小，没体现出来
*/
#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <string.h>
using namespace std;
#define     INF     999999.9999
#define     MAXN    50
#define     debug   printf("!\n")
double dis[MAXN];
bool visit[MAXN];
int  times[MAXN];
map < string, int > m;
vector<int> v[MAXN], rv[MAXN];
vector<double> e[MAXN], re[MAXN];
deque<int> Q;
int n, Index;

bool relax(int i, int j, double tax)
{
    if(dis[i] * tax > dis[j]) {
        dis[j] = dis[i] * tax;
        return true;
    }
    return false;
}
void SPFA(int s)
{
    for(int i = 0; i < Index; i++) dis[i] = -INF;
    memset(visit, false, sizeof(bool)*(Index+1));
    memset(times, 0, sizeof(int) * (Index+1));
    dis[s] = 1;
    visit[s] = true;
    Q.push_back(s);
    while(!Q.empty()) {
        int now = Q.front();
        Q.pop_front();
        visit[now] = false;
        for(int Size = v[now].size(), i = 0; i < Size; i++) {
            int tmp = v[now][i];
            if(relax(now, tmp, e[now][i])) {
                if(!visit[tmp]) {
                    visit[tmp] = true;
                    if(++times[tmp] > Index) return ;
                    if(dis[s] > 1.0) return ;
                    
                    if(!Q.empty()) {
                        if(dis[Q.front()] <= dis[tmp])
                            Q.push_front(tmp);
                        else Q.push_back(tmp);
                    }
                    else Q.push_back(tmp);
                }
            }
        }
    }
}
bool solve(int s)
{
    SPFA(s);
    return dis[s] > 1.0;
}
void init()
{
    Q.clear();
    for(int i = 0; i < Index; i++) {
        rv[i].clear();
        re[i].clear();
        e[i].clear();
        v[i].clear();
    }
    Index = 0;
    m.clear();
}
int main()
{
    int cases = 0;
    int M, x, y;
    double z;
    string xs, ys;
    
    while(cin >> n, n) {
        init();
        for(int i = 0; i < n; i++) {
            cin >> xs;
            m[xs] = Index++;
        }
        cin >> M;
        while(M--) {
            cin >> xs >> z >> ys;
            x = m[xs];
            y = m[ys];
            v[x].push_back(y);
            e[x].push_back(z);
            rv[y].push_back(x);
            re[y].push_back(z);
        }
        bool flag = false;
        for(int i = 0; i < Index; i++) 
            if(solve(i)) {
                flag = true;
                break;
            }
        cout << "Case " << ++cases << ": " << (flag ? "Yes" : "No") << endl;
    }
    return 0;
}
/*
    http://acm.hdu.edu.cn/showproblem.php?pid=1217
*/
