#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Node
{
public:
    string name;
    Node *child[10];
    Node();
    Node(const string x);
    Node * search(string x,Node &n);
    void insert(string x,Node &n,Node &m);
    void remove(string x,Node &n);
    void printall(Node & n, int);
    void print(string x, Node &n);
    void out(ofstream &);
};




Node::Node(const string x)
{
    name=x;
    for(int i=0;i<10;i++)
        child[i]=NULL;
}
Node::Node()
{
    for(int i=0;i<10;i++)
        child[i]=NULL;
}
/*
Node * Node :: search(string x, Node &n)

{
    if(x==n.name)
        return &n;
    else
    {
        for(int i=0;n.child[i]!=NULL;i++)
        {
            if (x==n.child[i]->name)
                return child[i];
            else
                for(int k=0;n.child[i]->child[k]!=NULL;k++)
                    if (x==n.child[i]->child[k]->name)
                        return n.child[i]->child[k];
        }
    
        cout << "搜索失败"<<endl;
        return NULL;
    }
}
*/
Node * Node :: search(string x,Node &n)
{
    if(x==n.name)
        return &n;
    else
        for(int i=0;n.child[i]!=NULL;i++)
            if(search(x,  *n.child[i]))
                return search(x,  *n.child[i]);

            
    return NULL;
}
    
void Node::insert(string x,Node &n, Node &m)
{
    m.name=x;

    int i=0;
    for(i;n.child[i]!=NULL;i++);
    n.child[i] = &m;
}

void Node::print(string x, Node &n)
{   
    if(n.child[0] == NULL) cout << n.name ;
    for(int i=0;n.child[i]!=NULL;i++) {
        Node * tmp = this->search(x, *n.child[i]);
        if(tmp == NULL) continue;
        cout << n.name << " -> " ;
        this->print(x, *n.child[i]);
    }
        
                

/*  for(int i=0;n.child[i]!=NULL;i++)
    {
        if (x==n.child[i]->name)
            cout<<n.name<<endl<<" "<<child[i]->name<<endl; 
        else
            for(int k=0;n.child[i]->child[k]!=NULL;k++)
                if (x==n.child[i]->child[k]->name)
                    cout<<n.name<<endl<<" "<<child[i]->name<<endl<<"  "<<n.child[i]->child[k]->name<<endl; 
                }
    cout<<"搜索失败";

  */
}
void Node::printall(Node & n, int indent)
{
    for(int k = 0; k < indent; k++) cout << " ";
    cout<<n.name<<endl;
    for(int i=0;n.child[i]!=NULL;i++)
    {
//      cout<<" "<<child[i]->name<<endl;
        child[i]->printall(*child[i], indent+2);
//      for(int k=0;n.child[i]->child[k]!=NULL;k++)
//          cout<<"  "<<n.child[i]->child[k]->name<<endl; 
    }

    

}
void Node:: remove(string x,Node &n)
{
        for(int i=0;n.child[i]!=NULL;i++)
            if(n.child[i]->name == x)
                for( i;n.child[i]!=NULL;i++)
                    n.child[i] =n.child[i+1];
            else remove(x, *n.child[i]);
}
void Node :: out(ofstream & ofs)
{
    for(int i=0; child[i]!=NULL;i++) {
        ofs << child[i]->name << "   " <<  this->name<< endl;
        child[i]->out(ofs);
    }
}

void insert(Node &a)
{
        Node *tmp[1000];
        int tmp_top = 0;
        string s,pres;
                cout<<"请输入要添加的文件"<<endl;
                cin>>s;
                cout<<"请输入添加文件的前文件"<<endl;
                cin>>pres;
                Node *z;
                z=a.search(pres,a);
//              cout << z->name << endl;
                tmp[tmp_top] = new Node(s);
                a.insert(s,*z, *tmp[tmp_top++]);
//              a.printall(a, 0); 
}
void search(Node &a)
{
    cout<<"请输入要查找的文件"<<endl;
    string k;
    cin>>k;
    a.print(k,a);  
}
void remove(Node &a)
{
    cout<<"请输入要删除的文件"<<endl;
                string y;
                cin>>y;
                a.remove(y,a);
}




int  main()
{
    

    Node a("/"); //,b,c,d,e,f,g,h;
    Node *tmp[1000];
    int tmp_top = 0;
    string s1,s2;

    ifstream ifs ("in.txt", ifstream :: in);
    while(ifs >> s1 >> s2) {
        //cout << s1 << "   " << s2 << endl;
        tmp[tmp_top] = new Node(s1);
        a.insert(s1, *a.search(s2, a), *tmp[tmp_top++]);//把s1查到s2后
    }
    a.printall(a,0);
    ifs.close();
    bool out_flag = false;
    for(;;)
    {
        cout<<"          UNIX文件系统的模拟          "<<endl;
        cout<<"添加文件请输入1                       "<<endl;
        cout<<"查找文件请输入2                       "<<endl;
        cout<<"删除文件请输入3                       "<<endl;
        cout<<"输出系统请输入4                       "<<endl;
        cout<<"退出系统请输入5                       "<<endl;
        
        int key;
        cin>>key;
        if(key>0&&key<=5)
        {
            switch(key%6)
            {
            case 1:
                insert(a);
                break;
            case 2: 
                search(a);
                break;
            case 3:
                remove(a);
                break;
            case 4:
                cout<<"当前文件系统为:"<<endl;
                a.printall(a, 0);
                break;
            case 5:
                cout<<"退出系统"<<endl;
                out_flag = true;
                break;
            }
        }
        else
            cout<<"输入错误请重新输入"<<endl;
        if(out_flag) break;
    }

    ofstream ofs ("in.txt", ifstream :: out);
    a.out(ofs);
    ofs.close();
    return 0;
}
