
typedef long long int64;
const int N = 262144;

int di;
int64 sum, n, k;

int main() {
cin >> n >> k;
forle(i, 1, n) {
        int64 a; scanf("%lld", &a);
        int64 d = sum-(i-di-1)*(n-di-(i-di))*a;
        if(d < k) { 
            printf("%d\n", i); 
            ++di; 
            continue; 
        }
        sum += a*(i-di-1);
}
return 0;
}
