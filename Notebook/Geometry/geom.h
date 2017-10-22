#include <vector>
#include <algorithm>

#define BCK(v, i) ((v)[(v).size() - (i)])

typedef long long ll;

struct pnt {
	ll x, y;
	pnt(ll x = 0, ll y = x) : x(x), y(y) {}
	pnt operator-() {return pnt(-x, -y);}
	pnt operator+(pnt o) {return pnt(x + o.x, y + o.y);}
	pnt operator-(pnt o) {return *this + (-o);}
	ll sqMag() {return x*x + y*y;}
};

typedef vector<pnt> vpt;

ll cross(pnt a, pnt b) {return a.x*b.y - b.x*a.y;}
ll dot(pnt a, pnt b) {return a.x*b.x + a.y*b.y;}

bool cnvaCmp(pnt a, pnt b) {
	ll c = cross(a, b);
	return (c == 0) ? (a.sqMag() < b.sqMag()) : (c > 0);
}
bool cartCmp(pnt a, pnt b) {
	return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x);
}

vpt hull(vpt& pts) {
	if(pts.size() < 4) return vpt(pts);
	pnt pvt = pts[0];
	for(pnt pt : pts) if(cartCmp(pt, pvt)) pvt = pt;
	for(pnt& pt : pts) pt = pt - pvt;
	sort(pts.begin(), pts.end(), cnvaCmp);
	for(pnt& pt : pts) pt = pt + pvt;
	for(pnt pt : pts) {
		while(h.size() > 1 && cross(pt - BCK(h, 1), BCK(h, 1) - BCK(h, 2)) >= 0) h.pop_back();
		h.push_back(pt);
	}
	return h;
}

//returns 2*area, oriented counterclockwise
ll area2(vpt& poly) {
	pnt opt = BCK(poly, 1);
	ll a = 0;
	for(pnt pt : poly) {
		a += cross(a, b);
		opt = pt;
	}
	return a;
}
