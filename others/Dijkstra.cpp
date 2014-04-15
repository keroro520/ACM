/*
input:in.txt
m roads
A B p  //A->B cost $p
*/
#include <string.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;
#define     INF     9999999
#define     MAXN    1000
map<string, int> m;
map<int, string> rm;
vector<int> v[MAXN], e[MAXN];
int pre[MAXN], dis[MAXN];
bool visit[MAXN];
string src, det;
int city_num = 0;

bool dijkstra(int s)
{
    int i, Size;
    memset(visit, false, sizeof(visit));
    for(i = 1; i <= city_num; i++) dis[i] = INF;
    dis[s] = 0;
    for(int k = 1; k < city_num; k++) {
        int min = INF, mini = -1;
        for(i = 1; i <= city_num; i++) 
            if(!visit[i] && dis[i] < min) {
                min = dis[i], mini = i;
            }
        visit[mini] = true;
        if(mini == -1) return false;
        if(mini == m[det]) return true;
        for(Size = v[mini].size(), i = 0; i < Size; i++) {
            int y = v[mini][i];
            if(!visit[y] && dis[y] > min + e[mini][i]) {
                dis[y] = min + e[mini][i];
                pre[y] = mini;
            }
        }
    }
    return true;
}
void output(int v)
{
    if(v == m[src]) {
        cout << src ;
        return ;
    }
    output(pre[v]);
    cout << " -> " << rm[v] ;
}
int main()
{
    ifstream ifs ("in.txt", ifstream :: in);
    string s1, s2;
    int p, M;
    ifs >> M;
    for(int i = 0; i < M; i++) {
        ifs >> s1 >> s2 >> p;
        if(m[s1] == 0) m[s1] = ++city_num, rm[city_num] = s1;
        if(m[s2] == 0) m[s2] = ++city_num, rm[city_num] = s2;
        v[m[s1]].push_back(m[s2]);
        e[m[s1]].push_back(p);
    }
    while(true) {
        cout << "start && end city : " ;
        cin >> src >> det;
        if(m[src] == 0 || m[det] == 0) {
            if(m[det] == 0) 
                cout << "Not found city " << det << endl << endl;
            if(m[src] == 0) 
                cout << "Not found city " << src << endl << endl;
            continue;
        }
        if(!dijkstra(m[src])) {
            cout << src << " Can't arrive " << det << endl << endl;
            continue;
        }
        vector<int> :: iterator it = find(v[m[src]].begin(), v[m[src]].end(), m[det]);
        if(it != v[m[src]].end()) 
            cout << "Non-stop: " << src << " -> " << det << "   " << e[m[src]][it-v[m[src]].begin()] << endl;
        output(m[det]);
        cout << "   " << dis[m[det]] << endl << endl;
        string op;
    }
    return 0;
}
