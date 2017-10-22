ull gcd(ull a, ull b) {
	while(b) {
		a %= b;
		swap(a, b);
	}
	return a;
}
