/* Floyd-Warshall is all-pairs shortest path that *does* handle negative edge weights (but not cycles). 
 * Running time: O(V^3)
 */

#include <vector>
#include <limits>
#include <map>
#include <queue>

using namespace std;

typedef vector<map<int, int>> graph;

#define INF numeric_limits<int>::max()

vector<vector<int>> dist(graph &g) {
	vector<vector<int>> dist(g.size(), vector<int>(g.size(), INF));

	for (int u = 0; u < g.size(); ++u) {
		dist[u][u] = 0;

		for (auto v : g[u]) {
			dist[u][v.first] = v.second;
		}
	}

	for (int k = 0; k < g.size(); ++k) {
		for (int i = 0; i < g.size(); ++i) {
			for (int j = 0; j < g.size(); ++j) {
				if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	return dist;
}
