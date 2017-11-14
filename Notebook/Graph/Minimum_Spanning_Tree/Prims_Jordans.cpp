/**
 * Generate a Minimum Spanning Tree on `g'.
 * Returns the total edge weight of the MST.
 * Preconditions:
 *  parent.size() == g.size();
 *  `g' is bidirectional and connected.
 * Postconditions:
 *  `parent[i]' refers to the parent vertex to `i' in the MST.
 * Complexity:
 * 	Time: O(E log E)
 * 	Space: O(V + E)
 */
ll PrimsMST(graph& g, vector<ull>& parent) {
	priority_queue<pair<ll, ull>> q;
	vector<ull> vis(g.size());
	ull vert = 0;
	ll w = 0;
	parent[vert] = vert;
	while(true) {
		vis[vert] = true;
		for(auto e : g[vert]) q.push(make_pair(-e.second, e.first));
		while(!q.empty() && vis[q.top().second]) q.pop();
		if(q.empty()) return w;
		auto e = q.top();
		q.pop();
		w -= e.first;
		parent[e.second] = vert;
		vert = e.second;
	}
}
