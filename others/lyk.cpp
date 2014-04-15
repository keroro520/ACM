#include "head.h"
#include "fun.h"
//#include "data.h"
int main()
{
    int v0 ;                                    /* 初始点          */
    int vv  ;                       /* 终点        */
    int i, v, w, min;                           /*声明要用到的变量*/
    int final[N];
    int dist[N];                                   /* 存储当前最少票价 */
    int path[N];                                   /*　存储路径　*/

    /*打印路线*/
    for (int i=0;i<N;i++)
    {
    printf("%5d %s \t ",i,num[i]);
    }
    printf("\n");

    GetData (v0,vv);                             /*获取起点终点*/

    /* 初始化数据 */
    for (v = 0; v < N; v++) {
        final[v] = false;
        dist[v] = cost[v0][v];
    if(v != v0 && dist[v]< I){
        path[v] = v0;
    }else{
        path[v] = -1;
    }
    }

    /* ------  寻找最低票价 dij算法 -------  */
    for (i = 0; i < N; i++) {
        min = I;                                      /* 初始最低票价无穷大  */

        for (w = 0; w < N; w++) {                     /*　遍历一遍cost[v0],寻找最小的一个*/
            if (!final[w] && dist[w] < min) {
                min = dist[w];
                v = w;
        }
        }
        final[v] = true;                              /* 加入新边          */
        for (w = 0; w < N; w++) {                      /* 更新 dist[] 数据  */
            if (!final[w] && dist[v] + cost[v][w] < dist[w]) {
                dist[w] = dist[v] + cost[v][w];
        path[w] = v;
            }
        }
    }
    
    /*　输出结果　*/
    printf("%d %s ->%d %s :最便宜%2d块！\n",v0,num[v0],vv,num[vv], dist[vv]);
    printf("路线是：\n");
    SearchPath(path,v0,vv);
    return 0;
}
