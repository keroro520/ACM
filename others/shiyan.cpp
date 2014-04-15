/*
#include<iostream>
using namespace std;
#define INF 100000
#define INFTY 10000000
enum
ResultCode{NoMemory,OutOfBounds,Underflow,Overflow,Failure,NotPresent,Duplicate,Success};
template<class T>
class Graph
{
	public:
		virtual ResultCode Insert(int u,int v,T &w)=0;
		virtual bool Exist(int u,int v)const=0;
		virtual int Vertices()const {return n;}
	protected:
		int n,e;
};
template<class T>
class MGraph:public Graph<T>
{
	public:
		MGraph(int mSize,const T &noedg);
		~MGraph();
		ResultCode Insert(int u,int v,T &w);
		bool Exist(int u,int v)const;
	protected:
		T **a;T noEdge;
};
template<class T>
MGraph<T>::MGraph(int mSize,const T &noedg)
{
	n=mSize;e=0;noegd=noEdge;
	a=new Enode<T> *[n];
	for(int i=0;i<n;i++) ;
	{
		a[i]=new T [n];
		for(int j=0;j<n;j++) a[i][j]=noEdge;
		a[i][i]=0;
	}
}
template<class T>
MGraph<T>::~MGraph()
{
	for(int i=0;i<n;i++) delete[]a[i];
	delete[]a;
}
template<class T>
bool MGraph<T>::Exist(int u,int v)
{
	if(u<0||v<0||u>n-1||v>n-1||u==v||a[u][v]==noEdge) return false;
	return true;
}
template<class T>
ResultCode MGraph<T>::Insert(int u,int v,T &w)
{
	if(u<0||v<0||u>n-1||v>n-1||u==v)
		return Failure;
	if(a[u][v]!=noEdge)
		return Duplicate;
	a[u][v]=w;e++;return Success;
}
template<class T>
class ExtMGraph:public MGraph<T>
{
	public:
		ExtMGraph(int mSize,const T &noedg):MGraph<T>(mSize,noedg){}
		int Choose(int *d,bool *s);
		void Dijkstra(int v,T *d,int *path);
	//	void Floyd(T **d,int **path);
		void Print(int k);
		//void Print(int u,int v);
};
template<class T>
int ExtMGraph<T>::Choose(int *d,bool *s)
{
	int i,minpos;T min;
	min =INFTY;minpos=-1;
	for(i=0;i<n;i++)
		if(d[i]<=min&&!s[i])
		{ min=d[i];minpos=i; }
		return minpos;
}
template<class T>
void ExtMGraph<T>::Dijkstra(int v,T *d,int *path)
{
	int i,k,w;
	if(u<0||u>n-1||v<0||v>n-1) throw OutOfBounds;
	bool *s=new bool[n];
	for(i=0;i<n;i++)
	{
		s[i]=false;d[i]=a[v][i];
		if(i!=v&&d[i]<INFTY) path[i]=v;
		else path[i]=-1;
	}
	s[v]=true;d[v]=0;
	for(i=1;i<n;i++)
	{
		k=Choose(d,s);s[k]=true;
		for(w=0;w<n;w++)
			if(!s[w]&&d[k]+a[k][w]<d[w])
			{ d[w]=d[k]+a[k][w];path[w]=k; }
	}
}
/*template<class T>
void ExtMGraph<T>::Floyd(T **d,int **path)
{
	int i,j,k;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			d[i][j]=a[i][j]; 
			if(i!=j&&a[i][j]<INFTY) path[i][j]=i;
			else path[i][j]=-1;
		}
		for(k=0;k<n;k++)
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					if(d[i][k]+d[k][j]<d[i][j])
					{
						d[i][j]=d[i][k]+d[k][j];path[i][j]=path[k][j];

					}
}*/
/*
template<class T>
void ExtMGraph<T>::Print(int k)
{
	cout<<k<<d[k];
	for(int i=1;i<k;i++)
		cout<<path[i]<<"->";
	cout<<endl;
}
*/
/*template<class T>
void ExtMGraph<T>::Print(int u,int v)
{
	cout<<"from"<<u<<"to"<<v<<":"<<d[u][v];
	int k=path[u][v];
	while(k!=u)
	{
		cout<<k<<"<-";
		k=path[u][k];
	}
}*/
/*
void mian()
{
	ExtMGraph<int> p(4,4);
	int k=1;
	p.Insert(0,1,k);
	p.Insert(0,3,k);
	p.Insert(1,0,k);
    p.Insert(1,2,k);
	p.Insert(1,3,k);
	p.Insert(2,1,k);
	p.Insert(2,3,k);
	p.Insert(3,0,k);
	p.Insert(3,1,k);
	p.Insert(3,2,k);
	int *a=new int[100];
	int *b=new int[100000];
	p.Dijkstra(5,a,b);
	//p.Floyd(&a,&b);
//	int u,v;
//	cin>>u>>v;
	int c=3;
	p.Print(c);
}*/

#include <map>
#include<iostream>
#include <string>
using namespace std;
#define INF 100000

int pre[100000];
int dis[1000], path[1000][1000];
bool visit[1000];
map<string, int> Map;
map<int,string> Remap;
//m["A"] = 1;
//m['B'] = 2;
//path[1][2] = 3;

void dijkstra(int n, int start, int det)
{
	for(int i = 0; i < n; i++) visit[i] = false;
	for(int i = 0; i < n; i++) dis[i] = INF;
	dis[start] = 0;
	for(int k = 0; k < n; k++) {
		int min = INF, mini = -1;
		for(int i = 0; i < n; i++) if(!visit[i] && dis[i] < min) {
			min = dis[i], mini = i;
		}
		/*
			case 终点无法到达
			case 当mini == det 时可以直接结束
		*/
		visit[mini] = true;
		for(int i = 0; i < n; i++) if(visit[i] == false && dis[i] > min + path[mini][i]) {
			dis[i] = min + path[mini][i];
			pre[i]=mini;
		}
	}
}

void output(int v ,int u)
{
	if(v==u){
		cout<<Remap[u];return;
	}
	output(pre[v],u);
	cout<<Remap[v];

}

int main()
{
	int m;int  j=1;
	cin>>m;
	string a,b;int price;
	for(int i=1;i<m;i++){
		cin>>a>>b>>price;
		
		if(Map[a]==0){
			Map[a]=j;Remap[j]=a;j=j+1;
		}
		if(Map[b]==0){
			Map[b]=j;Remap[j]=b;j=j+1;
		}
		path[Map[a]][Map[b]]=price;
	}
	string start,end;
	cin>>start>>end;
	if(!path[Map[start]][Map[end]])
		cout<<path[Map[start]][Map[end]];
	dijkstra(j, Map[start],Map[end]);
	output(Map[end],Map[start]);
    cout<<dis[Map[end]];
	return 0;
}
