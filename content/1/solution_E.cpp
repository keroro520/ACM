#include <stdio.h>
#include<iostream>
using namespace std;

const int NN = 131072, BITS = 50, rt = 0;

int n, m, max_xor;
int nn, p, chd[NN][2];

void add_word(int dep, int a) {
    if(dep == BITS) return;
    add_word(dep+1, a>>1);
    int& c = chd[p][a&1];
    p = c? c: c=++nn;
}

int best_xor(int dep, int b) {
    if(dep == BITS) return 0;
    int high_xor = best_xor(dep+1, b>>1);
    int same = chd[p][b&1], diff = chd[p][b&1^1];
    if(diff) { 
        p = diff;   
        return high_xor<<1|1; 
    } else { 
        p = same; 
        return high_xor<<1 ;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        int a; 
        scanf("%d", &a);
        p = rt;
        add_word(0, a);
    }
    for(int j = 1; j <= m; ++j) {
        int b; 
        scanf("%d", &b);
        p = rt;
        max_xor = max(max_xor, best_xor(0, b));
    }
    printf("%d\n", max_xor);
    return 0;
}
