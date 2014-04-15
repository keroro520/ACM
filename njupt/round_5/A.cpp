#include <iostream>
using namespace std;
int main()
{
    int I;
    while(cin >> I, I) {
        int i;
        for(i = 0; i < 31; i++) if(( I & (1 << i)) && (!(I & (1 << (i+1))))) {
            I += (1 << (i+1));
            I -= (1 << i);
            break;  
        }
        int sum = 0;
        for(i = i - 1; i >= 0; i--) 
            if(I & (1 << i)) sum++, I -= (1 << i);
        for(i = 0; i < sum; i++) I += (1 << i);
        cout << I << endl;
    }
    return 0;
}
