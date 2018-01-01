#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <utility>
#include <queue>
#include <cmath>

using namespace std;

struct disjoint_set {
    vector<int> parent;
    vector<int> size;

    disjoint_set() = delete;
    disjoint_set(int n) : parent(n), size(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    ~disjoint_set() = default;

    int root(int pos) {
        while (parent[pos] != pos) {
            parent[pos] = parent[parent[pos]];
            pos = parent[pos];
        }
        return pos;
    }

    bool find(int p, int q) {
        return root(p) == root(q);
    }

    void merge(int p, int q) {
        int rootp = root(p);
        int rootq = root(q);
        if (size[rootp] > size[rootq]) {
            parent[rootq] = rootp;
            size[rootp] += size[rootq];
        } else {
            parent[rootp] = rootq;
            size[rootq] += size[rootp];
        }
    }
};
