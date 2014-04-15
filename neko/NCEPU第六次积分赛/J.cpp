#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    long long n;
    while(cin >> n, n) 
        puts(n % 2 == 0 ? "Alice" : "Bob");
    return 0;
}
