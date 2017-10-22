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
