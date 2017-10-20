struct vec2 {
	ll x, y;
	explicit vec2(ll x = 0, ll y = 0) : x(x), y(y) {}
	vec2 operator+(vec2 o) {return vec2(x + o.x, y + o.y);}
	vec2 operator*(ll m) {return vec2(x*m, y*m);}
	vec2 operator-() {return *this * -1;}
	vec2 operator-(vec2 o) {return *this + (-o);}
};
