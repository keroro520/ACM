#include <stdio.h>
#include <string.h>

unsigned long long seq[10][4];
unsigned long long tmp[10];
int seqnum[10][10];
int seqcount[10];
int ansseq[12];
int n, m;

int check(unsigned long long *a, unsigned long long *b)
{
    return 
    ((a[0] & b[0]) == a[0])&&
    ((a[1] & b[1]) == a[1])&&
    ((a[2] & b[0]) == 0)&&
    ((a[3] & b[1]) == 0);
}

void output(unsigned long long * tmp, int i, int ans)
{
    if(i >= n){
        printf("%d\n", ans);
        return ;
    }
    if(check(tmp, seq[i])) {
        ansseq[++ansseq[0]] = i;
        output(tmp, i+1, ans+1);
    }
    else output(tmp, i+1, ans);
}
void output2()
{
    for(int k = 1; k <= ansseq[0]; k++) {
        int i = ansseq[k];
        printf("%d", seqcount[i]);
        for(int j = 0; j < seqcount[i]; j++)
            printf(" %d", seqnum[i][j]);
        printf("\n");
    }
}

void trans(unsigned long long * ki, int x)
{
    if(0 <= x && x <= 63) ki[0] |= (1LL<<x);
    else if(63 < x) ki[1] |= (1LL<<(x-64));
    else if(-63 <= x && x < 0) ki[2] |= (1LL<<(-x));
    else ki[3] |= (1LL<<(-x-64));
}
int main()
{
    int number, x;
    memset(seq, 0, sizeof(seq));
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", seqcount+i);
        for(int j = 0; j < seqcount[i]; j++) {
            scanf("%d", seqnum[i]+j);
            trans(seq[i], seqnum[i][j]);
        }
    }
    while(m--) {
        scanf("%d", &number);
        memset(tmp, 0, sizeof(tmp));
        while(number--) {
            scanf("%d", &x);
            trans(tmp, x);
        }
        memset(ansseq, 0, sizeof(ansseq));
        output(tmp, 0, 0);
        output2();
    }
    return 0;
}




