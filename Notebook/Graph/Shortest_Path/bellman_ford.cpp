/* Bellman-ford is single-source shortest path that *does* handle negative edge weights. 
 * Running time: O(E*V)
 */

#include <vector>
#include <limits>
#include <map>
#include <queue>

using namespace std;

typedef vector<map<int, int>> graph;

#define INF numeric_limits<int>::max()

vector<int> dist(graph &g, int src) {
    vector<int> dist(g.size(), INF);

    dist[src] = 0;

    for (int i = 0; i < g.size()-1; ++i) {
        for (int u = 0; u < g.size(); ++u) {
            for (auto k : g[u]) {
                int v = k.first, w = k.second;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    return dist;
}
