#include <vector>
#include <limits>
#include <map>
#include <queue>

using namespace std;

typedef vector<map<int, int>> graph;

vector<int> dist(graph &g, int src) {
    vector<int> dist(g.size(), numeric_limits<int>::max());
    vector<bool> vis(g.size());

    auto cmp = [](pair<int, int> one, pair<int, int> two) { return one.second > two.second; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    dist[src] = 0;
    pq.push(make_pair(src, 0));

    while (!pq.empty()) {
        auto cur = pq.top().first; pq.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (auto adj : g[cur]) {
            if (dist[cur] + adj.second < dist[adj.first]) {
                dist[adj.first] = dist[cur] + adj.second;
                pq.push(make_pair(adj.first, dist[adj.first]));
            }
        }
    }

    return dist;
}
