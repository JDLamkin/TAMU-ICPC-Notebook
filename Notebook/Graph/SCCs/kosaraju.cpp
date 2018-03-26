/* Kosaraju's algorithm - Computes SCCs in O(V+E) time using two DFSs.
 * Returns a DAG of how the SCCs are connected, as well as populating a disjoint set with the SCC information.
 */

#include <vector>
#include <map>
#include <stack>

using namespace std;

typedef vector<map<int, int>> graph;

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

void dfs(graph &g, stack<int> &s, vector<bool> &vis, int cur) {
    vis[cur] = true;
    for (auto &p : g[cur]) {
        if (!vis[p.first]) dfs(g, s, vis, p.first);
    }
    s.push(cur);
}

void dfs2(graph &g, disjoint_set &ds, vector<bool> &vis, int start, int cur) {
    vis[cur] = true;
    ds.merge(start, cur);
    for (auto &p : g[cur]) {
        if (!vis[p.first]) {
            dfs2(g, ds, vis, start, p.first);
        }
    }
}

graph scc(graph &out, graph &in, disjoint_set &ds) {
    vector<bool> vis(out.size());
    stack<int> s;

    for (int i = 0; i < in.size(); ++i) {
        if (!vis[i]) dfs(in, s, vis, i);
    }

    map<int, int> tag;
    fill(vis.begin(), vis.end(), false);
    int count = 0;
    while (!s.empty()) {
        int cur = s.top(); s.pop();
        if (!vis[cur]) {
            dfs2(out, ds, vis, cur, cur);
            tag[ds.root(cur)] = count;
            ++count;
        }
    }

    graph ans(count);
    for (int i = 0; i < out.size(); ++i) {
        int r1 = ds.root(i);
        for (auto &p : out[i]) {
            int r2 = ds.root(p.first);
            if (r1 != r2) {
                ans[tag[r1]][tag[r2]] = 1;
            }
        }
    }

    return ans;
}
