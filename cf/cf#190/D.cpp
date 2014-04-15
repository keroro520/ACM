/*
    贪心      也可以用费用流或DP做

    题意：Ciel有m张牌，每张牌有有一个攻击系数strength
          Jiro有n张牌，每张牌除了有strength外还有个position属性(Attack或Defence)。

          游戏规则如下：<1>Ciel选出一张没有使用过的牌X
                        <2>(a)如果Jiro用完了所有牌，则Jiro遭受X点攻击
                           (b)否则Ciel可从Jiro里选出一张没用过的牌Y，
                             如果选出的牌的position属性为Attack，则必须要X >= Y，则Jiro遭受X - Y点攻击
                             如果选出的牌的position属性为Defence，则必须要X > Y，Jiro不受攻击


          问最多能使Jiro遭受多大的攻击？

    贪心思路：游戏有两种结果：一是Ciel把Jiro的牌都给消灭光了，则可以用到<2>(a)条件，另外一种就是不消灭光。
              第一种情况：先把Jiro的Defence牌用最小代价消灭，再消灭剩下的Attack牌，此时消灭的顺序随便，结果都为sum(Ciel_remain) - sum(Jiro_remain)
              第二种情况：不碰Jiro的defence牌，因为不消灭Jiro所有牌的话，碰Defence牌没任何意义。对于Jiro的Attack牌，采用“用Ciel最大的牌去攻击Jiro最小的牌”的策略。
              为什么这样的策略优于“大攻大，小攻小”策略？假设Ciel有a,b牌，Jiro有c,d牌：
              当a > b > c > d: a-d + b-c = a-c + b-d     两种策略结果一样
              当a > c > b > d: a-d > a-c + b-d = a-d + (b-c)  前种策略优
*/
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
#define     MAXN    105
class Card {
    public : int  num;
             char label;
}a[MAXN], b[MAXN];

int n, m;

bool operator < (const Card & a, const Card & b) {
    return a.num > b.num;
}
int work1()
{
    int p = n-1, q = 0, ans = 0;
    while(p >= 0 && q < m && a[p].num <= b[q].num) {
        if(a[p].label == 'A') ans += b[q].num - a[p].num, p--, q++;
        else p--;
    }
    return ans;
}
int work2()
{
    int p = n-1, q = m-1, ans = 0;
    while(p >= 0) {
        if(a[p].label != 'D') {
            p--;
            continue;
        }
        if(a[p].num >= b[q].num) {
            q--;
            continue;
        }
        b[q].label = 'D';
        p--, q--;
    }
    p = q = 0;
    while(q < m) {
        if(b[q].label != 'D') ans += b[q].num;
        q++;
    }
    while(p < n) {
        if(a[p].label != 'D') ans -= a[p].num;
        p++;
    }
    return ans ;
}
int main()
{
    string s;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> s >> a[i].num;
        a[i].label = s[0];
    }
    for(int i = 0; i < m; i++) cin >> b[i].num;
    sort(a, a+n);
    sort(b, b+m);
    bool flag = true;
    for(int i = 0; i < max(n, m); i++) 
        if(a[i].num > b[i].num || (a[i].label == 'D' && a[i].num == b[i].num)) {
            flag = false; 
            break; 
        }
    if(m < n || flag == false) {
        cout << work1() << endl;
    } else cout << max(work1(), work2()) << endl;
    return 0;
}
