/*
  中青局 : 哈夫曼编码  huffman  实现  好题

  题意：一串字符串，用0/1编码，使得编码最短且具有唯一性，输出编码长度

  思路：huffman tree
        大牛们的实现好酷炫，学到了~
  摘：fjxmlhx大牛说得好：
 只要编码满足任意两个i j i的编码不是j的编码的前缀就行，于是考虑构造一棵trie满足节点是01，且每个叶子都对应了一个字母，且根到叶子的距离和*对应单词权最小..
 接下来考虑每一棵可行的树，实际上等于N棵只有一个叶子节点且树权为单词权的树，按照下面规则合并得到，规则是：
 1：由给定的n个权值构造n棵树只有一个叶子结点的二叉树，得到一个二叉树的合F； 2：再F中选取二棵二叉树作为左，右子树构造一棵新的二叉树，这棵树的根结点的权值为左右子树根结点权值之和。 3：在集合F中删除作为左右子树的二棵二叉树，并将新建的二叉树加入到集合F中。 4：重复2 ,3两步，当F中只剩下一棵二叉树时，结束
 可以看出，如果能找到使得最后代价最小的合并顺序，那么就他就一定是答案，可以发现最小的合并顺序求法就是合并果子，结束。


 *** 一棵trie满足节点是01，且每个叶子都对应了一个字母，且根到叶子的距离和*对应单词权最小***
*/
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <functional>
using namespace std;
priority_queue<int, vector<int>, greater<int> > Q;
int n, len;
int cnt[30];
char str[10000000];
int  solve()
{
  memset(cnt, 0, sizeof(cnt));
  for(int i = 0; i < len; i++) {
    str[i] = str[i] == '_' ? 26 : str[i] - 'A';
    cnt[str[i]]++;
  }
  while(!Q.empty()) Q.pop();
  for(int i = 0; i < 27; i++) if(cnt[i]) Q.push(cnt[i]);

  if(Q.size() == 1) { return Q.top() ; }
  int ans = 0;
  while(Q.size() > 1) {
    int x = Q.top(); Q.pop(); int y = Q.top(); Q.pop();
    ans += x + y;
    Q.push(x+y);
  }
  return ans;
}
int main()
{
  while(scanf("%s", str), strcmp(str, "END\0")) {
    len = strlen(str);
    int ans = solve();
    printf("%d %d %.1f\n", len*8, ans, len*8.0/ans);;
  }
  return 0;
}
