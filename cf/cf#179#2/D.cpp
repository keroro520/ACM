/*
    绝对的好题. floyd 的理解 图论 启发题

    题意: 给出一个有N个点的带权完全图G, 再给出一个删除序列{d}, 要按照这个序列把图G中与点di相关的边删掉, 求每次删边之前的所有两点路径之和.


    
    加深了我对floyd 算法的理解! 
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    f[i][j] = update(f[i][j], f[i][k] + f[k][j])
        上面的代码中, 是每次都枚举k作为中间节点, 更新i-->j的值.
        即相当于k是新加进来的点.

	floyd是不断加k点的过程， 那么题目其实就是floyd 思想的逆过程.
*/
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
#define     N   500
long long dis[N][N];
int add[N];
vector<long long> ans;

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> dis[i][j];
    
    for(int i = 0; i < n; i++) scanf("%d", &add[i]), add[i]--;
    for(int k = add[n-1], l = n-1; l >= 0; --l, k = add[l]) {
        for(int i = 0; i < n; i++) if(i != k)
            for(int j = 0; j < n; j++) if(i != j && j != k) 
                if(dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];

        long long sum = 0;
        for(int i = n-1; i >= l; i--) 
            for(int j = n-1; j >= l; j--)  
                sum += dis[add[i]][add[j]];
        ans.push_back(sum);
    }
    for(int i = ans.size()-1; i >= 0; i--) cout << ans[i] << "\t";
       
    cout << endl;
    return 0;
}
