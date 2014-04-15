#include <cstdio>
#include <cmath>
#include <algorithm>
#define maxn 60
#define eps 1e-7
using namespace std;
int dcmp(double x)    //���ƾ���
{
    if(fabs(x)<eps) return 0;
    else return x<0?-1:1;
}
double toRad(double deg)   //�Ƕ�ת����
{
    return deg/180.0*acos(-1.0);
}
struct Point
{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y) {}
    void input()
    {
        scanf("%lf %lf",&x,&y);
    }
};
typedef Point Vector;
Vector operator+( Vector A, Vector B )       //������
{
    return Vector( A.x + B.x, A.y + B.y );
}
Vector operator-(Vector A,Vector B)       //������
{
    return Vector( A.x - B.x, A.y - B.y );
}
Vector operator*( Vector A, double p )      //��������
{
    return Vector( A.x * p, A.y * p );
}
Vector operator/( Vector A, double p )      //��������
{
    return Vector( A.x / p, A.y / p );
}
bool operator<(const Point& A, const Point& B )   //����Ƚ�
{
    return dcmp( A.x - B.x ) < 0 || ( dcmp( A.x - B.x ) == 0 && dcmp( A.y - B.y ) < 0 );
}
bool operator==( const Point& a, const Point& b )   //�������
{
    return dcmp( a.x - b.x ) == 0 && dcmp( a.y - b.y ) == 0;
}
struct Line
{
    Point s,e;
    Vector v;
    Line() {}
    Line(Point s,Point v,int type)://������ʽ
        s(s),v(v){}
    Line(Point s,Point e):s(s),e(e)//����ʽ
    {v=e-s;}

};
double Dot(Vector A,Vector B)//�������
{
    return A.x*B.x+A.y*B.y;
}
double Length(Vector A)//����ģ
{
    return sqrt(Dot(A,A));
}
double Angle(Vector A,Vector B)//�����н�
{
    return acos(Dot(A,B)/Length(A)/Length(B));
}
double Cross(Vector A,Vector B)//�������
{
    return A.x*B.y-A.y*B.x;
}
double Area2(Point A,Point B,Point C )//�����������
{
    return Cross(B-A,C-A);
}
double Dist(Point A,Point B)
{
    return Length(A-B);
}
Vector Rotate(Vector A, double rad)//������ʱ����ת
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A)//������λ������
{
    double L=Length(A);
    return Vector(-A.y/L,A.x/L);
}
Point GetLineIntersection(Line l1,Line l2)//��ֱ�߽���
{
    Point P=l1.s;
    Vector v=l1.v;
    Point Q=l2.s;
    Vector w=l2.v;
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
double DistanceToLine(Point P,Line L)//�㵽ֱ�ߵľ���
{
    Point A,B;
    A=L.s,B=L.e;
    Vector v1=B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double DistanceToSegment(Point P, Line L)//�㵽�߶εľ���
{
    Point A,B;
    A=L.s,B=L.e;
    if(A==B) return Length(P-A);
    Vector v1=B-A,v2=P-A,v3=P-B;
    if (dcmp(Dot(v1,v2))<0) return Length(v2);
    else if (dcmp(Dot(v1,v3))>0) return Length(v3);
    else return fabs(Cross(v1,v2)) / Length(v1);
}
Point GetLineProjection(Point P,Line L)// ����ֱ���ϵ�ͶӰ
{
    Point A,B;
    A=L.s,B=L.e;
    Vector v=B-A;
    return A+v*(Dot(v,P-A)/Dot(v,v));
}
bool OnSegment(Point p,Line l)//�����߶��ϰ����˵�
{
    Point a1=l.s;
    Point a2=l.e;
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dist(p,a1)+Dist(p,a2)-Dist(a1,a2))==0;
}
bool Paralled(Line l1,Line l2)//ֱ��ƽ��
{
    return dcmp(Cross(l1.e-l1.s,l2.e-l2.s))==0;
}
bool SegmentProperIntersection(Line l1,Line l2)//�߶��ཻ
{
    if(Paralled(l1,l2))
    {
        return false;
    }
    Point t=GetLineIntersection(l1,l2);
    if(OnSegment(t,l1))
    {
        return true;
    }
    return false;
}
int ConvexHull(Point *p,int n,Point *ch)    //��͹��
{
    sort(p,p+n);
    int m=0;
    for ( int i = 0; i < n; ++i )
    {
        while ( m > 1 && Cross( ch[m - 1] - ch[m - 2], p[i] - ch[m - 2] ) <= 0 ) --m;
        ch[m++] = p[i];
    }
    int k = m;
    for ( int i = n - 2; i >= 0; --i )
    {
        while ( m > k && Cross( ch[m - 1] - ch[m - 2], p[i] - ch[m - 2] ) <= 0 ) --m;
        ch[m++] = p[i];
    }
    if ( n > 1 ) --m;
    return m;
}
double PolygonArea(Point *p,int n)   //������������
{
    double area=0;
    for (int i=1;i<n-1;++i)
        area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2.0;
}
///*******************************************************///

int N,M,Q;
Point city[maxn],base[maxn];

int solve(int a,int b)
{
    Line train=Line(city[a],city[b]);
    int res=0;
    int i,j,k;
    for(i=0; i<M; i++)
    {
        for(j=i+1; j<M; j++)
        {
            Line vert=Line((base[i]+base[j])/2,Normal(base[i]-base[j]),1);
            if(Paralled(train,vert)) continue;
            Point t=GetLineIntersection(train,vert);
            if(!OnSegment(t,train)) continue;
            double d1=Dist(t,base[i]);

            int flag=1;
            for(k=0;k<M;k++)
            {
                if(k==i||k==j) continue;
                double d2=Dist(t,base[k]);
                if(dcmp(d2-d1)<0)
                {
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                res++;
            }
        }
    }
    return res;
}
int main()
{
    //freopen("input.txt","r",stdin);
    int i,j;
    while(scanf("%d %d",&N,&M)==2)
    {
        for(i=0; i<N; i++)
        {
            city[i].input();
        }
        for(i=0; i<M; i++)
        {
            base[i].input();
        }
        scanf("%d",&Q);
        while(Q--)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            a--,b--;
            printf("%d\n",solve(a,b));
        }
    }
    return 0;
}
