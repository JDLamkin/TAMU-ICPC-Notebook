#include <bits/stdc++.h>
using namespace std;
//index = node, value = vector<out-edges>
typedef vector<vector<int>> Graph;
#define pb push_back

Graph transpose(Graph& g){
	Graph t(g.size());
	for(int v=0; v<g.size(); ++v) for(int u : g[v]) t[u].pb(v);
	return t;
}

void dfs(Graph& g, int v, vector<bool>& visited, vector<int>& s){
	visited[v] = true;
	s.pb(v);
	for(int u : g[v]) if(!visited[u]) dfs(g, u, visited, s);
}

vector<vector<int>> sccs(Graph& g){
	vector<int> s;
	vector<bool> visited(g.size());

	for(int v=0; v<g.size(); ++v)
		if(!visited[v]) dfs(g, v, visited, s);

	Graph t = transpose(g);

	fill(visited.begin(), visited.end(), false);
	vector<vector<int>> sccs;
	while(!s.empty()){
		int v = s.back(); s.pop_back();
		if(!visited[v]){
			vector<int> comp;
			dfs(t, v, visited, comp);
			sccs.pb(comp);
		}
	}
	return sccs;
}
