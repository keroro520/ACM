#include <iostream>
#include <string>
#include <vector>
using namespace std;
string s1 = "heavy", s2 = "metal", content;
vector<long long> v1,v2,seq;

int main()
{
    cin >> content;
    long long pos = -1, len = content.length();
    while((pos = content.find(s1, pos+1)) != string :: npos) { //是-1吗
        v1.push_back(pos);
    }
    pos = -1;
    while((pos = content.find(s2, pos+1)) != string :: npos) { //是-1吗
        v2.push_back(pos);
    }
    long long i = 0, j = 0;
    long long Size1 = v1.size(), Size2 = v2.size();
    while(i < Size1 && j < Size2) {
        if(v1[i] < v2[j]) {
            seq.push_back(0); 
            i++;
        } else {
            seq.push_back(1);
            j++;
        }
    }
    for(j ; j < Size2; j++) seq.push_back(1);
    long long ans = 0, sum = 0;
    i = 0;
    for(long long Size3 = seq.size(); i < Size3; i++) {
        if(seq[i] == 0) sum++;
        else ans += sum;
    }
    cout<< ans  << endl;
    return 0;
}
