/*
    最小公共祖先
    题意: 给出一颗无向有边权树, 询问若干个(u,v)对的距离.


    所谓LCA 的Tarjan算法, 实际上就是在建树的过程中把query中的lca给计算出来, 所以称为`离线算法` . 是的, 本质就是这么简单, 好多解释都搞复杂了.

    步骤略, 自己google.
    理解这个算法一定要抓住`递推`的思想(也有递归在里面, 也要抓住).
    Tarjan是利用并查集实现的, 在递推过程中, 一棵树的root节点代表这棵树(联系并查集来想), 这样做的好处是, 如果问点i与j的lca, 我们只要找i,j都属于的最小的哪棵子树就行了, 因为该子树就是我们的答案. 那如何确定是那颗子树呢? 这一点后面再解释一下.
    下面说Tarjan最巧妙的点了. 因为是在建树的过程中计算所有query, 也就表示我们此刻是否能计算某一query对(u,v)的条件是 : u和v是否都已经遍历过. 所以我们可以在遍历到点v(假设经历v的时间比u晚)的时候把query给计算出来. 比如lcm(u,v)就是find(u). 那此刻的find(v)和lcm(u,v)相不相等呢? 答案是不相等, 至少在我的代码实现上不相等. 因为father[x]的更新是在`递归回去`的时候更新的, 而此刻在遍历v点, 还没递归回去呢, father[v]当然也就没更新啦.
    其实上一段就已经回答了`如何确定哪棵子树是我们想要的答案`这一问题了. 就是find(u)所代表的子树! 注意, 是find(u), 不是find(v)! 因为u是在v之前已经被遍历过了, 并且递归回去过sub_root过了, 也就是father[u]被更新为sub_root了, 所以find(u)可以代表当前的sub_tree, 即`最小包含(u,v)子树`

下面两个解释, 推荐一下. 罗嗦一句, 看代码更容易理解, 人脑模拟一遍更容易理解
    http://www.nocow.cn/index.php/Tarjan%E7%AE%97%E6%B3%95
    http://blog.chinaunix.net/uid-1721137-id-181005.html
*/
#include <vector>
#include <stdio.h>
using namespace std;
#define     MAXN    40001
#define     debug   printf("!\n")
vector<int> v[MAXN], w[MAXN], query[MAXN], ans_num[MAXN];
int father[MAXN], dis[MAXN], ans[201];
bool visit[MAXN];
int n;

void init()
{
    for(int i = 1; i <= n; i++) {
        v[i].clear();
        w[i].clear();
        ans_num[i].clear();
        query[i].clear();
        father[i] = i;
        dis[i] = 0;
        visit[i] = false;
    }
}

int find(int x) 
{ 
    return x == father[x] ? x : father[x] = find(father[x]); 
}
void Union(int x, int y) { father[find(y)] = find(x); }
void Tarjan(int now, int value)
{
    visit[now] = true;
    dis[now] = value;
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
        if(visit[tmp] != 0) continue;
        Tarjan(tmp, value + w[now][i]);
        Union(now, tmp);            //注意顺序, 先Tarjan子节点tmp, 再更新其father[tmp], 因为要保证在递推tmp所代表的子树时, father[tmp] = tmp, 而与当前子树无关. 递归回来的时候再把tmp代表的子树`并入`到当前树里
    }

    for(int Size = query[now].size(), i = 0; i < Size; i++) {
        int tmp = query[now][i];
        if(!visit[tmp]) continue;       //若visit[tmp] == true, 即表示tmp节点已经遍历过, 此时可计算相应的query
        ans[ans_num[now][i]] = dis[now] + dis[tmp] - 2 * dis[find(tmp)];
    }
}

int main()
{
    int cases, Query, x, y, z;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &Query);
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d%d", &x, &y, &z);
            v[x].push_back(y);
            w[x].push_back(z);
            v[y].push_back(x);
            w[y].push_back(z);
        }

        for(int i = 0; i < Query; i++) {
            scanf("%d%d", &x, &y);
            query[x].push_back(y);
            query[y].push_back(x);
            ans_num[x].push_back(i);
            ans_num[y].push_back(i);
        }
        Tarjan(1, 0);
        for(int i = 0; i < Query; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
/*
     Tarjan算法是利用并查集来实现的。它按DFS的顺序遍历整棵树。对于每个结点x，它进行以下几步操作：
   * 计算当前结点的层号lv[x]，并在并查集中建立仅包含x结点的集合，即root[x]:=x。
   * 依次处理与该结点关联的询问。
   * 递归处理x的所有孩子。
   * root[x]:=root[father[x]]（对于根结点来说，它的父结点可以任选一个，反正这是最后一步操作了）。
    
　　现在我们来观察正在处理与x结点关联的询问时并查集的情况。由于一个结点处理完毕后，它就被归到其父结点所在的集合，所以在已经处理过的结点中（包括 x本身），x结点本身构成了与x的LCA是x的集合，x结点的父结点及以x的所有已处理的兄弟结点为根的子树构成了与x的LCA是father[x]的集合，x结点的父结点的父结点及以x的父结点的所有已处理的兄弟结点为根的子树构成了与x的LCA是father[father[x]]的集合……（上面这几句话如果看着别扭，就分析一下句子成分，也可参照右面的图）假设有一个询问(x,y)（y是已处理的结点），在并查集中查到y所属集合的根是z，那么z 就是x和y的LCA，x到y的路径长度就是lv[x]+lv[y]-lv[z]*2。累加所有经过的路径长度就得到答案。 　　现在还有一个问题：上面提到的询问(x,y)中，y是已处理过的结点。那么，如果y尚未处理怎么办？其实很简单，只要在询问列表中加入两个询问(x, y)、(y,x)，那么就可以保证这两个询问有且仅有一个被处理了（暂时无法处理的那个就pass掉）。而形如(x,x)的询问则根本不必存储。 　　如果在并查集的实现中使用路径压缩等优化措施，一次查询的复杂度将可以认为是常数级的，整个算法也就是线性的了。
 *
