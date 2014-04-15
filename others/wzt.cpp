#include <math.h>
#include <string>
#include <iostream>
#include <stack>
using namespace std;

bool isdigit(char ch) { return '0' <= ch && ch <= '9'; }
struct Elem {int type, value; };            //type是类型标记，1表数字，0表运算符
void PostExpression(Elem * Expression, string expr);
int Operate(int i, int j, char f);
int Calculate(Elem * Exprssion);
char Compare(char a,char b);
int top = 0;    //Expression's top

int main()
{
    Elem Expression[1000];
    string expr;
    cout << "中缀表达式: ";
    cin >> expr;
    cout << "后缀表达式: ";
    PostExpression(Expression, expr);
    cout << Calculate(Expression) << endl;
}
int Operate(int i, int j, char f)
{
    switch (f) {
        case '+' :  return i + j;
        case '-' :  return i - j;
        case '*' :  return i * j;
        case '/' :  return i / j;
        case '^' :  return (int)pow(i,j);
    }
    return 0;
}
int Calculate(Elem * Expression)
{
    int p[1000];
    int k = 0;
    int s1 = 0, s2 = 0, s3 = 0;
    for(int i = 1; i <= top; i++) {
        if(Expression[i].type == 1) {
            p[k++] = Expression[i].value;
        } else {
            s1 = p[--k];
            s2 = p[--k];
            s3 = Operate(s2,s1,(char)Expression[i].value);
            p[k++] = s3;
        }
    }
    return s3;
}
void PostExpression(Elem * Expression, string expr)
{
    stack<char> op;
    int len = expr.length();
    for(int i = 0; i < len; i++) {
        if(isdigit(expr[i])) {
            int num = 0;
            while(isdigit(expr[i+1])) {
                num = num * 10 + expr[i] - '0';
                i++;
            }
            num = num * 10 + expr[i] - '0';
            Elem tmp = {1, num};
            Expression[++top] = tmp;    //这里直接把多位数作为一个整数存到Expression里，当然标记type为1表这是数字，不懂去看上面的struct Elem;

            cout << num << " " ;
        } else if(op.empty()) {    
            op.push(expr[i]);
        } else {
            switch(Compare(expr[i], op.top())) {
                case '>' :  op.push(expr[i]); break;
                case '=' :  op.pop(); break;
                case '<' :  cout << op.top() << " " ;
                            Elem tmp = {0, op.top()};       //运算符标记为0
                            Expression[++top] = tmp;
                            op.pop();
                            i--;
                            break;
            }
        }
    }
    while(!op.empty()) {
        cout << op.top() << " ";
        Elem tmp = {0, op.top()};
        Expression[++top] = tmp;
        op.pop();
    }
    cout << endl;
}

char Compare(char a,char b)//比较运算符优先级
{
    switch(a) {
        case'+':case'-':
            if(b=='+'||b=='-'||b=='/'||b=='*'||b=='^'){
                return '<';  break; }
            else {
                return '>';break;}

        case '*':case '/':
            if(b=='+'||b=='-'||b=='(')   {
                return '>';break;}
            else {
                return '<';break;}

        /*case '^'*/
        case '^' :
            if(b == '(' || b == ')') return '<';
            else return '>';
            break;

        case '(':
            { return '>';break;}

        case ')':
            if(b=='('){
                return '=';break;}
            else{
                return '<';break;}

        default:return 0;
    }
}
