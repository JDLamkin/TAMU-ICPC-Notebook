def modexp(base, exp, mod):
    res = 1;
    while exp > 0:
        if exp % 2 == 1:
            res = res * base % mod
        base = base * base % mod
        exp = exp // 2
    return res

# a * n + b * m = g = gcd(n, m)
def bezout(n, m): # return (a, b, g)
    if m == 0:
        return (1, 0, n)
    (x, y, g) = bezout(m, n % m)
    return (y, x - y*(n // m), g)

def modinv(a, m):
    (r, _, _) = bezout(a, m);
    return r

def gcd(a, b):
    (_, _, g) = bezout(a, b)
    return g

# r % n = a
# r % m = b
def crt(a, b, n, m):
    (x, y, _) = bezout(n, m)
    return x*n*b + y*m*a
