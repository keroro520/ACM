/*
          [定理](SJ 定理)
          对于任意一个 Anti-SG 游戏,如果我们规定当局面中所有的单一游
          戏的 SG 值为 0 时,游戏结束,则先手必胜当且仅当:(1)游戏的 SG 函
          数不为 0 且游戏中某个单一游戏的 SG 函数大于 1;(2)游戏的 SG 函数
          为 0 且游戏中没有单一游戏的 SG 函数大于 1。
*/
/*
	“败态后面都是胜态，胜态后面都是败态”
	这个性质在什么情况下会出现呢？
*/

/*
	sg函数只会用，不会证明啊...

	今天做到一道sg，是这样的，一个长度为n的珍珠环，每次只能选连续的m个未染色的珍珠染色，轮到谁不能染就输。
	问题很容易变为，一条长度为n-m的珍珠链，轮流选连续m个未染色的珍珠染上色。
	假设长度为n的链，我们染上i,i+1,..,i+m-1，则原链n就变成两条子链(i-1),(n-(i+m-1))
	也就是说，当前链n可以变成两个后继状态(i-1),(n-i-m+1)，利用sg函数性质抑或之.
	for(i = 1; i < n-m; i++) vis[ sg(i-1) ^ (n-i-m+1) ] = true;
*/
/*
    博弈  二维sg  好题
    题意(hdu_4111)：n堆石子，每次可以有两种操作：1、拿走一颗石子。2、将两堆石子合并
    思路：
          之前做过一堆可以分成两堆的，但是两堆合成一堆的就不知道怎么做了。看了题解，知道需要分析一些东西，感觉自己在现场赛肯定做不出来

          假设所有堆都有多余1的石子，则因为每次可以拿走一颗石子变成sum-1，也可以合并变成sum，即奇偶性试试可以随意确定的（合并a堆和b堆的>石子相当于对一堆(a+b+1)的石子减1）
          “然而，特殊情况出现了。当某些堆石子只有一颗的时候呢？只要本来要输的那个人有机会将这颗石子拿走，本来要赢的那个孩子就没有机会将>这一堆合并了！整体奇偶性一改变，输家可能变成了赢家！” （无法逆转奇偶）

          sg[x][y]表有x堆石子数为1的堆，y代表剩下的∑ai+tot-1, ai>1, tot为ai>1的堆数
		int SG(int x, int y)
		{
		    if(x == 0) return y&1;
		    if(sg[x][y] != -1)   return sg[x][y];
		    if(y == 1) return sg[x][y] = SG(x+y, 0);                //不加这一句就会WA，为什么？
		    bool vis[7];
		    memset(vis, false, sizeof vis);
		    if(x >= 2) vis[ min(5, SG(x-2, y+2+(y?1:0))) ] = true;
		    if(x >= 1 && y > 0) vis[ min(5, SG(x-1, y+1)) ] = true;
		    if(x >= 1) vis[ min(5, SG(x-1, y  )) ] = true;
		    if(y >= 1) vis[ min(5, SG(x,   y-1)) ] = true;
		    for(int i = 0; ; i++) if(!vis[i]) return sg[x][y] = i;
		}

*/


/* Nim 游戏 ================================================================*/
一次只能从某一堆取石子：抑或和S = 0，则必败；反之必胜

NimK 游戏：一次能从不超过K堆中取走任意多石子：S(p1,p2,...,pn)，若所有二进制位上的1的个数mod (k+1)都等于0，则必败；反之必胜
K = 1时，就是经典的Nim游戏。

/* Bash/Wyhoff 游戏 ========================================================*/
Bash Game: 只有一堆石子，一次最多取m个：S % (m+1) == 0，则必败；反之必胜

Wyhoff Game: 两堆石子，一次能从某一堆里取任意多，或者从两堆里取相同多的石子：xi = [i*(√5+1)], yi = [i*(√5+3)] = xi+i
	bool Wyhoff_judge(long long A, long long B)	//判断(A,B)是否为必胜态
	{
	#define     gold_cut        ((sqrt((double)5.0) + 1) / 2)
	    double k = B - A;
	    return (long long)(k * gold_cut)  != A;
	}

/* 阶梯博弈 ================================================================*/
阶梯博弈：游戏开始时任意多硬币分布在楼梯上，共n阶楼梯，从地面到最上层楼梯编号为0-n。游戏者轮流将某一阶梯j上任意多的硬币移动到下一个阶梯j-1上，将最后一枚硬币移至地上的人获胜。
解法：将所有奇数阶梯看成N堆石子，做Nim
blog: http://blog.csdn.net/kk303/article/details/6692506
blog: http://blog.sina.com.cn/s/blog_6a6aa7830100p4nb.html
poj 1704
/* 博弈的图论模型 ==========================================================*/
定义：有向图中，集合X中任意两点之间无边，称集合X为内固集。
定义：有向图中，任意不再集合X的点存在一条边指向集合X，称集合X为外固集。
定义：若集合X即是内固集，有时外固集，称X为核
显然，核就是必败态集合。如果核存在，则其中一方有必胜策略。

定理：无回路的有向图有唯一核。
blog: http://yjq24.blogbus.com/logs/42653430.html

/* SG函数模板 ==============================================================*/
int SG(int u)
{
    if(sg[u] != -1) return sg[u];
    bool vis[MAXN];
    memset(vis, false, sizeof(bool) * (n+1));
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        vis[SG(v)] = true;
    }
    for(int i = 0; i < n; i++) if(!vis[i]) return sg[u] = i;
}
