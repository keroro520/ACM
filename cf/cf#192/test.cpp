#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#define     MAXN    105
#define     debug   cout << "!" <<endl
string map[MAXN];
int row[MAXN], col[MAXN];
int n;
int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> map[i];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) if(map[i][j] == '.') {
            row[i]++;
            col[j]++;
        }
    bool ok = false;
    int flag = 0;
    for(int i = 0; i < n; i++) flag += (row[i] > 0);
    if(flag == n) ok = true;
    flag = 0;
    for(int i = 0; i < n; i++) flag += (col[i] > 0);
    if(flag == n) ok = true;
    if(!ok) {
        cout << -1 << endl;
        return 0;
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) if(map[i][j] == '.') {
            if(row[i] > 1 && col[j] > 1) {
                map[i][j] = 'E';
                row[i]--, col[j]--;
            }
        }
    for(int i = 0; i < n; i++) 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(map[i][j] == '.') cout << i+1 << " " << j+1 << endl;
    return 0;
}
