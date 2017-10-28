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
