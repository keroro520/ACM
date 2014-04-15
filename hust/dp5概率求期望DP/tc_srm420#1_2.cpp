//tc srm420 div 500


double get_profit(int R, int B) {
    for(int i = 0; i <= R; i++) {
        cur ^= 1;
        for(int j = 0; j <= B; j++)
            if(i == 0) e[i][j] = 0;
            else if(j == 0) e[i][j] = e[i-1][j] + 1;
            else e[i][j] = max((e[i-1][j]+1) * (i*1.0/(i+j)) + (e[i][j-1]-1)*(j*1.0/(i+j)), 0);
    }
}

e(i,j)剩余i张红牌j张黑牌，还能赢钱的期望。
e(0,0) = 0;
(0,j) 状态只会输钱，计算的话期望为负数，所以我们取为0，即停止翻牌。
(i,0) 只会赢钱，所以e(i,0) = e(i-1,0) + 1;
(i,j) = max(0 , (1 + e(i-1,j)) * i/(i+j) + (1 + e(i,j-1)) * j/(i+j));
目标状态e(R,B)
