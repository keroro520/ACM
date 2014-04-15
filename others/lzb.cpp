#include <stdio.h>
#include <stdlib.h>
#include "iostream"   
#include <math.h>
using namespace std;  
enum ResultCode{Underflow,Overflow,RangeError,Success,Duplicate,Fail,NotPresent};  
  
template<class T>  
struct SNode                       
{  
    SNode(int mSize)  
    {  
        link = new SNode* [mSize];  
        size = mSize;    
    }  
    ~SNode()  
    {  
        delete []link;  
    }  
    int size;  
    T element;  
    SNode<T> **link;  
};  
  
template<class T>  
class SkipList  
{  
    public:  
        SkipList(T large, int mLev); 
		void CreateSkipList(T* A,int n);
        ~SkipList();  
        ResultCode Insert(T x);  
        ResultCode ListOut();  
        ResultCode Search(T x);  
        ResultCode Remove(T x);  
    private:  
        int Level();  
        SNode<T>* SaveSearch(T x);  
        int maxLevel, levels;  
        SNode<T> *head, *tail, **last;
  
};  
  
template<class T>  
SkipList<T>::SkipList(T large, int mLev)  
{  
    maxLevel = mLev;  
    levels = 0;  
    head = new SNode<T>(maxLevel+1);        
    tail = new SNode<T>(0);                    
    last = new SNode<T>*[maxLevel+1];     
    tail->element = large;               
    for (int i=0; i<=maxLevel; i++)  
    {  
        head->link[i] = tail;           
    }    
}  
  
template<class T>  
SkipList<T>::~SkipList()  
{  
  
    SNode<T>* ptr=head;
    SNode<T>* pre=head;
    while(pre!=NULL)
    {
        ptr=ptr->link[0];
        delete pre;
        pre=ptr;
    };

}  
template<class T>  
ResultCode SkipList<T>::ListOut()  
{  
  SNode<T> *p=head; 
  for(int i=0;i<maxLevel;i++) 
 {  
          cout<<i<<":"; 
		  p=head->link[i]; 
     while(p!=tail) 
	 {  
        cout<<p->element<<" ";  
        p=p->link[i]; 
	 } 
        cout<<endl; 
  }
  return Success;
}
template<class T>  
int SkipList<T>::Level()  
{  
    int lev = 0;  
    while (rand()<=RAND_MAX/2)  
        lev++;  

    return(lev<=maxLevel)?lev:maxLevel;  
}  
  
template<class T>  
SNode<T>* SkipList<T>::SaveSearch(T x)  
{  
    SNode<T> *p = head;  
    for (int i=levels; i>=0; i--)  
    {  
        while (p->link[i]->element<x)                 
      
            p = p->link[i];  
       
        last[i] = p;           
    }  
    return(p->link[0]);  
}  
  

  
template<class T>  
ResultCode SkipList<T>::Search(T x)  
{  
    if(x>=tail->element)
		return RangeError;
	SNode<T>*p=head;
    for (int i=levels; i>=0; i--)  
    {  
        while (p->link[i]->element<x)  
        {  
              
            p = p->link[i];  
        }  
    }  
    if (p->link[0]->element == x)  
    {  
		x=p->link[0]->element;
        return Success; 
    }  
    else  
    {  
        return NotPresent;  
    }  
}  
  
template<class T>  
ResultCode SkipList<T>::Remove(T x)  
{  
    if (x>= tail->element)  
    {  
        return RangeError;  
    }  
    SNode<T> *p = SaveSearch(x);  
    if ( x != p->element)  
    {  
        return NotPresent;  
    }  
  
    for (int i=0; i<=levels && last[i]->link[i]==p; i++)  
    {  
        last[i]->link[i] = p->link[i];   
    }  
	while(levels>0 && head->link[levels]==tail)
		levels--;
	x=p->element;
	delete p;
    return Success;  
}  
  
template<class T>  
ResultCode SkipList<T>::Insert(T x)  
{  
    if (x>=tail->element)  {  
        return RangeError;  
    }  
    SNode<T> *p = SaveSearch(x);  
  
    if (p->element == x)  {  
        x=p->element; 
        return Duplicate;  
    }  
      
    int lev = Level();                 
    if (lev > levels)  {  
        lev = ++levels;  
        last[lev] = head;  
    }  
  
    SNode<T> *y = new SNode<T>(lev+1);        
    y->element = x;  
    for (int i=0; i<=lev; i++) {  
        y->link[i] = last[i]->link[i];  
        last[i]->link[i] = y;  
    }  
    return Success;  
}  
 
int main()  
{  
	int choose;
	int n;
	int ele[300] ;
	cout<<"-------------跳表------------"<<endl;
	cout<<"请输入元素个数:"<<endl;
    scanf("%d", &n);  
    cout<<"请输入跳表中的元素:"<<endl;
    for(int tt = 0; tt < n; tt++) 
	scanf("%d", &ele[tt]);
    int maxlevel=int(log(n)/log(2)); 
    SkipList<int> sl(9999,maxlevel);
	for(int i = 0; i < n; i++)  {
		sl.Insert(ele[i]); 
	}
    cout<<endl<<endl;
	cout<<"初始状态为:"<<endl;
	sl.ListOut(); 
	cout<<endl<<endl;
	while(1) 
	{    
         cout<<"***********操作菜单**********"<<endl;
	 	 cout<<"*****************************"<<endl; 
		 cout<<"   1.查找           2.插入"<<endl; 
		 cout<<"   3.删除           4.输出"<<endl;  
		 cout<<"            0.退出        "<<endl; 
		 cout<<"*****************************"<<endl;  
		 cout<<"请进行选择:"<<endl;  
		 scanf("%d",&choose);
		 while(choose<0||choose>4)  
		 {    printf("输入有误，请重新输入!\n");   
		       scanf("%d",&choose);  
		 }   
		 switch(choose)   
		 { 
		 case 1:{  
				int i;
			    cout<<"输入搜索的元素:"<<endl;
			    cin>>i; 
				
				i= sl.Search(i);  
	            if (i==3)  
				{  
					 cout<<"Success"<<endl;  
				}  
				 else  
				 {  
                  cout<<"Not Present"<<endl;  
				}  
				break;
				}
		 case 2:{
			  cout<<"输入插入的元素:"<<endl;
			  int m;
			  cin>>m; 
			  sl.Insert(m);     
			  break;
				}
		 case 3:{
			 cout<<"输入删除的元素:"<<endl;
			 int n;
			 cin>>n; 
			 sl.Remove(n);
			 break;
				}
		 case 4:{
			 cout<<"操作后显示为:"<<endl;
			sl.ListOut();
			break;
				}
		 case 0:{
		   exit(0);
		   break;
				}
		}
	}
    return 0;
}
