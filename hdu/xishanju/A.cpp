#include <iostream>
#include <deque>
#include <string>
using namespace std;
deque<string> Q[22]; 
int sum;
string people;
void init()
{
    sum = 0;
    for(int i = 0; i <= 20; i++) Q[i].clear();
}
void insert(string name, int power)
{
    Q[power].push_back(name);
}
bool find(int power)
{
    bool flag = false;
    for(int i = power; i <= 20; i++) if(!Q[i].empty()) {
        flag = true;
        people = Q[i].front();
        Q[i].pop_front();
        break;
    }
    return flag;
}
int main()
{
    int cases, Cas = 1, query, power;
    string name, op;
    cin >> cases;
    while(cases--) {
        cout << "Case #" << Cas++ << ":" << endl;
        init();
        cin >> query;
        while(query--) {
            cin >> op;
            if(op == "Add") {
                cin >> name >> power;
                insert(name, power);
                sum++;
                cout << sum << endl;
            } else {
                cin >> power;
                if(find(power)) {
                    sum--;
                    cout << people << endl;
                } else {
                    cout << "WAIT..." << endl;
                }
            }
        }
    }
    return 0;
}
