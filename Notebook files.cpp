//--------------------------- Number Theory ---------------------------//
ull gcd(ull a, ull b) {
	while(b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

struct rat {
	ll n;
	ull d;
	rat(ll nn = 0, ull dd = 1) : n(nn), d(dd) {
		ull c = gcd(n < 0 ? -n : n, d);
		n /= c;
		d /= c;
	}
	rat operator+(rat o) {return rat(o.d*n + d*o.n, d*o.d);}
	rat operator-() {return rat(-n, d);}
	rat operator-(rat o) {return *this + (-o);}
	rat operator*(rat o) {return rat(n*o.n, d*o.d);}
	rat operator/(rat o) {
		bool sgn = o.n < 0;
		if(sgn) o.n = -o.n;
		return rat(n*o.d*(sgn ? -1 : 1), o.n*d);
	}
	bool operator<(rat o) {return n*o.d < d*o.n;}
};


//------------------------------- Graph -------------------------------//
/* Toplogical sort algorithm (Kahn's).
 * Takes a graph of in_edges and a graph of out_edges
 * Running time: O(E + V)
 */

typedef vector<map<int, int>> graph;
bool cycle = false;

vector<int> dist(graph &in, graph &out) {
    vector<int> order;
    queue<int> next;

    for (int i = 0; i < in.size(); ++i) {
        if (in[i].empty()) next.push(i);
    }
    while (!next.empty()) {
        int cur = next.front(); next.pop();
        order.push_back(cur);
        for (auto e : out[cur]) {
            int v = e.first;
            in[v].erase(cur);
            if (in[v].empty()) {
                next.push(v);
            }
        }
    }
    for (int i = 0; i < in.size(); ++i) {
        if (!in[i].empty()) {
            cycle = true;
            break;
        }
    }
    return order;
}

/* Floyd-Warshall is all-pairs shortest path that *does* handle
 * negative edge weights (but not cycles). 
 * Running time: O(V^3)
 */

typedef vector<map<int, int>> graph;
#define INF numeric_limits<int>::max()

vector<vector<int>> dist(graph &g) {
    vector<vector<int>> dist(g.size(), vector<int>(g.size(), INF));

    for (int u = 0; u < g.size(); ++u) {
        dist[u][u] = 0;
        for (auto v : g[u]) dist[u][v.first] = v.second;
    }
    for (int k = 0; k < g.size(); ++k) {
        for (int i = 0; i < g.size(); ++i) {
            for (int j = 0; j < g.size(); ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}


/* Dijkstra's is single-source shortest path that does NOT handle negative edge weights. 
 * Running time: O(E*log(E))
 */

typedef vector<map<int, int>> graph;
#define INF numeric_limits<int>::max()

vector<int> dist(graph &g, int src) {
    vector<int> dist(g.size(), INF);
    vector<bool> vis(g.size());

    auto cmp = [](pair<int, int> one, pair<int, int> two) { return one.second > two.second; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    dist[src] = 0;
    pq.push(make_pair(src, 0));

    while (!pq.empty()) {
        auto cur = pq.top().first; pq.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (auto adj : g[cur]) {
            if (dist[cur] + adj.second < dist[adj.first]) {
                dist[adj.first] = dist[cur] + adj.second;
                pq.push(make_pair(adj.first, dist[adj.first]));
            }
        }
    }
    return dist;
}


/* Bellman-ford is single-source shortest path that *does*
 * handle negative edge weights. 
 * Running time: O(E*V)
 */

typedef vector<map<int, int>> graph;
#define INF numeric_limits<int>::max()

vector<int> dist(graph &g, int src) {
    vector<int> dist(g.size(), INF);
    dist[src] = 0;
    for (int i = 0; i < g.size()-1; ++i) {
        for (int u = 0; u < g.size(); ++u) {
            for (auto k : g[u]) {
                int v = k.first, w = k.second;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    return dist;
}


/**
 * Generate a Minimum Spanning Tree on `g'.
 * Returns the total edge weight of the MST.
 * Preconditions:
 *  parent.size() == g.size();
 *  `g' is bidirectional and connected.
 * Postconditions:
 *  `parent[i]' refers to the parent vertex to `i' in the MST.
 * Complexity:
 * 	Time: O(E log E)
 * 	Space: O(V + E)
 */
ll PrimsMST(graph& g, vector<ull>& parent) {
	priority_queue<pair<ll, ull>> q;
	vector<ull> vis(g.size());
	ull vert = 0;
	ll w = 0;
	parent[vert] = vert;
	while(true) {
		vis[vert] = true;
		for(auto e : g[vert]) q.push(make_pair(e.second, e.first));
		while(!q.empty() && !vis[q.top().second]) q.pop();
		if(q.empty()) return w;
		auto e = q.top();
		q.pop();
		w += e.first;
		parent[e.second] = vert;
	}
}


/* Dinic's algorithm - max flow / bipartite matching
 * Running time: O(E*V^2) in general and O(E*sqrt(V)) on bipartite graphs with unit edge weights
 */

typedef vector<map<int, int>> graph;
typedef map<int, int>::iterator it;
#define INF numeric_limits<int>::max()

bool bfs(graph &g, vector<int> &level, int s, int t) {
    for (int i = 0; i < g.size(); ++i) level[i] = -1;
    level[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : g[u]) {
            int v = e.first, w = e.second;
            if (level[v] < 0 && w > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] >= 0;
}
int dfs(graph &g, vector<int> &level, vector<it> &start, int u, int t, int flow) {
    if (u == t) return flow;
    for (it& e = start[u]; e != g[u].end(); ++e) {
        int v = e->first, w = e->second;
        if (level[v] == level[u]+1 && w > 0) {
            int cur_flow = min(flow, w);
            int temp_flow = dfs(g, level, start, v, t, cur_flow);
            if (temp_flow > 0) {
                g[u][v] -= temp_flow;
                g[v][u] += temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}
int dinic(graph &g, int s, int t) {
    int total = 0;
    vector<int> level(g.size());
    vector<it> start(g.size());

    while (bfs(g, level, s, t)) {
        for (int i = 0; i < g.size(); ++i) start[i] = g[i].begin();
        while (int flow = dfs(g, level, start, s, t, INF)) {
            total += flow;
        }
    }
    return total;
}



//------------------------------ Geometry -----------------------------//
struct vec2 {
	ll x, y;
	explicit vec2(ll x = 0, ll y = 0) : x(x), y(y) {}
	vec2 operator+(vec2 o) {return vec2(x + o.x, y + o.y);}
	vec2 operator*(ll m) {return vec2(x*m, y*m);}
	vec2 operator-() {return *this * -1;}
	vec2 operator-(vec2 o) {return *this + (-o);}
};


#define BCK(v, i) ((v)[(v).size() - (i)])
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


/* Convex Hull (Top-Bottom) */
struct Point{
	ld x, y;
	friend bool operator==(Point& a, Point& b){
		return a.x == b.x && a.y == b.y;
	}
	ld slope(Point& b){
		return x == b.x ? inf : (b.y - y)/(b.x - x);
	}
};
//returns c_hull edge from [it, end)
template<class It> vector<Point> half_hull(It it, It end){
	vector<Point> hull;
	hull.push_back(*it); hull.push_back(*(++it));
	while(++it != end){
		if(it->x == hull.back().x) continue;
		auto back2 = hull[hull.size()-2];
		while(back2.slope(hull.back()) <= back2.slope(*it)) hull.pop_back();
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


//---------------------------- Binary Data ----------------------------//
/* Range Tree */
#include <functional>

ull MSB(ull x) {
	x |= x >> 0x01;
	x |= x >> 0x02;
	x |= x >> 0x04;
	x |= x >> 0x08;
	x |= x >> 0x10;
	x |= x >> 0x20;
	return (x >> 1) + 1;
}
template<typename T> struct rtree {
	vector<T> v; T z; function<T(T, T)> c;
	rtree(ull n, function<T(T, T)> m, T x = T()) : v(MSB(n - 1) << 2, x), c(m), z(x) {}
	// Set the value at i to x and update the tree
	void set(ull i, T x) {
		for(i += v.size()/2; i; i /= 2) {
			v[i] = x;
			x = c(v[i & ~1], v[i | 1]);
		}
	}
	// Return reference to the value at i
	T& raw(ull i) {
		return v[i + v.size()/2];
	}
	// Update the whole range tree
	void update() {
		for(ull i = v.size()/2 - 1; i; --i) {
			v[i] = c(v[2*i], v[2*i + 1]);
		}
	}
	T get0(ull b, ull s, ull e, ull i, ull j) {
		if(s == i && e == j) return v[b];
		ull m = (s + e)/2;
		if(j <= m) return get0(2*b, s, m, i, j);
		if(i >= m) return get0(2*b + 1, m, e, i, j);
		return c(get0(2*b, s, m, i, m), get0(2*b + 1, m, e, m, j));
	}
	// Return the sum between [i, j)
	T get(ull i, ull j) {
		if(i >= j) return z;
		return get0(1, 0, v.size()/2, i, j);
	}
};
struct irtree : rtree<ll> {
	irtree(ull n) : rtree<ll>(n, [](auto x, auto y) {return x + y;}, 0) {}
};



//----------------------- Body/Header Templates -----------------------//
/* Header Small */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


/* Header Large */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<unordered_map<ull, ll> > graph;


/* Body Large */
int main() {
	int n; cin >> n;
//	ios_base::sync_with_stdio(false);

//	vector<int> v; v.reserve(n);
//	copy_n(istream_iterator<int>(cin), n, back_inserter(v));

	while(n --> 0) {
		//CODE
	}
}
