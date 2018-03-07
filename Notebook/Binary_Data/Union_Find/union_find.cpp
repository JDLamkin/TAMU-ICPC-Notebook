#include <vector>
using namespace std;

struct disjoint_set{
    vector<int> parent;

    ~disjoint_set() = default;
    disjoint_set() = delete;
    disjoint_set(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int root(int pos) {
        int tmp = pos;
        while (parent[tmp] != tmp) {
            tmp = parent[tmp];
        }
        while (pos != tmp) {
            int next = parent[pos];
            parent[pos] = tmp;
            pos = next;
        }
        return tmp;
    }

    bool find(int p, int q) {
        return root(p) == root(q);
    }

    void merge(int p, int q) {
        int rootp = root(p), rootq = root(q);
        parent[rootp] = rootq;
    }
};
