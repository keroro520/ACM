
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

int max_size, m;
deque<int> dq;

int main() {
    scanf("%d %d", &max_size, &m);
    while(m--) {
        char op[16]; scanf("%s", op);
        if(op[1] == 'u') {
            int x; scanf("%d", &x);
            dq.push_back(x);
            if(dq.size() > max_size) dq.pop_front();
        } else if(op[1] == 'o') {
            if(dq.size() == 0) puts("Empty!");
            else /* */ printf("%d\n", dq.back()), dq.pop_back();
        }
    }
    return 0;
}
