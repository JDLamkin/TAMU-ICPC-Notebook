/* Hierholzer's algorithm finds an Euler circuit in a DAG.
 * Running time: O(V + E)
 * Input constraints: Every vertex in g must have in degree == out degree
 */

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef vector<map<int, int>> graph;

void dfs(graph &g, vector<int> &circuit, int cur) {
    for (auto& p : g[cur]) {
        g[cur].erase(p.first);
        dfs(g, circuit, p.first);
    }
    circuit.push_back(cur);
}

vector<int> euler(graph& g) {
    vector<int> circ;
    dfs(g, circ, 0);
    reverse(circ.begin(), circ.end());
    return circ;
}
