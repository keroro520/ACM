WA点：sqrt函数如果传int参数，在oj上会CE

class Point {
    public : double x, y;
    Point () { }
    Point (double x, double y) : x(x), y(y) { }
    friend Point operator - (const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
    friend Point operator + (const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    friend Point operator / (const Point &a, const double k) {
        return Point(a.x / k, a.y / k);
    }
    friend Point operator * (const Point &a, const double k) {
        return Point(a.x * k, a.y * k);
    }
};
class Line {
    public : Point a, b;
    Line () { }
    Line (const Point &a, const Point &b) : a(a), b(b) { }
    Point vec() const {
        return b - a;
    }
};

typedef		Point		Vector;


//叉积
double xmulti(Point &a, Point &b, Point &c)
{
	/* 得到ab与ac的叉积
       r>0,c在矢量ab的逆时针方向；r=0三点共线；r<0,c在矢量ab的顺时针方向 */
	return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}
double xmulti(const Point &a, const Point &b)
{
    return a.x * b.y - b.x * a.y;
}

//判断直线ab是否与线段l相交
bool cross(Point &a, Point &b, Seg &l)
{
	/* 就是判断l.a和l.b分别在直线ab的哪边，同一边则叉积之积大于0，即不相交；反之相交	*/
	return xmulti(a, b, l.a) * xmulti(a, b, l.b) <= ZERO;
}

//把浮点p的值转化为0,1或-1  (精度讨论)
int  dblcmp(double x) 
{
	if(fabs(x) <= ZERO) return 0;
	return x > 0 ? 1 : -1;
}
//判平行
bool parallel(Line &A, Line &B)
{
    return zero( (A.a.x - A.b.x)*(B.a.y - B.b.y) - (A.a.y - A.b.y)*(B.a.x - B.b.x) );
}

//求两直线的交点	要去除掉共线的可能性先喔
Point intersection(Line &A, Line &B)
{
    Point &a = A.a, &b = A.b, &c = B.a, &d = B.b, r = a;
    double t = ((a.x - c.x)*(c.y - d.y) - (a.y - c.y)*(c.x - d.x))
                / ((a.x - b.x)*(c.y - d.y) - (a.y - b.y)*(c.x - d.x));
    r.x += (b.x - a.x)*t, r.y += (b.y - a.y)*t;
    return r;
}
Point intersection(const Line &a, const Line &b)
{
    double u = xmulti(a.vec(), Point(b.b - a.b));
    double v = xmulti(a.vec(), Point(b.a - a.b));
    return (b.b * v - b.a * u) / (v - u);
}


//判断两条线段是否相交
bool inter(Seg &A, Seg &B)
{
	if(min(A.a.x, A.b.x) > max(B.a.x, B.b.x) ||
	   min(A.a.y, A.b.y) > max(B.a.y, B.b.y) ||
	   min(B.a.x, B.b.x) > max(A.a.x, A.b.x) ||
	   min(B.a.y, B.b.y) > max(A.a.y, A.b.y)) return false;
	double r1 = xmulti(A.a, A.b, B.a);
	double r2 = xmulti(A.a, A.b, B.b);
	double r3 = xmulti(B.a, B.b, A.a);
	double r4 = xmulti(B.a, B.b, A.b);
	return r1*r2 <= ZERO && r3*r4 <= ZERO;
}

// 极角排序(叉积法)
bool cmp_By_Angle(const Point &a, const Point &b) {
    int res = xxmulti(cur, a, b);
    if(res > 0) return true;
    else if(res < 0) return false;
    else return dis(a,cur) < dis(b, cur);
}


bool anticlockwise(int i)			//判断是否逆时针
{
	return dblcmp(xmulti(p[(i+1)%n] - p[i], p[(i+2)%n] - p[i])) >= 0;
}
bool is_convex_hull()				//判断凸包
{
    for(int i = 0; i < n; i++)
        if(dblcmp(xmulti(p[(i+1)%n] - p[i], p[(i+2)%n] - p[(i+1)%n])) < 0) return false;
    return true;
}
bool in_convex(const Point &peg)	//判断点是否在凸包里面
{
    for(int i = 0; i < n; i++)
        if(dblcmp(xmulti(p[i] - peg, p[(i+1)%n] - peg)) <= 0) return false;             //两种都可以
        //if(dblcmp(xmulti(p[(i+1)%n] - p[i], peg - p[(i+1)%n])) <= 0) return false;
    return true;
}
double dis_p2l(Point &p, Point &p1, Point p2)		//点到直线的距离
{
	double area = fabs(xmulti(p1 - p, p2 - p));
	return area / distance(p1, p2);
}
