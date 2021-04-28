#include <vector>
#include <limits>
#include <queue>
#include <cmath>

using namespace std;

struct edge {
    int u, v, cap, cost, flow, orig;
};

typedef vector<vector<int>> graph;

graph g;
vector<edge> edges;

void add_edge(int u, int v, int c, int w) {
    g[u].push_back(edges.size());
    edges.push_back({u, v, c, w, 0, w});
    g[v].push_back(edges.size());
    edges.push_back({v, u, 0, -w, 0, 0});
}

#define INF numeric_limits<int>::max()

// initial potentials using Bellman-Ford
vector<int> potentials(int src) {
    vector<int> pot(g.size(), INF);

    pot[src] = 0;

    bool change = true;
    for (int i = 0; i < g.size()-1 && change; ++i) {
        change = false;
        for (int u = 0; u < g.size(); ++u) {
            for (int k : g[u]) {
                edge e = edges[k];
                if (pot[u] != INF && e.cap - e.flow > 0 && pot[u] + e.cost < pot[e.v]) {
                    pot[e.v] = pot[u] + e.cost;
                    change = true;
                }
            }
        }
    }
    return pot;
}

// Dijkstra's using cost as distance
bool sssp(vector<int> &dist, vector<int> &parent, int src, int sink) {
    fill(dist.begin(), dist.end(), INF);
    vector<bool> vis(g.size());

    auto cmp = [](pair<int, int> one, pair<int, int> two) { return one.second > two.second; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    dist[src] = 0;
    parent[src] = -1;
    pq.push(make_pair(src, 0));

    while (!pq.empty()) {
        auto cur = pq.top().first; pq.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (int i : g[cur]) {
            edge e = edges[i];
            if (e.cap - e.flow > 0 && dist[cur] + e.cost < dist[e.v]) {
                dist[e.v] = dist[cur] + e.cost;
                parent[e.v] = i;
                pq.push(make_pair(e.v, dist[e.v]));
            }
        }
    }

    return dist[sink] != INF;
}

// Update "reduced" costs with potentials to avoid negative cycles
void reduce(vector<int> &dist) {
    for (int i = 0; i < edges.size(); ++i) {
        edge &forward = edges[i], &back = edges[i^1];
        if (forward.cap - forward.flow > 0) {
            forward.cost += dist[forward.u] - dist[forward.v];
            back.cost = 0;
        }
    }
}

pair<int, int> min_cost_max_flow(int s, int t) {
    auto dist = potentials(s);
    reduce(dist);
    vector<int> parent(g.size());
    int flow = 0, cost = 0;
    while (sssp(dist, parent, s, t)) {
        reduce(dist);
        int delta = INF;
        for (int cur = t; parent[cur] != -1; cur = edges[parent[cur]].u) {
            edge &e = edges[parent[cur]];
            delta = min(delta, e.cap - e.flow);
        }
        for (int cur = t; parent[cur] != -1; cur = edges[parent[cur]].u) {
            edge &forward = edges[parent[cur]], &back = edges[parent[cur] ^ 1];
            forward.flow += delta; 
            back.flow -= delta;
        }
        flow += delta;
    }

    // calculate cost using original costs
    for (int i = 0; i < edges.size(); ++i) {
        edge &e = edges[i];
        cost += e.flow * e.orig;
    }
    return make_pair(flow, cost);
}
