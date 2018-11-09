#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

void prime_gen(vector<ull>& v, ull mx) {
    vector<bool> sieve(mx + 1);
    for(ull i = 2; i <= mx; ++i) {
        if(sieve[i]) continue;
        v.push_back(i);
        for(ull j = i*i; j <= mx; j += i)
            sieve[j] = true;
    }
}
