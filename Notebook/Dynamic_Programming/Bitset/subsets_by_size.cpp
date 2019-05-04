#include <bits/stdc++.h>

using namespace std;

inline int next_bit_perm(int v) {
    int t = v | (v - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}

void iterate(int n) {
    for (int k = 0; k <= n; ++k) {
        for (int w = (1<<k)-1; w < (1<<n); w = next_bit_perm(w)) {
            // do stuff
        }
    }
}
