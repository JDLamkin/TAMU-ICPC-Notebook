/* Dinic's algorithm - max flow / bipartite matching
 * Running time: O(E*V^2) in general and O(E*sqrt(V)) on bipartite graphs with unit edge weights
 */

#include <vector>
#include <limits>
#include <map>
#include <queue>

using namespace std;

typedef vector<map<int, int>> graph;
typedef map<int, int>::iterator it;

#define INF numeric_limits<int>::max()

bool bfs(graph &g, vector<int> &level, int s, int t) {
	for (int i = 0; i < g.size(); ++i) {
		level[i] = -1;
	}
	level[s] = 0;

	queue<int> q; q.push(s);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto e : g[u]) {
			int v = e.first, w = e.second;
			if (level[v] < 0 && w > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}

	return level[t] >= 0;
}

int dfs(graph &g, vector<int> &level, vector<it> &start, int u, int t, int flow) {
	if (u == t) return flow;

	for (it& e = start[u]; e != g[u].end(); ++e) {
		int v = e->first, w = e->second;
		if (level[v] == level[u]+1 && w > 0) {
			int cur_flow = min(flow, w);
			int temp_flow = dfs(g, level, start, v, t, cur_flow);
			if (temp_flow > 0) {
				g[u][v] -= temp_flow;
				g[v][u] += temp_flow;
				return temp_flow;
			}
		}
	}

	return 0;
}

int dinic(graph &g, int s, int t) {
	int total = 0;
	vector<int> level(g.size());
	vector<it> start(g.size());

	while (bfs(g, level, s, t)) {
		for (int i = 0; i < g.size(); ++i) start[i] = g[i].begin();
		while (int flow = dfs(g, level, start, s, t, INF)) {
			total += flow;
		}
	}

	return total;
}
