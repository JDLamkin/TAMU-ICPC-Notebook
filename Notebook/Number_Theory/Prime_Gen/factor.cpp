#include <iostream>
#include <cmath>
#include <map>

using namespace std;

typedef unsigned long long ull;

ull cntFact(ull x, map<ull, ull>& f) {
	ull s = sqrt(x) + 1;
	s = x > s ? s : (x - 1);
	ull c = 1;
	for(; s > 1; --s) if(x % s == 0) {
		c += cntFact(s, f);
		x /= s;
		ull s2 = sqrt(x) + 1;
		s = s > s2 ? s2 : s;
		s = x > s ? s : (x - 1);
		++s;
	}
	if(f.count(x)) ++f[x];
	else f[x] = 1;
	return c;
}
