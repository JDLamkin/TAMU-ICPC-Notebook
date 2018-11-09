#include <vector>

using namespace std;

struct fenwick {
    vector<int> tree;

    fenwick(int size) : tree(size+1, 0) {}

    void add(int pos, int val) {
        ++pos;
        while (pos < tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }

    int get(int pos) {
        ++pos;
        int ans = 0;
        while (pos > 0) {
            ans += tree[pos];
            pos -= (pos & -pos);
        }
        return ans;
    }
};

