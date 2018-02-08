#include <vector>
#include <cmath>

using namespace std;

struct tree {
    vector<int> parent, level;
    vector<vector<int>> ancestor;

    tree(int n) : parent(n+1, -1), level(n+1, -1), ancestor(n+1, vector<int>((int)ceil(log2(n)), -1)) {
        level[0] = 0;
    }

    void insert(int i, int par) {
        parent[i] = par;
        level[i] = level[par]+1;
        ancestor[i][0] = par;

        for (int j = 1; (1<<j) < parent.size(); ++j) {
            if (ancestor[i][j-1] != -1) ancestor[i][j] = ancestor[ancestor[i][j-1]][j-1];
        }
    }

    int lca(int u, int v) {
        if (level[u] < level[v]) swap(u, v);
        
        int dist = level[u] - level[v];
        while (dist > 0) {
            int rb = log2(dist);
            u = ancestor[u][rb];
            dist -= (1 << rb);
        }

        if (u == v) return u;

        for (int j = log2(parent.size()); j >= 0; --j) {
            if (ancestor[u][j] != -1 && ancestor[u][j] != ancestor[v][j]) {
                u = ancestor[u][j];
                v = ancestor[v][j];
            }
        }

        return parent[u];
    }
};
