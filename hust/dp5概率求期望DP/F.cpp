/*
    概率DP 

    题意：在ACM比赛种出题，共M道题，T个队，要求冠军出的题数不少于N，问每队至少过一题且冠军至少N题的概率。

    思路：易知每个队至少出一题的概率是相互独立的。p[i][j]表示队i出j题的概率，g[i][j][k]表示队i对于前j题而言作出k题的概率。
          g[i][j][k] = g[i][j-1][k-1] * p[i][j]  +  g[i][j-1][k] * (1 - p[i][j])
          则对于队i，至少作出1题的概率为 1 - g[i][M][0].
          则每个队至少作出1题的概率为 ans = ∏(1-g[i][M][0])

          接着考虑至少有一队过N题的概率 = ans - 所有队都没过N题的概率
                                        = ans - ∏( Σ g[i][M][j] ) ,  j = 1,2,...,N-1
*/
//poj 2151
#include <stdio.h>
double get[1005][35][35], p[1005][35];

int main()
{
    int Team, Topic, MaxTopic;
    while(scanf("%d%d%d", &Topic, &Team, &MaxTopic), Topic+Team+MaxTopic) {
        for(int i = 1; i <= Team; i++)
            for(int j = 1; j <= Topic; j++) scanf("%lf", &p[i][j]);
        
        double ans = 1.0;
        for(int i = 1; i <= Team; i++) {
            get[i][0][0] = 1;
            for(int j = 1; j <= Topic; j++) {
                get[i][j][0] = get[i][j-1][0] * (1 - p[i][j]);
                for(int k = 1; k <= j; k++) 
                    get[i][j][k] = get[i][j-1][k-1] * p[i][j] + get[i][j-1][k] * (1 - p[i][j]);
            }
            ans *= (1 - get[i][Topic][0]);      //每队至少过一题的概率
        }
        double tot = 1.0;
        for(int i = 1; i <= Team; i++) {
            double tmp = 0;
            for(int j = 1; j < MaxTopic; j++) tmp += get[i][Topic][j];
            tot *= tmp;         //没有一个队过N题的概率
        }
        printf("%.3f\n", ans - tot);
    }
    return 0;
}
