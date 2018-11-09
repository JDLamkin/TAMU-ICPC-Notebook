#include <iostream>
#include <tuple>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

typedef tuple<ll, ll, ull> tllu;

ull modexp(ull b, ull e, ull m) {
    ull r = 1;
    while(e > 0) {
        if(e % 2 == 1)
            r = r*b % m;
        b = b*b % m;
        e /= 2;
    }
    return r;
}

// a * n + b * m = g = gcd(n, m)
tllu bezout(ull n, ull m) { // return {a, b, g}
    if(m == 0)
        return {1, 0, n};
    ll x, y; ull g;
    tie(x, y, g) = bezout(m, n % m);
    return {y, x - y*(n/m), g};
}

ull modinv(ull a, ull m) {
    ll r = get<0>(bezout(a, m));
    return (r % (ll)m + m) % m;
}

ull gcd(ull a, ull b) {
    return get<2>(bezout(a, b));
}

// r % n = a
// r % m = b
ull crt(ull a, ull b, ull n, ull m) {
    ll x, y; ull M;
    tie(x, y, M) = bezout(n, m);
    ll r = x*n*b + y*m*a;
    M = n*m;
    return (r % (ll)M + M) % M;
}
