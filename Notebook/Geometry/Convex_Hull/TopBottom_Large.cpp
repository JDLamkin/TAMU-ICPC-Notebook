#include <vector>
#include <iostream>
using namespace std;
typedef long double ld;
#define inf numeric_limits<ld>::max()

struct Point{
	ld x, y;
	friend bool operator==(Point& a, Point& b){
		return a.x == b.x && a.y == b.y;
	}
	ld slope(Point& b){
		return (b.y - y)/(b.x - x);
	}
};
//returns c_hull edge from [it, end)
template<class It> vector<Point> half_hull(It it, It end){
	vector<Point> hull;
	hull.push_back(*it);
	while(it != end && it->x == hull[0].x) ++it;
	if(it == end) return hull;
	hull.push_back(*it);

	while(++it != end){
		if(it->x == hull.back().x) continue;
		while(hull.size() > 1){
			auto back2 = hull[hull.size()-2];
			if(back2.slope(*it) > back2.slope(hull.back())) hull.pop_back();
			else break;
		}
		hull.push_back(*it);
	}
	return hull;
}

vector<Point> convex_hull(vector<Point>& p){
	sort(p.begin(), p.end(), [](Point& a, Point& b){
		return a.x == b.x ? a.y > b.y : a.x < b.x;
	});

	//get two halves of c_hull
	vector<Point> upper = half_hull(p.begin(), --p.end());
	vector<Point> lower = half_hull(p.rbegin(), --p.rend());
	//merge & return
	upper.insert(upper.end(), lower.begin(), lower.end());
	return upper;
}

int main(){
	//vector<Point> pts = {{0,1}, {0,0}, {1,1}, {1,0}};
	vector<Point> pts = {{0,2},{0,0},{2,2,},{2,0},{1,0}};
	vector<Point> c_hull = convex_hull(pts);
	for(Point p : c_hull){
		cout << '(' << p.x << ',' << p.y << ')' << endl;
	}
}
