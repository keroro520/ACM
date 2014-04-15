
相邻0/1序列交换  好题  思路题   启发题

link : http://blog.csdn.net/keroro520/article/details/12614455



昨天做CF D题，是neko搞出来的，赛后看了一下standing上别人的代码，记下对这道题的理解。
problem link: http://codeforces.com/contest/353/problem/D
首先来一个最短的代码：

[cpp] view plaincopy
for(int i = 0; i < n; i++) {  
    if(str[i] == 'M') x++;  
    else if(x) y = max(y+1, x);  
}  
printf("%d\n". y);  


x是前面boys的累加，a表前面最近一个girl，b表当前girl，y0是a所需要的时间，y1是b所需要的时间。
<1>首先，y0+1和x是y1的两个下界。
     证明：不论a、b相对位置如何，x是y1的一个下界都没有争议吧，因为b至少要跟x个人交换嘛； 若a、b是相邻的，则显而易见y1 = y0 + 1；若a、b不相邻，当然，下界还是(y0+1, x)~~对了，我这里说的“下界”只是为了说明y1肯定比x和y0+1大
<2>两个下界的最大值就是当前girl b所需要的时间
    证明：如果b能畅通无阻地走到其目的地，则所需时间为x；
              如若不能，说明在某个时刻a会挡住b，即a、b贴在一起。OK，既然知道她们俩在某个时刻会贴在一起，而移动又都是同步的，那y1 = y0 +１
　　这种思路的巧妙性在于，它不去讨论两个girls中间有多少个boys，而是直接就分成上述两种情况，掩盖了各种讨论的种种细节。

       这种做法给我的启发，遇到这种需要分很多种情况的题，不妨换种思路，换种分情况的法子。像这道题，因为交换是同步的，然后每一次交换都把序列变得乱七八糟的没有规律。如果找到“不论怎样，每个girl的相对顺序不变”，“当前girl所需的时间只跟前面那个girl移动的时间和前面总boys数有关”这两个性质，大概就能分析出来了。

ps : if(x) .... 这是为了判断前导‘F’的情况。





再来一发：
[cpp] view plaincopy
for(int i = 0; i < n; i++) {  
    if(str[i] == 'F') {  
        time = i - female++;  
        if(time) time += continousFemale++;  
    } else {  
        continousFemale = max(0, continousFemale-1);  
    }  
    ans = max(ans, time);  
}  

这份代码我并没理解到它的精髓。
continousFemale其实就是当前女孩所需要等待的时间（所需时间 = 移动到目的地的步数 + 等待时间），有种同性相加，异性相消的感觉...
随便记点小理解吧~    str[i] == 'M'，说明后面的女生又可以少一个空闲时间了(假设continousFemale > 0)，因为多了一个str[i]要交换呀...
我根据这份代码猜测出一个结论：把girl看成1，boy看成-1，得到一个1/-1序列。若有0~i-1的前缀和sum都大于等于0，则对于当前位置i上的女生，她的等待时间为sum。
如果遇到前缀和小于0的时候，我们把前面砍掉，sum清空为0，重新从下一个位置开始计算一个新的前缀和sum。
只是猜测，不知对错，不知怎么证明，但我觉得要是搞懂这个点应该是很有价值的。有想出证明的大神路过求告知~~


第3分比较常规，跟第2分类似：
[cpp] view plaincopy
for(int i = 0; i < n; i++) {  
    if(str[i] == 'F') to[i] = dst++;  
    else to[i] = -1;  
}  
delay[0] = 0;  
for(int i = 1; i < n; i++) {  
    if(to[i] == i) delay[i] = 0;  
    else if(str[i] == str[i-1] && str[i] == 'F') delay[i] = delay[i-1] + 1;  
    else if(str[i] == str[i-1] && s[i] == 'M') delay[i] = max(0, delay[i-1] - 1);  
    else delay[i] = delay[i-1];  
}  
for(int i = 0; i < n; i++)   
    if(str[i] == 'F' && to[i] != i)   
        ans = max(ans, i - to[i] + delay[i]);  
