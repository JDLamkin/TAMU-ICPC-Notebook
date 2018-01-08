/* Hierholzer's algorithm finds an Euler circuit in an undirected ayclic graph.
 * Running time: O(V + E)
 * Input constraints: Every vertex in g must have an even degree.
 */

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef vector<map<int, int>> graph;

vector<int> euler(graph& g) {
    vector<int> circuit;
    vector<int> cur_path = {0};
    while (!cur_path.empty()) {
        int cur = *cur_path.rbegin();
        if (g[cur].empty()) {
            circuit.push_back(cur);
            cur_path.pop_back();
        } else {
            auto p = *g[cur].begin();
            g[cur].erase(p.first);
            g[p.first].erase(cur);
            cur_path.push_back(p.first);
        }
    }
    reverse(circuit.begin(), circuit.end());
    return circuit;
}
