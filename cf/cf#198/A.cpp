#include <iostream>
#include <algorithm>
using namespace std;

long long Gcd(long long a, long long b)
{
	return b == 0 ? a : Gcd(b, a%b);
}
long long Lcm(long long x, long long y)
{
	//return x / Gcd(max(x, y), min(x, y)) * y;
	return x / Gcd(x, y) * y;
}
int main()
{
	for(int x = 1; x < 1000; x++)
		for(int y = x+1; y < 1000; y++) 
			if(Lcm(x, y) != Lcm(y, x)) {
				cout << x << " "  << y << endl;
				return 0;
			}
	return 0;
}
