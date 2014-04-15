#include <iostream>
#include <math.h>

using namespace  std;
const int StackSize=50;
static int h=0;
char *q=new char[50];
bool isdigit(char ch) {
    return ch >= '0' && ch <='9';
}
class Stack   //堆栈类
{
	char *StackList;
	int top;
public:
	Stack()
	{
		StackList=new char[StackSize];
		top=-1;
	}
	bool IsEmpty();
	bool IsFull();
	void Push(char x);
	char Pop();
	char GetTop();
	char Compare(char,char);//比较运算符优先级
	void PostExpression(char *,int);//中缀转化为后缀,并求值输出
	int Operate(int ,int ,char );//运算
};
char Stack::GetTop()
{
	if (IsEmpty()) {
		cout<<"栈空！"<<endl;  
        return 0;
    } else return StackList[top];
}
bool Stack::IsFull( )
{
	if(top==StackSize-1)
		return true;
	else
		return false;
}
bool Stack::IsEmpty ( )
{
	if(top==-1)
		return true;
	else
		return false;
}
void Stack::Push(char x)
{
	if (IsFull( ))
		cout<<"栈满！"<<endl;
	else
		StackList[++top]=x;
}
char Stack::Pop( )
{
	if (IsEmpty( )) {
		cout<<"栈空！"<<endl;
        return 0;
    }
	return StackList[top--];
}

void Stack::PostExpression(char *expression,int j)//转化
{
	for(int k=0;k<=j;k++)
		if(isdigit(expression[k])) {
            while(isdigit(expression[k+1])) {   //@@ 跟原来的没什么区别，因为多位数是几个数字凑一块儿，所以应该放一块处理blablabla
                cout << expression[k];
                q[h++] = expression[k];
                k++;
            }
            q[h++] = expression[k];
            cout << expression[k] << " ";
            q[h++] = ' ';       //为了Calculate的时候把两个数字区分开，这点得去看void Calclate()才能懂
        } else if(top==-1) {
			Push(expression[k]);
        } else {
            switch(Compare(expression[k],GetTop())) {
                case '>':   Push(expression[k]); break;
                case '=':   Pop(); break;  
                case '<':   cout << GetTop();
			                q[h++] = GetTop();
			                Pop();
                            k--;
                            break;
            }
		}

	while(top!=-1) {
		cout<<GetTop();
		q[h++]=GetTop();
		Pop();
	}
	cout<<endl;
}


int Stack::Operate(int i,int j,char f)//运算
{
	switch(f)
	{
	case '+':return (i+j);break;
	case '-':return (i-j);break;
	case '*':return (i*j);break;
	case '/':return (i/j);break;
	case '^':return (int)(pow(i,j));break;
	default:    return 0;break;
	}
}
char Stack::Compare(char a,char b)//比较运算符优先级
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


void Calculate(Stack E)//计算结果
{
	int *p;
	p = new int[1000];
	int k=0;
	int s1=0,s2=0,s3=0;
	for(int i=0;i<h;i++) {
		if(isdigit(q[i])) {
            int result = 0;
            do {
                result = result * 10 + q[i] - '0';
                i++;
            } while(i < h && isdigit(q[i]));    //q里面若有连续的一块儿数字，那它(们)就是多位数...一起处理blablabla
            i--;
			p[k++] = result;
        } else if(q[i] == ' ') continue;    //这就是为什么PostExpression里在解析完一个数字后就在后面扔一个空格的原因
        else {
			s1=p[--k];
			s2=p[--k];
			s3=E.Operate(s2,s1,q[i]);
			p[k++]=s3;
		}
	}
	cout<<"后缀表达式运算结果是:"<<s3<<endl;
}


int main()
{
    int i, j;
	Stack Expression;
	char c;
	char *expression;
	expression=new char[StackSize];
	cout<<"输入中缀表达式:"<<endl;
	cin>>c;
	for(i=0;c!='='&&i<StackSize;i++)
	{
		expression[i]=c;
		cin>>c;
	}
	cout<<"输出中缀表达式:"<<endl;
	for(j=0;j<i;j++)
	{
		if(expression[j]>='0'&&expression[j]<='9')
			cout<<expression[j]<<" ";
		else
			cout<<expression[j]<<" ";
	}
	cout<<"="<<endl;
	cout<<"输出后缀表达式:"<<endl;
	Expression.PostExpression(expression,j);
	Calculate(Expression);
	return 0;
}
