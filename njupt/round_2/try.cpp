#include <stack>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
int main(){
    int len;
    int c=0;
    string s;
 
    stack<char>as;
    getline(cin,s);
    len=s.size();
    for(int i=0;i<len;i++){
        if(s[i]=='('|| s[i] =='['){
            s[i]=(s[i]=='(')?')':']';
            as.push(s[i]);
        }
        else{
            if(!as.empty() ){
                   if(as.top()==s[i])
                    c++;
                     as.pop();
                }
           
            }
            
        }
        
        cout<<2*c<<endl;
 
         
       
        
    }
