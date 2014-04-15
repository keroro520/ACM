#include <stdio.h>
#include <algorithm>
using namespace std;

int a[2*1000000];
long long ans = 0;
int N;
int main()
{
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &a[i]);
    sort(a, a+N);
    int step = 1;
    for(int i = 0; i < N; i += 4) {
        long long sum = 0;
        step++;
        for(int j = i; j < i+4; j++) sum += a[j];
        if(step%4 == 0)
            ans += sum * (step/4+1);
        else ans+= sum;
        if((i+1) % 16 == 0) {
            ans += a[i];
        }
    }
    for(int j = N-1; j > N-4; j--) ans += a[j];
    ans += a[N-1];
    printf("%lld\n", ans);
    return 0;
}
