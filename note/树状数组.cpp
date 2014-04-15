/*
    二维树状数组

    区间修改，询问单点
    TODO : 到底“区间修改，询问单点” 和 “修改单点，询问区间” 有什么本质上的区别？ poj_2155 与 poj_1195

    心得：先记录“区间修改，询问单点”的理解。
          Update()和一般的树状数组的顺序倒了过来，因为Updtae(x,y,add)是指在[0,0,x,y]这个区间都加上add，所以我们就相当于标记区间一样，在[0,0,x,y]的“关键点”上加上add。为什么标记的时候是向下的顺序？理解了二维树状的构造就能大概理解了。
          二维树状数组的构造:http://fqq11679.blog.hexun.com/21722866_d.html

          Query ()和一般的树状数组的顺序倒了过来，Query(x, y)就是查包含(x,y)这个点的所有区间的add之和。区间修改的时候是在区间上标记，则>询问单点的时候就是向上询问包含(x,y)的区间标记之和。


          那一般的“单点修改，区间求和”呢？这种情况是标记点，询问的时候向下询问，即向下把该区间的点的值都加起来。
          细节上面还没考虑，现在的水平还没办法思考细节，只能感性上理解。

        大牛blog : http://hi.baidu.com/edelweisszf/item/f5a0139f55c480cfb6253156
                   http://www.cnblogs.com/ambition/archive/2011/04/06/bit_rmq.html
*/


// ========== *** 模式1: 修改单点，区间求和 *** =======================================================
poj 1195
        one :在二维情况下，如果修改了A[i][j]=delta,则对应的二维树状数组更新函数为： 
        two :在二维情况下，求子矩阵元素之和∑ a[i][j](前i行和前j列)的函数为 :
        void Update(int x, int y, int add)
        {
            for(int i = x; i <= n; i += low(i))
                for(int j = y; j <= n; j += low(j)) c[i][j] += add;
        }
        int Query(int x, int y)
        {
            int sum = 0;
            for(int i = x; i > 0; i -= low(i))
                for(int j = y; j > 0; j -= low(j))
                    sum += c[i][j];
            return sum;
        }



//========== *** 下面是区间0/1覆盖问题，不知道为什么，跟标准的区间求和不一样  *** ==============  TODO  
//========== *** 模式2: 修改区间，询问单点 *** ========================================================
poj 2155
    //此过程是向下求的，不同于标准向上求
    void Update(int x, int y, int val)
    {
        for(int i = x; i > 0; i -= low(i))
            for(int j = y; j > 0; j -= low(j))
                c[i][j] += val;
    }
    //此过程是向上求的，不同于标准向下求
    int  Query(int x, int y)
    {
        int result = 0;
        for(int i = x; i <= n; i += low(i))
            for(int j = y; j <= n; j += low(j))
                result += c[i][j];
        return result;
    }
//=============================================================================================*/
