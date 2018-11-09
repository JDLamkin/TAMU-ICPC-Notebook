#include <vector>
#include <queue>
#include <map>

using namespace std;

typedef vector<map<int, int>> graph;

int prim(graph &g) {
    vector<bool> vis(g.size());
    priority_queue<pair<int, int>> pq;
    pq.push({0, 0});
    int ans = 0;
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int u, w; tie(w, u) = cur;
        if (vis[u]) continue;
        vis[u] = true;
        ans += -w;
        for (auto adj : g[u]) {
            if (!vis[adj.first]) pq.push({-adj.second, adj.first});
        }
    }
    return ans;
}
