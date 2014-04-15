#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <vector>

const int MaxN=100000+500;

using namespace std;
int father[MaxN],s[MaxN],vis[MaxN];
char ch[MaxN];
vector < int > Son[MaxN];
int N;
int DFS(int x){
    s[x]=1;
    for (int i=0;i<Son[x].size();i++)
    if (father[x]!=Son[x][i]){
        father[Son[x][i]]=x;
        DFS(Son[x][i]);
        s[x]+=s[Son[x][i]];
    }
}
int Did(int x){
    for (int i=0;i<Son[x].size();i++){
        int y=Son[x][i];
        if (vis[y]) continue;
        if (s[y]>s[x]/2){
            int tmp=s[y];
            s[y]=s[x];
            s[x]=s[y]-tmp;
            father[y]=x;
            father[x]=0;
            return Did(y);
        }
    }
    return x;
}
int Do(int x,char c){
    int k=Did(x);
    ch[k]=c;
    vis[k]=1;
    for (int i=0;i<Son[k].size();i++){
        int y=Son[k][i];
        if (!vis[y]){
            father[y]=0;
            Do(y,c+1);
        }
    }
}
int main(){
    cin >> N;
    for (int i=1;i<=N;i++)
    Son[i].clear();
    int M;
    for (int i=1;i<N;i++){
        int x,y;
        scanf("%d %d", &x, &y);
        Son[x].push_back(y);
        Son[y].push_back(x);
    }
    memset(father,0,sizeof father);
    DFS(1);
    memset(vis,0,sizeof vis);
    Do(1,'A');
    for (int i=1;i<=N;i++){
        printf("%c", ch[i]);
        if (i==N) puts("");else
        printf(" ");
    }
    return 0;
}
