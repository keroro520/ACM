/*
	记忆化  DP  好题
	题意：题意：给你n个坐标点（n<=16），问你最少划几条线能穿过所有的点


	思路：n很少，所以直接就想到了状压DP，方程也很容易就想出来了，目测是可以瞬秒的题，结果...悲剧了。
		  写迭代的DP不断地TLE，我是用的递推式DP，因为递推式DP比较简单好写，在一些小地方优化了一些，还是TLE。看了wuyiqi的代码，发现我和他只是写法不一样而已，他是记忆化递归，我是迭代递推，但思路都一样。能够明显感觉到记忆化DP相对于迭代的优势，但又有说不出来的感觉，于是请教了wuyiqi，他建议我要体会到记忆化与迭代DP的效率差别的话最好每道题都先记忆化写一遍。受教了。
		  写了一个记忆化DP，1A了。代码很容易懂。
		  
	 	  顺便记一下剪枝吧。
		  <1>预处理出line[i,j]表示i,j连成的直线能覆盖的点集状态。
		  <2> 对于只剩两个点或一个点没有覆盖的点集S，可以 f[所有点集] = f[S] + 1. 
		 	  for(int i = 0; i < n; i++) for(int j = i; j < n; j++) f[line[i][j]] = 1;		//这算是个简单的剪枝吧
			  像在wuyiqi代码里面是每次都要算一遍S的‘1’的个数，如果小于等于2的话就return 1.
		  <3> 因为每个点都要被覆盖，而如果i, j , k(i < j < k)共线，那枚举线段的第一个点(line(start, end)) 枚举到 i 点就可以break;了，也就是不枚举j , k.	这个剪枝很重要，不加直接TLE。           TODO  
*/
//lightoj 1018
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     N   17
int f[1 << N], n, line[N][N];
struct point {
    int x, y;
} a[N];
int cross(point &a,point &b,point &c) {
    return ! ((b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x)) ;
}
void init()	
{
    memset(line, 0, sizeof(line));
    for(int i = 0; i < n; i++) { 
        for(int j = i+1; j < n; j++) {
            for(int k = j+1; k < n; k++) if(cross(a[i], a[j], a[k])) {
                line[i][j] |= (1 << k);
                line[i][k] |= (1 << j);
                line[j][k] |= (1 << i);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        line[i][i] = (1 << i);
        for(int j = i+1; j < n; j++)
            line[j][i] = (line[i][j] |= (((1 << i) | (1 << j))));
    }
}
void Update(int &x, int y)
{
	if(x == -1) x = y; else if(y < x) x = y;
}
int DP(int S)
{
	if(f[S] != -1) return f[S];
	for(int i = 0; i < n; i++) if((1 << i) & S) {
		for(int j = i+1; j < n; j++) if((1 << j) & S) {
			Update(f[S], DP(S - (S & line[i][j])) + 1);
		}
		break;		// TODO  IMPORTANT
	}
	return f[S];
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d%d", &a[i].x, &a[i].y);
        init();
        memset(f, -1, sizeof(f));
		f[0] = 0;
		for(int i = 0; i < n; i++) for(int j = i; j < n; j++) f[line[i][j]] = 1;		//这算是个简单的剪枝吧
        printf("Case %d: %d\n", ++Cas, DP((1 << n) - 1));
    }
    return 0;
}
