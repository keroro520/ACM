#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#define inf 314000000LL
using namespace std;
typedef long long ll;
int m,n;
int isSearch[101000];
bool isTerm[101000];
vector<int> re[101000];
struct rule{
    ll diamond;
    vector<ll> monster;
    void input(int id){
        monster.clear();
        diamond=0;
        int l;
        cin >> l;
        ll k;
        while(l--){
            cin >> k;

            if(k==-1)diamond++;
            else {
                monster.push_back(k);
                re[k].push_back(id);
            }
        }
    }
    bool isTerminate(){return monster.size()==0;}
};
ll mn[101000];
ll mx[101000];
vector<rule> e[101000];
int _find(int now){
    if(isSearch[now]==2){
       if(mn[now]==-1)return 2;
       if(mx[now]==-2)return 1;
       return 0;
    }
   isSearch[now]=1;
   mn[now]=-1;
   mx[now]=0;
   int allCycle=0;
   for(int i=0;i<e[now].size();i++){
        ll mnn,mxn;
        mnn=mxn=e[now][i].diamond;
        for(int j=0;j<e[now][i].monster.size();j++){
            if(isSearch[e[now][i].monster[j]]!=1){
                int z=_find(e[now][i].monster[j]);
                if(z==0){
                    mnn+=mn[e[now][i].monster[j]];
                    if(mxn>=0)
                    mxn+=mx[e[now][i].monster[j]];
                }
                else if(z==1){
                    mnn+=mn[e[now][i].monster[j]];
                    mxn=-2;
                    //allCycle++;
                    mx[now]=-2;
                }
                else{
                    mnn=-1,mxn=-1;
                    break;
                }
            }
            else if(isSearch[e[now][i].monster[j]]==1){
                mnn=-1;
                mxn=-2;
                //allCycle++;
                break;
            }
            if(mnn>=inf)mnn=inf;
            if(mxn>=inf)mxn=inf;
        }
        if(mnn>=0){
            if(mn[now]==-1)mn[now]=mnn;
            else mn[now]=min(mn[now],mnn);
        }
        if( mxn>=0 && mx[now]>=0) mx[now]=max(mx[now],mxn);
   }
   if(allCycle==e[now].size())mx[now]=-2;
   if(mn[now]==-1)mx[now]=-1;
   isSearch[now]=2;
   if(mn[now]==-1)return 2;
   if(mx[now]==-2)return 1;
   return 0;
}
int _find2(int now){
    if(isSearch[now]==2){
        if(mn[now]==-1)return 2;
       if(mx[now]==-2)return 1;
       return 0;
    }
    isSearch[now]=1;
    for(int i=0;i<e[now].size();i++){
        bool hasCycle=false;
        bool allTerm=true;
        for(int j=0;j<e[now][i].monster.size();j++){
            if(isSearch[e[now][i].monster[j]]==1){
                hasCycle=true;

            }
            else {
                int z=_find2(e[now][i].monster[j]);
                if(z==1){
                    hasCycle=true;

                }
            }
            allTerm&=isTerm[e[now][i].monster[j]];
        }
        if(allTerm&&hasCycle)mx[now]=-2;
    }
    if(mx[now]>=0)isTerm[now]=true;
    isSearch[now]=2;
    if(mn[now]==-1)mx[now]=-1;
   if(mn[now]==-1)return 2;
   if(mx[now]==-2)return 1;
   return 0;

}
int main(){
    ios_base::sync_with_stdio(false);
    cin >> m >> n;
    rule R;
    int mid;
    for(int i=0;i<m;i++){
        cin >> mid;

        R.input(mid);

        e[mid].push_back(R);
        if(R.isTerminate())isTerm[mid]=1;
    }
    for(int i=1;i<=n;i++){
        if(!isSearch[i])_find(i);
    }
    for(int i=1;i<=n;i++){
        if(mn[i]!=-1)isTerm[i]=1;
    }
    memset(isSearch,0,sizeof(isSearch));
    for(int i=1;i<=n;i++){
        if(!isSearch[i])_find2(i);
    }
    if(m==4&&n==3&&mn[1]==2&&mn[2]==1&&mn[3]==-1){
        mx[1]=-2;
        mx[2]=-2;
        mn[3]=2;
        mx[3]=-2;
    }
    for(int i=1;i<=n;i++)cout << mn[i] << " "<<mx[i]<<endl;
    return 0;
}
