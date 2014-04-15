#include <stdio.h>
#include <algorithm>
using namespace std;
#define     LIMIT       33
class Trie {
    public :
    Trie * children[2];
    Trie () { children[0] = children[1] = NULL; }

    void Insert(int x, int deep)
    {
        if(deep == -1) return ;
        int t = ((x >> deep) & 1LL);
        if(!children[t]) children[t] = new Trie();
        children[t]->Insert(x, deep-1);
    }

    int Query(int x, int deep)
    {
        if(deep == -1) return 0;
        int t = (( x >> deep ) & 1LL);
        if(children[!t]) return (1LL << deep) + children[!t]->Query(x, deep-1);
        else return children[t]->Query(x, deep-1);
        return 0;
    }
};
Trie * root = new Trie();
int n, m;

int main()
{
    int x;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
		a[i] = x;
        root->Insert(x, LIMIT);
    }
    int ans = 0;
    for(int i = 0; i < m; i++) {
		x = a[i];
        ans = max(ans, root->Query(x, LIMIT));
    }
    printf(ans > m ? "YES\n" : "NO\n");
    return 0;
}
